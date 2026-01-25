//
// Created by lukasz on 25.01.26.
//

#ifndef ARBITRATORCALLEATMETHOD_HPP
#define ARBITRATORCALLEATMETHOD_HPP

#include <philosophers/IEatMethod.hpp>

#include <shared_resources/ForkArbitrator.hpp>

namespace philosophers {

class ArbitratorCallEatMethod final : public IEatMethod {
  private:
    const shared_resources::ForkArbitrator& fork_arbitrator_;

  public:
    explicit ArbitratorCallEatMethod(
      const shared_resources::ForkArbitrator& fork_arbitrator);
    ~ArbitratorCallEatMethod() override = default;
    void operator()(const shared_resources::Fork& left_fork, const shared_resources::Fork& right_fork, std::atomic<State>& state) override;
};

}

#endif //ARBITRATORCALLEATMETHOD_HPP
