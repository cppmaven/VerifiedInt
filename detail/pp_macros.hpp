//               Copyright Ben Robinson 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef PP_MACROS_HPP
#define PP_MACROS_HPP

namespace boost {
namespace detail {
template<class T> struct remove_parentheses_helper
{
    typedef T type;
};

template<class T> struct remove_parentheses_helper<void (T)>
{
    typedef T type;
};

} // namespace detail
} // namespace boost

#define REMOVE_PARENTHESIS(type_possible_parens) \
    boost::detail::remove_parentheses_helper<void (type_possible_parens)>::type

#define TYPEDEF_AWAY_COMMAS(type_possible_commas, type_no_commas) \
    typedef typename REMOVE_PARENTHESIS(type_possible_commas) type_no_commas

#endif // PP_MACROS_HPP
