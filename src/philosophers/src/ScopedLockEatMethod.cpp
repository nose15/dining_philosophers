//
// Created by lukasz on 25.01.26.
//

#include <thread>

#include <philosophers/ScopedLockEatMethod.hpp>

namespace philosophers {

void ScopedLockEatMethod::operator()(const shared_resources::Fork &left_fork, const shared_resources::Fork &right_fork, std::atomic<State>& state) {
  std::scoped_lock lock(left_fork.mutex_, right_fork.mutex_);

  state = Eating;

  std::this_thread::sleep_for(std::chrono::milliseconds(10) + std::chrono::microseconds(random() % 100));
}

}
