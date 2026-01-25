#include <core/DiningPhilosophers.hpp>

#include <philosophers/NoSyncEatMethod.hpp>
#include <iostream>

// TODO: Take this testing out of here
int main() {
  uint32_t counts[7] = {5, 10, 20, 50, 100, 200, 500};

  for (unsigned int count : counts) {
    std::cout << count;
    const auto dining_philosophers = core::DiningPhilosophers(count);
    dining_philosophers.run();
    std::cout << std::endl << std::endl;
  }
}
