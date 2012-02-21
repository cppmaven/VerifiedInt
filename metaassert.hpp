//               Copyright Ben Robinson 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef METAASSERT_HPP
#define METAASSERT_HPP

#ifndef BOOST_METAASSERT_UNITTEST
#include <boost/mpl/assert.hpp>
#else // BOOST_METAASSERT_UNITTEST
#include <boost/mpl/assert.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <detail/pp_macros.hpp>
#include <exception>
#include <sstream>
#endif // BOOST_METAASSERT_UNITTEST

#ifndef BOOST_METAASSERT_UNITTEST

// Simply forward to BOOST_MPL_ASSERT_* for maximally informative compiler error messages.
#define BOOST_STATIC_METAASSERT(cond)                    BOOST_STATIC_ASSERT(cond)
#define BOOST_METAASSERT(pred)                           BOOST_MPL_ASSERT(pred)
#define BOOST_METAASSERT_NOT(pred)                       BOOST_MPL_ASSERT_NOT(pred)
#define BOOST_METAASSERT_RELATION(x, rel, y)             BOOST_MPL_ASSERT_RELATION(x, rel, y)
#define BOOST_METAASSERT_MSG(cond, msg, types)           BOOST_MPL_ASSERT_MSG(cond, msg, types)

#define BOOST_STATIC_METAASSERT_EXP(cond, exc)           BOOST_STATIC_ASSERT(cond)
#define BOOST_METAASSERT_EXP(pred, exc)                  BOOST_MPL_ASSERT(pred)
#define BOOST_METAASSERT_NOT_EXP(pred, exc)              BOOST_MPL_ASSERT_NOT(pred)
#define BOOST_METAASSERT_RELATION_EXP(x, rel, y, exc)    BOOST_MPL_ASSERT_RELATION(x, rel, y)
#define BOOST_METAASSERT_MSG_EXP(cond, msg, types, exc)  BOOST_MPL_ASSERT_MSG(cond, msg, types)

#else // BOOST_METAASSERT_UNITTEST

// Permit the compile, and throw a run-time exception instead.
namespace boost
{
    struct metaassert_exception : virtual public std::exception
    {
        metaassert_exception(std::string const & filename, int linenum, std::string const & reason)
            : filename_(filename),
              linenum_(linenum),
              reason_(reason) {} // Set breakpoint on this line to examine the call stack of a failing metaassert.
        virtual ~metaassert_exception() throw () {}
        virtual char const *what() const throw()
        {
            std::stringstream ss; \
            ss << filename_ << ":" << linenum_ << ": metaassert exception: '" << reason_ << "'."; \
            return ss.str().c_str(); \
        }

        std::string filename_;
        int linenum_;
        std::string reason_;
    };
} // namespace boost

// --------------------------------------------------------------
// BOOST_STATIC_METAASSERT and BOOST_STATIC_METAASSERT_EXP
// --------------------------------------------------------------
#define BOOST_STATIC_METAASSERT(cond) \
    BOOST_STATIC_METAASSERT_IMPL(cond, BOOST_MPL_AUX_PP_COUNTER())

#define BOOST_STATIC_METAASSERT_IMPL(cond, counter) \
    BOOST_STATIC_METAASSERT_TYPEDEF_EXCEPTION_PRETTY(cond, counter, BOOST_PP_CAT(metaassert_exception_pretty_on_line_,counter)); \
    BOOST_STATIC_METAASSERT_EXP_IMPL(cond, BOOST_PP_CAT(metaassert_exception_pretty_on_line_,counter), counter)

#define BOOST_STATIC_METAASSERT_EXP(cond, exc) \
    BOOST_STATIC_METAASSERT_EXP_IMPL(cond, exc, BOOST_MPL_AUX_PP_COUNTER())

#define BOOST_STATIC_METAASSERT_EXP_IMPL(cond, exc, counter) \
    BOOST_STATIC_METAASSERT_TYPEDEF_CONDITIONAL(cond, exc, BOOST_PP_CAT(metaassert_cond_type_on_line_,counter)); \
    BOOST_PP_CAT(metaassert_cond_type_on_line_,counter) BOOST_PP_CAT(metaassert_cond_instance_on_line_,BOOST_MPL_AUX_PP_COUNTER())

#define BOOST_STATIC_METAASSERT_TYPEDEF_EXCEPTION_PRETTY(cond, counter, name) \
    typedef struct BOOST_PP_CAT(struct_,name) : virtual public metaassert_exception \
    { \
        BOOST_PP_CAT(struct_,name)() \
        : metaassert_exception(__FILE__, counter, BOOST_PP_STRINGIZE((cond) != true)) {} \
    } name

