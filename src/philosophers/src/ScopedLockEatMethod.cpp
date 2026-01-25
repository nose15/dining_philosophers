//
// Created by lukasz on 25.01.26.
//

#include <random>
#include <thread>

#include <philosophers/ScopedLockEatMethod.hpp>

namespace philosophers {

void ScopedLockEatMethod::operator()(const shared_resources::Fork &left_fork, const shared_resources::Fork &right_fork, std::atomic<State>& state) {
  thread_local std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<uint64_t> micro_dist(0, MAX_EATING_TIME_DEV_US);


  std::scoped_lock lock(left_fork.mutex_, right_fork.mutex_);

  state = Eating;

  std::this_thread::sleep_for(std::chrono::milliseconds(EATING_TIME_MS) + std::chrono::microseconds(micro_dist(gen)));
}

}
