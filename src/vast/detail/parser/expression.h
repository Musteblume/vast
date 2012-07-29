#ifndef VAST_DETAIL_PARSER_EXPRESSION_H
#define VAST_DETAIL_PARSER_EXPRESSION_H

// Improves compile times significantly at the cost of predefining terminals.
#define BOOST_SPIRIT_NO_PREDEFINED_TERMINALS

#include <boost/spirit/include/qi.hpp>
#include <ze/parser/value.h>
#include "vast/detail/ast.h"
#include "vast/util/parser/error_handler.h"
#include "vast/util/parser/skipper.h"

namespace vast {
namespace detail {
namespace parser {

using util::parser::skipper;
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template <typename Iterator>
struct expression : qi::grammar<Iterator, ast::expression(), skipper<Iterator>>
{
    expression(util::parser::error_handler<Iterator>& error_handler);

    qi::rule<Iterator, ast::expression(), skipper<Iterator>>
        expr;

    qi::rule<Iterator, ast::expr_operand(), skipper<Iterator>>
        unary, primary;

    qi::rule<Iterator, std::string(), skipper<Iterator>>
        identifier;

    qi::symbols<char, ast::expr_operator>
        unary_op, binary_op;

    ze::parser::value<Iterator> val;
};

} // namespace ast
} // namespace detail
} // namespace vast

#endif