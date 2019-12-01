/*
 * @Author: lipixun
 * @Date: 2019-11-30 17:50:32
 * @Last Modified by: lipixun
 * @Last Modified time: 2019-11-30 20:06:08
 */

#ifndef GITHUB_BYTESPIRIT_GRANITEDB_GRANITEDB_STORAGE_DB_H_
#define GITHUB_BYTESPIRIT_GRANITEDB_GRANITEDB_STORAGE_DB_H_

#define DEFAULT_DBOPTIONS_SYNC_BATCH_SIZE 4194304  // 4MB

#include <memory>
#include <string>

#include "rocksdb/db.h"
#include "rocksdb/options.h"
#include "rocksdb/slice.h"

#include "idl/sync.pb.h"
#include "status.h"

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
  virtual auto get_closed() const -> bool = 0;
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
  virtual ~SyncUpStream() {}
  // Get closed state
  virtual auto get_closed() const -> bool = 0;
  // Read data to sync
  virtual auto Read(SyncData* data) -> bool = 0;
  // Write sync result
  virtual auto Write(SyncAck* ack) -> bool = 0;
};

class DBOptions : public rocksdb::DBOptions {
 public:
  DBOptions() : DBOptions(rocksdb::DBOptions()) {}
  DBOptions(const rocksdb::DBOptions& options) : DBOptions(options, false, DEFAULT_DBOPTIONS_SYNC_BATCH_SIZE) {}
  DBOptions(const rocksdb::DBOptions& options, bool readonly, size_t sync_batch_size)
      : rocksdb::DBOptions(options), readonly_(readonly), sync_batch_size_(sync_batch_size) {}

  // Readonly
  auto get_readonly() const -> bool { return readonly_; }

  //
  // Sync options
  //

  // Sync batch size
  auto get_sync_batch_size() const -> size_t { return sync_batch_size_; }

 private:
  bool readonly_;
  size_t sync_batch_size_;
};

//
// Database implements all necessary features of a single-shard database
//
// Critical features:
//
//  1. Single write thread internally
//
class Database {
 public:
  explict Database(const std::string& path) : Database(path, DBOptions()) {}
  explict Database(const std::string& path, const DBOptions& db_options);
  virtual ~Database();

  //
  // Status
  //

  // Get unique id
  auto get_id() const -> const std::string& { return id_; }
  // Get database status
  auto get_status() const -> const Status& { return status_; }

  //
  // Read functions
  //

  //
  // Write & Delete functions
  //

  //
  // Sync functions
  //

  // Sync data to another database (always slave database)
  auto SyncUp(const std::shared_ptr<SyncUpStream>& syncup_stream) -> void;
  // Catch data from another database (always master database)
  auto CatchUp(const std::shared_ptr<CatchUpStream>& catchup_stream) -> void;

  //
  // Maintain functions
  //

 private:
  auto WriteWorker() -> void;

  std::string id_;
  Status status_;
  rocksdb::DB* db_;
  DBOptions db_options_;
  std::thread_t write_thread_;
};

}  // namespace storage
}  // namespace granitedb
}  // namespace bytespirit

#endif  // GITHUB_BYTESPIRIT_GRANITEDB_GRANITEDB_STORAGE_DB_H_
