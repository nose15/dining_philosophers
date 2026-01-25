//
// Created by lukasz on 25.01.26.
//

#ifndef FORKARBITRATOR_HPP
#define FORKARBITRATOR_HPP


#include <shared_resources/Fork.hpp>

namespace shared_resources {

class ForkArbitrator {
  public:
    mutable std::mutex mutex_;
};

}

#endif //FORKARBITRATOR_HPP
