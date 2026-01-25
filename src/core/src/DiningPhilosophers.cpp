//
// Created by lukasz on 17.01.26.
//

#include <iomanip>

#include <core/DiningPhilosophers.hpp>

#include <philosophers/Philosopher.hpp>

#include <vector>
#include <thread>
#include <memory>
#include <syncstream>
#include <iostream>

#include <philosophers/ArbitratorCallEatMethod.hpp>

#include "philosophers/HierarchyEatMethod.hpp"
#include "philosophers/NoSyncEatMethod.hpp"
#include "philosophers/ScopedLockEatMethod.hpp"

void core::DiningPhilosophers::initializeForks(const uint32_t count) {
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
  std::vector<std::shared_ptr<philosophers::Philosopher> > philosophers;
  threads.reserve(philosopher_count_);
  philosophers.reserve(philosopher_count_);

  std::atomic<bool> monitor{true};

  // TODO: create a factory for EatMethods
  shared_resources::ForkArbitrator fork_arbitrator{};
  auto eat_method = std::make_shared<philosophers::ArbitratorCallEatMethod>(fork_arbitrator);

  for (uint32_t i = 0; i < philosopher_count_; i++) {
    philosophers.push_back(std::make_shared<::philosophers::Philosopher>(
      i,
      eat_method,
      forks.at(i),
      forks.at((i + 1) % forks.size())));
  }

  for (const auto &philosopher : philosophers) {
    threads.emplace_back([philosopher] {
      philosopher->run();
    });
  }

  // TODO: create a monitor class that also analyses results
  std::thread monitoring_thread([&philosophers, &monitor] {
    std::vector<philosophers::State> states;
    std::vector<philosophers::State> prev_states(philosophers.size(), philosophers::Done);
    std::vector hungry_timestamps(philosophers.size(), std::chrono::system_clock::now());

    std::vector<uint32_t> ate_counts(philosophers.size(), 0);
    const auto wait_times = std::make_shared<std::vector<std::chrono::duration<long, std::ratio<1, 1000000000> > > >();
    const auto eating_counts = std::make_shared<std::vector<uint32_t> >();

    states.reserve(philosophers.size());

    uint64_t total_meals_last = 0;
    uint32_t consecutive_all_hungry = 0;
    uint32_t consecutive_no_progress = 0;

    while (monitor.load()) {
      states.clear();
      const auto time_stamp_start = std::chrono::system_clock::now();

      for (const auto &philosopher : philosophers) {
        states.push_back(philosopher->state);
      }

      bool all_hungry = std::all_of(states.begin(), states.end(), [](int s) { return s == 0; });
      if (all_hungry) consecutive_all_hungry++;
      else consecutive_all_hungry = 0;

      uint64_t total_meals_curr = std::accumulate(ate_counts.begin(), ate_counts.end(), 0ULL);
      if (total_meals_curr == total_meals_last) consecutive_no_progress++;
      else {
        consecutive_no_progress = 0;
        total_meals_last = total_meals_curr;
      }

      if (consecutive_all_hungry > 500000) {
        std::cerr << "\n[!] CRITICAL: DEADLOCK DETECTED (Circular Wait)\n";
        monitor.store(false);
        break;
      }
      if (consecutive_no_progress > 2000000) {
        std::cerr << "\n[!] CRITICAL: LIVELOCK DETECTED (No progress made)\n";
        monitor.store(false);
        break;
      }

      for (int i = 0; i < states.size(); i++) {
        if (const auto curr_state = states.at(i); curr_state != prev_states.at(i)) {
          if (curr_state == philosophers::Thinking) {
            ate_counts.at(i) += 1;
          } else if (curr_state == philosophers::Hungry) {
            hungry_timestamps.at(i) = std::chrono::system_clock::now();
          } else if (curr_state == philosophers::Eating) {
            auto dur = std::chrono::system_clock::now() - hungry_timestamps.at(i);
            wait_times->push_back(dur);
          }
        }
      }

      eating_counts->push_back(std::count_if(states.begin(),
                                             states.end(),
                                             [](const uint32_t x) { return x == philosophers::Eating; }));

      prev_states = states;

      const auto time_stamp_end_sync = std::chrono::system_clock::now();
      std::this_thread::sleep_for(std::chrono::microseconds(1)
        - std::chrono::duration_cast<std::chrono::nanoseconds>(time_stamp_end_sync - time_stamp_start));
    }

    std::cout << "\n" << std::string(40, '=') << "\n";
    std::cout << " FINAL SIMULATION ANALYTICS \n";
    std::cout << std::string(40, '=') << "\n";

    uint64_t total_meals = std::accumulate(ate_counts.begin(), ate_counts.end(), 0ULL);
    double avg_meals = static_cast<double>(total_meals) / ate_counts.size();

    double variance = 0;
    for (uint32_t count : ate_counts) {
      variance += std::pow(count - avg_meals, 2);
    }
    double std_dev = std::sqrt(variance / ate_counts.size());
    double rsd = (avg_meals > 0) ? (std_dev / avg_meals) * 100.0 : 0.0;

    double avg_wait_ms = 0;
    double max_wait_ms = 0;
    if (!wait_times->empty()) {
      double total_wait = 0;
      for (auto dur : *wait_times) {
        double ms = dur.count() / 1e6;
        total_wait += ms;
        if (ms > max_wait_ms) max_wait_ms = ms;
      }
      avg_wait_ms = total_wait / wait_times->size();
    }

    double avg_concurrency = 0;
    uint32_t peak_concurrency = 0;
    if (!eating_counts->empty()) {
      avg_concurrency = std::accumulate(eating_counts->begin(), eating_counts->end(), 0.0) / eating_counts->size();
      peak_concurrency = *std::max_element(eating_counts->begin(), eating_counts->end());
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "[THROUGHPUT]\n";
    std::cout << "  - Total Meals:     " << total_meals << "\n";
    std::cout << "  - Avg Meals/Phil:  " << avg_meals << "\n\n";

    std::cout << "[FAIRNESS & STABILITY]\n";
    std::cout << "  - Std Deviation:   " << std_dev << " meals\n";
    std::cout << "  - Rel. Std Dev:    " << rsd << "%\n";
    std::cout << "  - Range (Min/Max): " << *std::min_element(ate_counts.begin(), ate_counts.end())
        << " to " << *std::max_element(ate_counts.begin(), ate_counts.end()) << "\n\n";

    std::cout << "[LATENCY]\n";
    std::cout << "  - Avg Wait Time:   " << avg_wait_ms << " ms\n";
    std::cout << "  - Worst Starve:    " << max_wait_ms << " ms\n\n";

    std::cout << "[PARALLELISM]\n";
    std::cout << "  - Avg Concurrency: " << avg_concurrency << " philosophers eating\n";
    std::cout << "  - Peak Concurrency: " << peak_concurrency << " philosophers eating\n";
    std::cout << std::string(40, '=') << "\n";
  });

  for (auto &t : threads) {
    t.join();
  }

  monitor = false;
  if (monitoring_thread.joinable()) {
    monitoring_thread.join();
  }

  std::cout << "Finished" << std::endl;
}
