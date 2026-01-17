//
// Created by lukasz on 17.01.26.
//

#include <core/DiningPhilosophers.hpp>

#include <core/Fork.hpp>
#include <core/Philosopher.hpp>

#include <iostream>
#include <vector>
#include <thread>
#include <memory>

void core::DiningPhilosophers::initializeForks(uint32_t count) {
  forks.reserve(count);

  for (uint32_t i = 0; i < count; i++) {
    auto fork = std::make_shared<core::Fork>();
    forks.push_back(fork);
  }
}

core::DiningPhilosophers::DiningPhilosophers(uint32_t philosopher_count) {
  initializeForks(philosopher_count);

  philosopher_count_ = philosopher_count;
}

void core::DiningPhilosophers::run() {
  std::vector<std::shared_ptr<std::thread>> threads;
  threads.reserve(philosopher_count_);

  for (uint32_t i = 0; i < philosopher_count_; i++) {
    auto philosopher = std::make_unique<core::Philosopher>(
        i + 1, forks.at(i), forks.at((i + 1) % philosopher_count_));

    auto philThread = std::make_shared<std::thread>([ philosopher = std::move(philosopher) ] {
      philosopher->run();
    });

    threads.push_back(philThread);
  }

  for (const auto &thread : threads) {
    thread->join();
  }
}

