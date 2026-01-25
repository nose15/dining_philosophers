//
// Created by lukasz on 17.01.26.
//

#include <core/DiningPhilosophers.hpp>

#include <philosophers/Philosopher.hpp>

#include <vector>
#include <thread>
#include <memory>
#include <syncstream>
#include <iostream>

#include <philosophers/ArbitratorCallEatMethod.hpp>
#include <philosophers/NoSyncEatMethod.hpp>
#include <philosophers/ScopedLockEatMethod.hpp>

void core::DiningPhilosophers::initializeForks(const uint32_t count) {
  forks.reserve(count);

  for (uint32_t i = 0; i < count; i++) {
    forks.emplace_back(i);
  }
}

core::DiningPhilosophers::DiningPhilosophers(const uint32_t philosopher_count) {
  initializeForks(philosopher_count);

  philosopher_count_ = philosopher_count;
}

void core::DiningPhilosophers::run() const {
  std::vector<std::thread> threads;
  std::vector<std::shared_ptr<philosophers::Philosopher>> philosophers;
  threads.reserve(philosopher_count_);
  philosophers.reserve(philosopher_count_);

  // TODO: create a factory for EatCallMethod
  shared_resources::ForkArbitrator fork_arbitrator{};
  auto eat_method = std::make_shared<philosophers::ArbitratorCallEatMethod>(fork_arbitrator);

  for (uint32_t i = 0; i < philosopher_count_; i++) {
    philosophers.push_back(std::make_shared<::philosophers::Philosopher>(
      i, eat_method, forks.at(i), forks.at((i + 1) % forks.size())));
  }

  for (const auto& philosopher : philosophers) {
    threads.emplace_back([philosopher] {
      philosopher->run();
    });
  }

  // TODO: create a monitor class that also analyses results
  std::thread monitoring_thread([&philosophers, &threads] {
    while (threads.at(0).joinable()) {
      const auto time_stamp_start = std::chrono::system_clock::now();
      std::string output = std::to_string(time_stamp_start.time_since_epoch().count()) + " ";

      for (const auto& philosopher : philosophers) {
        output.append(std::to_string(philosopher->state) + " ");
      }
      const auto time_stamp_end = std::chrono::system_clock::now();

      output.append(std::to_string(time_stamp_end.time_since_epoch().count()));

      std::osyncstream(std::cout) << output << std::endl;

      const auto time_stamp_end_sync = std::chrono::system_clock::now();

      std::this_thread::sleep_for(std::chrono::milliseconds(1)
        - std::chrono::duration_cast<std::chrono::nanoseconds>(time_stamp_end_sync - time_stamp_start));
    }
  });

  for (auto &t : threads) {
    t.join();
  }
}

