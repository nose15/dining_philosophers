//
// Created by lukasz on 25.01.26.
//

#ifndef BACKOFFEATMETHOD_HPP
#define BACKOFFEATMETHOD_HPP

#include <philosophers/IEatMethod.hpp>

#include <shared_resources/Fork.hpp>

namespace philosophers {

class HierarchyEatMethod final : public IEatMethod {
  public:
    ~HierarchyEatMethod() override = default;
    void operator()(const shared_resources::Fork& left_fork, const shared_resources::Fork& right_fork) override;
};

}

#endif //BACKOFFEATMETHOD_HPP
