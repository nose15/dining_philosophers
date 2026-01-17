#include <dining_philosophers_entities/Philosopher.hpp>

#include <iostream>
#include <thread>


int main() {
  auto philosopher = std::make_unique<dining_philosophers_entities::Philosopher>();

  auto philThread = std::thread(&dining_philosophers_entities::Philosopher::run, &(*philosopher));

  philThread.join();

  std::cout << "Hello, World!" << std::endl;
  return 0;
}
