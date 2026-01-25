//
// Created by lukasz on 25.01.26.
//

#include <shared_resources/Fork.hpp>

namespace shared_resources {

Fork::Fork(const Fork &other) {
  this->id_.store(other.id_);
}

Fork::Fork(Fork &&other) noexcept {
  this->id_.store(other.id_);
}

Fork::Fork(const uint32_t id) {
  id_ = id;
}

}