//
// Created by lukasz on 25.01.26.
//

#ifndef DINING_PHILOSOPHERS_SRC_PHILOSOPHER_INCLUDE_PHILOSOPHER_IPHILOSOPHER_HPP_
#define DINING_PHILOSOPHERS_SRC_PHILOSOPHER_INCLUDE_PHILOSOPHER_IPHILOSOPHER_HPP_

#include <shared_resources/Fork.hpp>
#include <philosophers/IEatMethod.hpp>

#include <cstdint>
#include <memory>
#include <random>
#include <vector>

#include <philosophers/State.hpp>

namespace philosophers {

class Philosopher {
  private:
    const uint32_t id;

    mutable std::mt19937 gen;

    const shared_resources::Fork& left_fork_;
    const shared_resources::Fork& right_fork_;

    std::shared_ptr<IEatMethod> eat_method_;

    void eat() const;
    void think() const;

  public:
    mutable std::atomic<State> state;

    Philosopher(
      uint32_t id,
      std::shared_ptr<IEatMethod> eat_method,
      const shared_resources::Fork& left_fork,
      const shared_resources::Fork& right_fork);

    void run() const;
};

}

#endif //DINING_PHILOSOPHERS_SRC_PHILOSOPHER_INCLUDE_PHILOSOPHER_IPHILOSOPHER_HPP_
