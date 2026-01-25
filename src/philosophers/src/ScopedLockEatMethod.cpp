//
// Created by lukasz on 25.01.26.
//

#include <random>
#include <thread>

#include <philosophers/ScopedLockEatMethod.hpp>

namespace philosophers {

void ScopedLockEatMethod::operator()(const shared_resources::Fork &left_fork, const shared_resources::Fork &right_fork, std::atomic<State>& state) {
  thread_local std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<uint64_t> nano_dist(0, DF_MAX_EATING_TIME_DEV_NS);


  std::scoped_lock lock(left_fork.mutex_, right_fork.mutex_);

  state = Eating;

  std::this_thread::sleep_for(std::chrono::microseconds(DF_EATING_TIME_US) + std::chrono::nanoseconds(nano_dist(gen)));
}

}
