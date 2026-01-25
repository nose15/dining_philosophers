#include <core/DiningPhilosophers.hpp>

#include "philosophers/NoSyncEatMethod.hpp"

int main() {
  const auto dining_philosophers = core::DiningPhilosophers(10);
  dining_philosophers.run();
}
