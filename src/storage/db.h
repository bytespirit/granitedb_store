/*
 * @Author: lipixun
 * @Date: 2019-11-30 17:50:32
 * @Last Modified by: lipixun
 * @Last Modified time: 2019-12-08 00:19:56
 */

#ifndef GITHUB_BYTESPIRIT_GRANITEDB_GRANITEDB_STORAGE_DB_H_
#define GITHUB_BYTESPIRIT_GRANITEDB_GRANITEDB_STORAGE_DB_H_

#include <functional>
#include <memory>
#include <string>

#include "rocksdb/db.h"

#include "common/status.h"

#include "idl/granitedb/storage/read.pb.h"
#include "idl/granitedb/storage/sync.pb.h"
#include "idl/granitedb/storage/update.pb.h"

namespace bytespirit {
namespace granitedb {
namespace storage {

//
// The sync up stream interface
//
class SyncUpStream {
 public:
  virtual ~SyncUpStream() {}
  // Get closed state
  virtual auto get_closed() const noexcept -> bool = 0;
  // Write data to sync
  virtual auto Write(const SyncData& data) -> bool = 0;
  // Read the sync result
  virtual auto Read(SyncAck* ack) -> bool = 0;
};

//
// The catch up stream interface
//
class CatchUpStream {
 public:
  virtual ~CatchUpStream() {}
  // Get closed state
  virtual auto get_closed() const noexcept -> bool = 0;
  // Read data to sync
  virtual auto Read(SyncData* data) -> bool = 0;
  // Write sync result
  virtual auto Write(SyncAck* ack) -> bool = 0;
};

// The update ack callback
// NOTE:
//  The ack parameter has already encoded `status` in itself
typedef std::function<void(const Status& status, const EnsureAck& ack)> EnsureCallback;

//
// Database implementation
//
class Database {
 public:
  explict Database(std::unique_ptr<rocksdb::DB>&& db,
                   std::vector<std::unique_ptr<rocksdb::ColumnFamilyHandle>>&& cl_handlers)
      : Database(std::move(db), std::move(cl_handlers), Options()) {}
  explict Database(std::unique_ptr<rocksdb::DB>&& db,
                   std::vector<std::unique_ptr<rocksdb::ColumnFamilyHandle>>&& cl_handlers, const Options& options);

  // Close the database and release resources
  // NOTE:
  //  This operation may take sometime to complete.
  //  Please consider calling the `Close` function explicitly in a thread.
  virtual ~Database();

  // Close the database safely
  virtual auto Close() noexcept -> void;

  // Get closed
  auto get_closed() const noexcept -> bool { return closed_; }
  // Get options
  auto get_options() const noexcept -> const Options& { return options_; }

  //
  // Read & Update
  //

  // Read data
  virtual auto Read(const ReadParam& param, ReadData* data) -> Status;
  // Update data
  virtual auto Update(const UpdateParam& param, UpdateAck* ack) -> Status;
  // Ensure data (Ensure the number of wrote instances)
  virtual auto Ensure(const EnsureParam& param, EnsureCallback cb) -> void;

  //
  // Sync functions
  //

  // Sync up data to another database (always be called on master database)
  virtual auto SyncUp(const std::shared_ptr<SyncUpStream>& syncup_stream) -> void;
  // Catch up data from another database (always be called on slave database)
  virtual auto CatchUp(const std::shared_ptr<CatchUpStream>& catchup_stream) -> void;

  //
  // Maintain functions
  //

  // Get the open column family size
  auto get_open_column_family_size() const -> size_t {
    size_t count = 0;
    for (const auto& handler : cf_handlers_) {
      if (handler != nullptr) {
        ++count;
      }
      return count;
    }
  }

  // Create column family
  virtual auto CreateColumnFamily(size_t index, const std::string& name, const rocksdb::ColumnFamilyOptions& options)
      -> Status;

  // Drop column family
  virtual auto DropColumnFamily(size_t index) -> Status;

 protected:
  // Get rocksdb instance pointer
  auto get_db() const noexcept -> const std::unique_ptr<rocksdb::DB>& { return db_; }

  //
  // Update
  //

 private:
  bool closed_ = false;
  std::unique_ptr<rocksdb::DB> db_;
  std::vector<std::unique_ptr<rocksdb::ColumnFamilyHandle>> cf_handlers_;
  Options options_;
};

}  // namespace storage
}  // namespace granitedb
}  // namespace bytespirit

#endif  // GITHUB_BYTESPIRIT_GRANITEDB_GRANITEDB_STORAGE_DB_H_
