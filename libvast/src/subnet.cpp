#include <tuple>

#include "vast/concept/printable/to_string.hpp"
#include "vast/concept/printable/vast/subnet.hpp"
#include "vast/json.hpp"
#include "vast/subnet.hpp"

namespace vast {

subnet::subnet() : length_{0u} {
}

subnet::subnet(address addr, uint8_t length)
  : network_{std::move(addr)}, length_{length} {
  if (!initialize()) {
    network_ = address{};
    length_ = 0;
  }
}

bool subnet::contains(address const& addr) const {
  return addr.compare(network_, length_);
}

bool subnet::contains(subnet const& other) const {
  return length_ <= other.length_ && contains(other.network_);
}

address const& subnet::network() const {
  return network_;
}

uint8_t subnet::length() const {
  return network_.is_v4() ? length_ - 96 : length_;
}

bool subnet::initialize() {
  if (network_.is_v4()) {
    if (length_ > 32)
      return false;
    length_ += 96;
  } else if (length_ > 128) {
    return false;
  }
  network_.mask(length_);
  return true;
}

bool operator==(subnet const& x, subnet const& y) {
  return x.network_ == y.network_ && x.length_ == y.length_;
}

bool operator<(subnet const& x, subnet const& y) {
  return std::tie(x.network_, x.length_) < std::tie(y.network_, y.length_);
}

bool convert(subnet const& sn, json& j) {
  j = to_string(sn);
  return true;
}

} // namespace vast
