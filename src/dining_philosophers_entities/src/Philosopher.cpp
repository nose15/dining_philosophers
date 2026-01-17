//
// Created by lukasz on 17.01.26.
//

#include <dining_philosophers_entities/Philosopher.hpp>

#include <iostream>
#include <thread>
#include <chrono>


namespace dining_philosophers_entities {

void Philosopher::run() {
  for (int i = 0; i < 10; i++) {
    std::cout << "Running" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

}