//
// Created by lukasz on 17.01.26.
//

#ifndef DINING_PHILOSOPHERS_SRC_CORE_INCLUDE_CORE_FORK_HPP_
#define DINING_PHILOSOPHERS_SRC_CORE_INCLUDE_CORE_FORK_HPP_

#include <atomic>
#include <mutex>

namespace shared_resources {

class Fork {
 public:
  Fork() = default;
  Fork(const Fork& other);
  Fork(Fork&&) noexcept;
  explicit Fork(uint32_t id);
  std::atomic<uint32_t> id_;
  mutable std::mutex mutex_;
};

}

#endif //DINING_PHILOSOPHERS_SRC_CORE_INCLUDE_CORE_FORK_HPP_
