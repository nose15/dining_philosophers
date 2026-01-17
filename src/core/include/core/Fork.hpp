//
// Created by lukasz on 17.01.26.
//

#ifndef DINING_PHILOSOPHERS_SRC_CORE_INCLUDE_CORE_FORK_HPP_
#define DINING_PHILOSOPHERS_SRC_CORE_INCLUDE_CORE_FORK_HPP_

#include <mutex>

namespace core {

class Fork {
 public:
  mutable std::mutex mutex_;
};

}

#endif //DINING_PHILOSOPHERS_SRC_CORE_INCLUDE_CORE_FORK_HPP_
