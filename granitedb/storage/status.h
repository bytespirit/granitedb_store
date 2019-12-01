/*
 * @Author: lipixun
 * @Date: 2019-11-30 17:58:34
 * @Last Modified by: lipixun
 * @Last Modified time: 2019-11-30 18:09:50
 */

#ifndef GITHUB_BYTESPIRIT_GRANITEDB_GRANITEDB_STORAGE_STATUS_H_
#define GITHUB_BYTESPIRIT_GRANITEDB_GRANITEDB_STORAGE_STATUS_H_

namespace bytespirit {
namespace granitedb {
namespace storage {

class Status {
 public:
  // State
  auto get_state() const -> int { return state_; }
  auto set_state(int state) -> void { state_ = state; }
  // Open timestamp
  auto get_open_ts() const -> std::time_t { return open_ts_; }
  auto set_open_ts(std::time_t ts) -> void { open_ts_ = ts; }

 private:
  int state_;
  std::time_t open_ts_;
};

}  // namespace storage
}  // namespace granitedb
}  // namespace bytespirit

#endif  // GITHUB_BYTESPIRIT_GRANITEDB_GRANITEDB_STORAGE_STATUS_H_
