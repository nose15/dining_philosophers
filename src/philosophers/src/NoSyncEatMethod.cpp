//
// Created by lukasz on 25.01.26.
//

#include <philosophers/NoSyncEatMethod.hpp>

#include <thread>

#include <random>


namespace philosophers {

void NoSyncEatMethod::operator()(const shared_resources::Fork &left_fork, const shared_resources::Fork &right_fork) {
  thread_local std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<uint64_t> micro_dist(0, 10);

  left_fork.mutex_.lock();
  std::this_thread::sleep_for(std::chrono::microseconds(10));
  right_fork.mutex_.lock();

  const auto dur = std::chrono::milliseconds(1) + std::chrono::microseconds(micro_dist(gen));
  std::this_thread::sleep_for(dur);

  left_fork.mutex_.unlock();
  right_fork.mutex_.unlock();
}

}
