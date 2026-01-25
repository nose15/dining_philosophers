//
// Created by lukasz on 17.01.26.
//

#include <core/DiningPhilosophers.hpp>

#include <philosophers/Philosopher.hpp>

#include <vector>
#include <thread>
#include <memory>

#include "philosophers/ArbitratorCallEatMethod.hpp"
#include "philosophers/ScopedLockEatMethod.hpp"

void core::DiningPhilosophers::initializeForks(const uint32_t count) {
  forks.reserve(count);

  for (uint32_t i = 0; i < count; i++) {
    forks.emplace_back(i);
  }
}

core::DiningPhilosophers::DiningPhilosophers(uint32_t philosopher_count) {
  initializeForks(philosopher_count);

  philosopher_count_ = philosopher_count;
}

void core::DiningPhilosophers::run() const {
  std::vector<std::thread> threads;
  std::vector<std::shared_ptr<philosophers::Philosopher>> philosophers;
  threads.reserve(philosopher_count_);
  philosophers.reserve(philosopher_count_);

  auto eat_method = std::make_shared<philosophers::ScopedLockEatMethod>();
  shared_resources::ForkArbitrator fork_arbitrator{};

  for (uint32_t i = 0; i < philosopher_count_; i++) {
    philosophers.push_back(std::make_shared<::philosophers::Philosopher>(
      i, eat_method, forks.at(i), forks.at((i + 1) % forks.size())));
  }

  for (const auto& philosopher : philosophers) {
    threads.emplace_back([philosopher] {
      philosopher->run();
    });
  }

  for (auto &t : threads) {
    t.join();
  }
}

