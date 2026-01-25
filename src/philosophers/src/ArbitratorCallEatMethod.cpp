//
// Created by lukasz on 25.01.26.
//

#include <random>

#include <philosophers/ArbitratorCallEatMethod.hpp>

#include <thread>

namespace philosophers {

ArbitratorCallEatMethod::ArbitratorCallEatMethod(const shared_resources::ForkArbitrator &fork_arbitrator) : fork_arbitrator_(fork_arbitrator) {}

void ArbitratorCallEatMethod::operator()(const shared_resources::Fork &left_fork, const shared_resources::Fork &right_fork, std::atomic<State>& state) {
  thread_local std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<uint64_t> nano_dist(0, DF_MAX_EATING_TIME_DEV_NS);

  fork_arbitrator_.mutex_.lock();

  left_fork.mutex_.lock();
  right_fork.mutex_.lock();

  fork_arbitrator_.mutex_.unlock();

  state = Eating;

  std::this_thread::sleep_for(std::chrono::microseconds(DF_EATING_TIME_US) + std::chrono::nanoseconds(nano_dist(gen)));

  left_fork.mutex_.unlock();
  right_fork.mutex_.unlock();
}

}
