//
// Created by lukasz on 25.01.26.
//

#ifndef IEATMETHOD_HPP
#define IEATMETHOD_HPP

#include <shared_resources/Fork.hpp>

#include "State.hpp"

namespace philosophers {
  class IEatMethod {
    public:
      virtual ~IEatMethod() = default;
      virtual void operator()(
        const shared_resources::Fork& left_fork,
        const shared_resources::Fork& right_fork,
        std::atomic<State>& state) = 0;
  };
}

#endif //IEATMETHOD_HPP
