//
// Created by lukasz on 17.01.26.
//

#include <core/Philosopher.hpp>

#include <thread>
#include <mutex>
#include <chrono>
#include <iostream>
#include <syncstream>

namespace core {

Philosopher::Philosopher(const uint32_t id, std::shared_ptr<Fork> left_fork, std::shared_ptr<Fork> right_fork) :
  id(id), left_fork_(std::move(left_fork)), right_fork_(std::move(right_fork)) {}

void Philosopher::run() {
  for (uint64_t i = 0; i < INT64_MAX; i++) {
    think();
    eat();
  }
}

void Philosopher::eat() {
  std::osyncstream(std::cout) << "Philosopher " << id << " is trying to lock the forks." << std::endl;

  std::scoped_lock lock(left_fork_->mutex_, right_fork_->mutex_);

  std::osyncstream(std::cout) << "Philosopher " << id << " is eating" << std::endl;
}

void Philosopher::think() const {
  std::osyncstream(std::cout) << "Philosopher " << id << " is thinking..." << std::endl;

  int duration = 1000 + (std::rand() % 4000);
  std::this_thread::sleep_for(std::chrono::milliseconds(duration));
}

}