#define BOOST_STATIC_METAASSERT_TYPEDEF_CONDITIONAL(cond, exc, name) \
    typedef struct BOOST_PP_CAT(struct_,name) \
    { \
        BOOST_PP_CAT(struct_,name)() \
        { \
            if ((cond) != true) { \
                throw exc(); \
            } \
        } \
    } name

// --------------------------------------------------------------
// BOOST_METAASSERT and BOOST_METAASSERT_EXP
// --------------------------------------------------------------
#define BOOST_METAASSERT(pred) \
    BOOST_METAASSERT_IMPL(pred, BOOST_MPL_AUX_PP_COUNTER())

#define BOOST_METAASSERT_IMPL(pred, counter) \
    BOOST_METAASSERT_TYPEDEF_EXCEPTION_PRETTY(pred, counter, BOOST_PP_CAT(metaassert_exception_pretty_on_line_,counter)); \
    BOOST_METAASSERT_EXP_IMPL(pred, BOOST_PP_CAT(metaassert_exception_pretty_on_line_,counter), counter)

#define BOOST_METAASSERT_EXP(pred, exc) \
    BOOST_METAASSERT_EXP_IMPL(pred, exc, BOOST_MPL_AUX_PP_COUNTER())

#define BOOST_METAASSERT_EXP_IMPL(pred, exc, counter) \
    BOOST_METAASSERT_TYPEDEF_CONDITIONAL(pred, exc, BOOST_PP_CAT(metaassert_cond_type_on_line_,counter)); \
    BOOST_PP_CAT(metaassert_cond_type_on_line_,counter) BOOST_PP_CAT(metaassert_cond_instance_on_line_,BOOST_MPL_AUX_PP_COUNTER())

#define BOOST_METAASSERT_TYPEDEF_EXCEPTION_PRETTY(pred, counter, name) \
    typedef struct BOOST_PP_CAT(struct_,name) : virtual public metaassert_exception \
    { \
        BOOST_PP_CAT(struct_,name)() \
        : metaassert_exception(__FILE__, counter, BOOST_PP_STRINGIZE(pred::type::value != true)) {} \
    } name

#define BOOST_METAASSERT_TYPEDEF_CONDITIONAL(pred, exc, name) \
    typedef struct BOOST_PP_CAT(struct_,name) \
    { \
        BOOST_PP_CAT(struct_,name)() \
        { \
            if (REMOVE_PARENTHESIS(pred)::type::value != true) { \
                throw exc(); \
            } \
        } \
    } name

// --------------------------------------------------------------
// BOOST_METAASSERT_NOT and BOOST_METAASSERT_NOT_EXP
// --------------------------------------------------------------
#define BOOST_METAASSERT_NOT(pred) \
    BOOST_METAASSERT_NOT_IMPL(pred, BOOST_MPL_AUX_PP_COUNTER())

#define BOOST_METAASSERT_NOT_IMPL(pred, counter) \
    BOOST_METAASSERT_NOT_TYPEDEF_EXCEPTION_PRETTY(pred, counter, BOOST_PP_CAT(metaassert_exception_pretty_on_line_,counter)); \
    BOOST_METAASSERT_NOT_EXP_IMPL(pred, BOOST_PP_CAT(metaassert_exception_pretty_on_line_,counter), counter)

#define BOOST_METAASSERT_NOT_EXP(pred, exc) \
    BOOST_METAASSERT_NOT_EXP_IMPL(pred, exc, BOOST_MPL_AUX_PP_COUNTER())

#define BOOST_METAASSERT_NOT_EXP_IMPL(pred, exc, counter) \
    BOOST_METAASSERT_NOT_TYPEDEF_CONDITIONAL(pred, exc, BOOST_PP_CAT(metaassert_cond_type_on_line_,counter)); \
    BOOST_PP_CAT(metaassert_cond_type_on_line_,counter) BOOST_PP_CAT(metaassert_cond_instance_on_line_,BOOST_MPL_AUX_PP_COUNTER())

#define BOOST_METAASSERT_NOT_TYPEDEF_EXCEPTION_PRETTY(pred, counter, name) \
    typedef struct BOOST_PP_CAT(struct_,name) : virtual public metaassert_exception \
    { \
        BOOST_PP_CAT(struct_,name)() \
        : metaassert_exception(__FILE__, counter, BOOST_PP_STRINGIZE(mpl::not_<typename pred>::type::value != true)) {} \
    } name

#define BOOST_METAASSERT_NOT_TYPEDEF_CONDITIONAL(pred, exc, name) \
    typedef struct BOOST_PP_CAT(struct_,name) \
    { \
        BOOST_PP_CAT(struct_,name)() \
        { \
            if (mpl::not_<typename REMOVE_PARENTHESIS(pred)>::type::value != true) { \
                throw exc(); \
            } \
        } \
    } name

