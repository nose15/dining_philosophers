//
// Created by lukasz on 25.01.26.
//

#ifndef NOSYNCEATMETHOD_HPP
#define NOSYNCEATMETHOD_HPP

#include <philosophers/IEatMethod.hpp>

#include <shared_resources/Fork.hpp>

namespace philosophers {

class NoSyncEatMethod final : public IEatMethod {
  public:
    ~NoSyncEatMethod() override = default;
    void operator()(const shared_resources::Fork& left_fork, const shared_resources::Fork& right_fork) override;
};

}

#endif //NOSYNCEATMETHOD_HPP
