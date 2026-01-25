//
// Created by lukasz on 25.01.26.
//

#include <philosophers/HierarchyEatMethod.hpp>

#include <thread>

namespace philosophers {

void HierarchyEatMethod::operator()(const shared_resources::Fork &left_fork, const shared_resources::Fork &right_fork) {
  if (left_fork.id_ < right_fork.id_) {
    left_fork.mutex_.lock();
    right_fork.mutex_.lock();
  } else {
    right_fork.mutex_.lock();
    left_fork.mutex_.lock();
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(10) + std::chrono::microseconds(random() % 100));

  left_fork.mutex_.unlock();
  right_fork.mutex_.unlock();
}

}
