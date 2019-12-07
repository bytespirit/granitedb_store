/*
 * @Author: lipixun
 * @Date: 2019-12-07 16:42:16
 * @Last Modified by: lipixun
 * @Last Modified time: 2019-12-07 16:49:04
 */

#include "db.h"

#include <exception>

using namespace bytespirit;
using namespace bytespirit::granitedb;
using namespace bytespirit::granitedb::storage;

Database::Database(std::unique_ptr<rocksdb::DB>&& db,
                   std::vector<std::unique_ptr<rocksdb::ColumnFamilyHandle>>&& cl_handlers, const DBOptions& options)
    : db_(std::move(db)), cl_handlers_(std::move(cl_handlers)), options_(options) {
  if (db_ == nullptr) {
    throw std::invalid_argument("Parameter [db] is null");
  }
}

~Database::Database() {
  Close();  // Safely close (and wait)
}

