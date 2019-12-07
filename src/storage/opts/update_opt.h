/*
 * @Author: lipixun
 * @Date: 2019-12-07 20:45:42
 * @Last Modified by: lipixun
 * @Last Modified time: 2019-12-07 21:05:37
 */

#ifndef GITHUB_BYTESPIRIT_GRANITEDB_GRANITEDB_STORAGE_OPTS_UPDATE_OPT_H_
#define GITHUB_BYTESPIRIT_GRANITEDB_GRANITEDB_STORAGE_OPTS_UPDATE_OPT_H_

#include <functional>

#include "rocksdb/db.h"
#include "rocksdb/write_batch.h"

namespace bytespirit {
namespace granitedb {
namespace storage {
namespace opts {

typedef std::function<Status(const DB& db, const std::vector<std::unique_ptr<rocksdb::ColumnFamilyHandle>>& cf_handlers,
                             const UpdateOpt& opt, rocksdb::WriteBatch* batch)>
    UpdateOptHandler;

const std::vector<UpdateOptHandler> UpdateOptFuncs = {
    nullptr,                        // 0. Unset
    nullptr,                        // 1. Unused
    nullptr,                        // 2. Unused
    nullptr,                        // 3. Unused
    nullptr,                        // 4. Unused
    nullptr,                        // 5. Unused
    update_opt_put_handler,         // 6. Put
    update_opt_delete_handler,      // 7. Delete
    update_opt_arithmetic_handler,  // 8. Arithmetic
    update_opt_script_handler,      // 9. Script
};

}  // namespace opts
}  // namespace storage
}  // namespace granitedb
}  // namespace bytespirit

#endif  // GITHUB_BYTESPIRIT_GRANITEDB_GRANITEDB_STORAGE_OPTS_UPDATE_OPT_H_
