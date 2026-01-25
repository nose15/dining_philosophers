//
// Created by lukasz on 25.01.26.
//

#include <iostream>
#include <syncstream>

#include <philosophers/Philosopher.hpp>

#include <philosophers/config.hpp>

#include <thread>
#include <utility>

namespace philosophers {

Philosopher::Philosopher(const uint32_t id, std::shared_ptr<IEatMethod> eat_method, const shared_resources::Fork& left_fork, const shared_resources::Fork& right_fork) :
  id(id), left_fork_(left_fork), right_fork_(right_fork), eat_method_(std::move(eat_method)), gen(id) {
}

void Philosopher::run() const {
  for (uint64_t i = 0; i < DF_ITERATIONS; i++) {
    think();
    eat();
  }

  state = Done;
}

void Philosopher::eat() const {
  state = Hungry;
  (*eat_method_)(left_fork_, right_fork_, state);
}

void Philosopher::think() const {
  state = Thinking;
  std::uniform_int_distribution<uint64_t> dist(DF_THINKING_TIME_US - DF_THINKING_TIME_DEV_US, DF_THINKING_TIME_US + DF_THINKING_TIME_DEV_US);
  const auto dur = std::chrono::microseconds(dist(gen));

  std::this_thread::sleep_for(dur);
}

}