// --------------------------------------------------------------
// BOOST_METAASSERT_RELATION and BOOST_METAASSERT_RELATION_EXP
// --------------------------------------------------------------
#define BOOST_METAASSERT_RELATION(xx, rel, yy) \
    BOOST_METAASSERT_RELATION_IMPL(xx, rel, yy, BOOST_MPL_AUX_PP_COUNTER())

#define BOOST_METAASSERT_RELATION_IMPL(xx, rel, yy, counter) \
    BOOST_METAASSERT_RELATION_TYPEDEF_EXCEPTION_PRETTY(xx, rel, yy, counter, BOOST_PP_CAT(metaassert_exception_pretty_on_line_,counter)); \
    BOOST_METAASSERT_RELATION_EXP_IMPL(xx, rel, yy, BOOST_PP_CAT(metaassert_exception_pretty_on_line_,counter), counter)

#define BOOST_METAASSERT_RELATION_EXP(xx, rel, yy, exc) \
    BOOST_METAASSERT_RELATION_EXP_IMPL(xx, rel, yy, exc, BOOST_MPL_AUX_PP_COUNTER())

#define BOOST_METAASSERT_RELATION_EXP_IMPL(xx, rel, yy, exc, counter) \
    BOOST_METAASSERT_RELATION_TYPEDEF_CONDITIONAL(xx, rel, yy, exc, BOOST_PP_CAT(metaassert_cond_type_on_line_,counter)); \
    BOOST_PP_CAT(metaassert_cond_type_on_line_,counter) BOOST_PP_CAT(metaassert_cond_instance_on_line_,BOOST_MPL_AUX_PP_COUNTER())

#define BOOST_METAASSERT_RELATION_TYPEDEF_EXCEPTION_PRETTY(xx, rel, yy, counter, name) \
    typedef struct BOOST_PP_CAT(struct_,name) : virtual public metaassert_exception \
    { \
        BOOST_PP_CAT(struct_,name)() \
        : metaassert_exception(__FILE__, counter, BOOST_PP_STRINGIZE((xx rel yy) != true)) {} \
    } name

#define BOOST_METAASSERT_RELATION_TYPEDEF_CONDITIONAL(xx, rel, yy, exc, name) \
    typedef struct BOOST_PP_CAT(struct_,name) \
    { \
        BOOST_PP_CAT(struct_,name)() \
        { \
            if ((xx rel yy) != true) { \
                throw exc(); \
            } \
        } \
    } name

// --------------------------------------------------------------
// BOOST_METAASSERT_MSG and BOOST_METAASSERT_MSG_EXP
// --------------------------------------------------------------
#define BOOST_METAASSERT_MSG(cond, msg, types) \
    BOOST_METAASSERT_MSG_IMPL(cond, msg, types, BOOST_MPL_AUX_PP_COUNTER())

#define BOOST_METAASSERT_MSG_IMPL(cond, msg, types, counter) \
    BOOST_METAASSERT_MSG_TYPEDEF_EXCEPTION_PRETTY(cond, msg, types, counter, BOOST_PP_CAT(metaassert_exception_pretty_on_line_,counter)); \
    BOOST_METAASSERT_MSG_EXP_IMPL(cond, msg, types, BOOST_PP_CAT(metaassert_exception_pretty_on_line_,counter), counter)

#define BOOST_METAASSERT_MSG_EXP(cond, msg, types, exc) \
    BOOST_METAASSERT_MSG_EXP_IMPL(cond, msg, types, exc, BOOST_MPL_AUX_PP_COUNTER())

#define BOOST_METAASSERT_MSG_EXP_IMPL(cond, msg, types, exc, counter) \
    BOOST_METAASSERT_MSG_TYPEDEF_CONDITIONAL(cond, exc, msg); \
    msg BOOST_PP_CAT(metaassert_cond_instance_on_line_,BOOST_MPL_AUX_PP_COUNTER())

#define BOOST_METAASSERT_MSG_TYPEDEF_EXCEPTION_PRETTY(cond, msg, types, counter, name) \
    typedef struct BOOST_PP_CAT(struct_,name) : virtual public metaassert_exception \
    { \
        BOOST_PP_CAT(struct_,name)() \
        : metaassert_exception(__FILE__, counter, BOOST_PP_STRINGIZE(msg)) {} \
    } name

#define BOOST_METAASSERT_MSG_TYPEDEF_CONDITIONAL(cond, exc, name) \
    typedef struct BOOST_PP_CAT(struct_,name) \
    { \
        BOOST_PP_CAT(struct_,name)() \
        { \
            if ((cond) != true) { \
                throw exc(); \
            } \
        } \
    } name

#endif // BOOST_METAASSERT_UNITTEST

#endif // METAASSERT_HPP
