//
// Created by lukasz on 17.01.26.
//

#ifndef DINING_PHILOSOPHERS_SRC_PHILOSOPHER_INCLUDE_PHILOSOPHER_PHILOSOPHER_HPP_
#define DINING_PHILOSOPHERS_SRC_PHILOSOPHER_INCLUDE_PHILOSOPHER_PHILOSOPHER_HPP_

#include <core/Fork.hpp>
#include <memory>

namespace core {

class Philosopher {
 private:
  uint32_t id;

  std::shared_ptr<Fork> left_fork_;
  std::shared_ptr<Fork> right_fork_;

  void eat();
  void think() const;

 public:
  Philosopher(uint32_t id, std::shared_ptr<Fork> left_fork, std::shared_ptr<Fork> right_fork);

  void run();

};

}

#endif //DINING_PHILOSOPHERS_SRC_PHILOSOPHER_INCLUDE_PHILOSOPHER_PHILOSOPHER_HPP_
