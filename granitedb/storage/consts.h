/*
 * @Author: lipixun
 * @Date: 2019-11-30 18:00:43
 * @Last Modified by: lipixun
 * @Last Modified time: 2019-11-30 18:08:29
 */

#ifndef GITHUB_BYTESPIRIT_GRANITEDB_GRANITEDB_STORAGE_CONSTS_H_
#define GITHUB_BYTESPIRIT_GRANITEDB_GRANITEDB_STORAGE_CONSTS_H_

#include <string.h>
#include <unordered_map>

namespace bytespirit {
namespace granitedb {
namespace storage {

static const int kStateOK = 0;
static const int kStateFault = 1;
static const int kStateOpening = 2;
static const int kStateSyncing = 3;

auto kStateToString(int state) -> const std::string&;

}  // namespace storage
}  // namespace granitedb
}  // namespace bytespirit

#endif  // GITHUB_BYTESPIRIT_GRANITEDB_GRANITEDB_STORAGE_CONSTS_H_
