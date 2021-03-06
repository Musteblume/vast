#ifndef VAST_FORMAT_JSON_HPP
#define VAST_FORMAT_JSON_HPP

#include "vast/json.hpp"
#include "vast/concept/printable/vast/json.hpp"

#include "vast/format/writer.hpp"

namespace vast {
namespace format {
namespace json {

struct event_printer : printer<event_printer> {
  using attribute = event;

  template <class Iterator>
  bool print(Iterator& out, event const& e) const {
    vast::json j;
    return convert(e, j) && printers::json<policy::oneline>.print(out, j);
  }
};

class writer : public format::writer<event_printer>{
public:
  using format::writer<event_printer>::writer;

  char const* name() const {
    return "json-writer";
  }
};

} // namespace csv
} // namespace format
} // namespace vast

#endif


