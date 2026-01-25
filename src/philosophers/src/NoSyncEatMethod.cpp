//
// Created by lukasz on 25.01.26.
//

#include <philosophers/NoSyncEatMethod.hpp>

#include <thread>

#include <random>


namespace philosophers {

void NoSyncEatMethod::operator()(const shared_resources::Fork &left_fork, const shared_resources::Fork &right_fork, std::atomic<State>& state) {
  thread_local std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<uint64_t> micro_dist(0, MAX_EATING_TIME_DEV_US);

  left_fork.mutex_.lock();
  std::this_thread::yield();
  right_fork.mutex_.lock();

  state = Eating;

  const auto dur = std::chrono::milliseconds(EATING_TIME_MS) + std::chrono::microseconds(micro_dist(gen));
  std::this_thread::sleep_for(dur);

  left_fork.mutex_.unlock();
  right_fork.mutex_.unlock();
}

}
