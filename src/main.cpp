#include <core/DiningPhilosophers.hpp>

int main() {
  auto dining_philosophers = core::DiningPhilosophers(10);
  dining_philosophers.run();
}
