/*
 * @Author: lipixun
 * @Date: 2019-12-07 20:48:06
 * @Last Modified by: lipixun
 * @Last Modified time: 2019-12-07 20:49:37
 */

#ifndef GITHUB_BYTESPIRIT_GRANITEDB_GRANITEDB_STORAGE_OPTIONS_H_
#define GITHUB_BYTESPIRIT_GRANITEDB_GRANITEDB_STORAGE_OPTIONS_H_

#define DEFAULT_OPTIONS_SYNC_BATCH_SIZE 41943040      // 40MB
#define DEFAULT_OPTIONS_SYNC_MAX_BATCH_SIZE 41943040  // 40MB
#define DEFAULT_OPTIONS_SYNC_WAIT_TIMEOUT_MS 500      // 500ms

namespace bytespirit {
namespace granitedb {
namespace storage {

class Options {
 public:
  Options()
      : Options(DEFAULT_OPTIONS_SYNC_BATCH_SIZE, DEFAULT_OPTIONS_SYNC_MAX_BATCH_SIZE,
                DEFAULT_OPTIONS_SYNC_WAIT_TIMEOUT_MS) {}
  Options(size_t sync_batch_size, size_t sync_max_batch_size, int sync_wait_timeout_ms)
      : sync_batch_size_(sync_batch_size),
        sync_max_batch_size_(sync_max_batch_size),
        sync_wait_timeout_ms_(sync_wait_timeout_ms) {}
  ~Options() {}

  //
  // Sync options
  //

  // Sync batch size
  auto get_sync_batch_size() const noexcept -> size_t { return sync_batch_size_; }
  auto set_sync_batch_size(size_t size) noexcept -> bool {
    if (size >= 0) {
      sync_batch_size_ = size;
      return true;
    }
    return false;
  }

  // Sync max batch size
  auto get_sync_max_batch_size() const noexcept -> size_t { return sync_max_batch_size_; }
  auto set_sync_max_batch_size(size_t size) noexcept -> bool {
    if (size >= 0) {
      sync_max_batch_size_ = size;
      return true;
    }
    return false;
  }

  // Sync wait timeout ms
  auto get_sync_wait_timeout_ms() const noexcept -> int { return sync_wait_timeout_ms_; }
  auto set_sync_wait_timeout_ms(int timeout) noexcept -> bool {
    if (timeout >= 0) {
      sync_wait_timeout_ms_ = sync_wait_timeout_ms;
      return true;
    }
    return false;
  }

 private:
  size_t sync_batch_size_;
  size_t sync_max_batch_size_;
  int sync_wait_timeout_ms_;
};

}  // namespace storage
}  // namespace granitedb
}  // namespace bytespirit

#endif  // GITHUB_BYTESPIRIT_GRANITEDB_GRANITEDB_STORAGE_OPTIONS_H_
