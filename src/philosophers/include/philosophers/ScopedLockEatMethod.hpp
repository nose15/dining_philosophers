//
// Created by lukasz on 25.01.26.
//

#ifndef SCOPEDLOCKEATMETHOD_HPP
#define SCOPEDLOCKEATMETHOD_HPP

#include <philosophers/IEatMethod.hpp>

#include <shared_resources/Fork.hpp>

namespace philosophers {

class ScopedLockEatMethod final : public IEatMethod {
  public:
    ~ScopedLockEatMethod() override = default;
    void operator()(const shared_resources::Fork& left_fork, const shared_resources::Fork& right_fork, std::atomic<State>& state) override;
};

}

#endif //SCOPEDLOCKEATMETHOD_HPP
