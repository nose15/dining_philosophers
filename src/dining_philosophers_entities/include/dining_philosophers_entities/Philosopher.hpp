//
// Created by lukasz on 17.01.26.
//

#ifndef DINING_PHILOSOPHERS_SRC_PHILOSOPHER_INCLUDE_PHILOSOPHER_PHILOSOPHER_HPP_
#define DINING_PHILOSOPHERS_SRC_PHILOSOPHER_INCLUDE_PHILOSOPHER_PHILOSOPHER_HPP_

#include <dining_philosophers_entities/Fork.hpp>
#include <memory>

namespace dining_philosophers_entities {

class Philosopher {
 private:
  std::shared_ptr<Fork> leftFork;
  std::shared_ptr<Fork> rightFork;

 public:
  void run();

};

}

#endif //DINING_PHILOSOPHERS_SRC_PHILOSOPHER_INCLUDE_PHILOSOPHER_PHILOSOPHER_HPP_
