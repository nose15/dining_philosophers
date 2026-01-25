//
// Created by lukasz on 17.01.26.
//

#ifndef DINING_PHILOSOPHERS_SRC_CORE_INCLUDE_CORE_DININGPHILOSOPHERS_HPP_
#define DINING_PHILOSOPHERS_SRC_CORE_INCLUDE_CORE_DININGPHILOSOPHERS_HPP_

#include <shared_resources/Fork.hpp>

#include <philosophers/IEatMethod.hpp>

#include <cstdint>
#include <vector>
#include <memory>

namespace core {

class DiningPhilosophers {
 private:
  uint32_t philosopher_count_;
  std::vector<shared_resources::Fork> forks;

  void initializeForks(uint32_t count);

 public:
  explicit DiningPhilosophers(uint32_t philosopher_count);
  void run() const;
};

}

#endif //DINING_PHILOSOPHERS_SRC_CORE_INCLUDE_CORE_DININGPHILOSOPHERS_HPP_
