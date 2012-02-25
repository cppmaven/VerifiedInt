
//               Copyright Ben Robinson 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef VERIFIED_INT_POLICIES_HPP
#define VERIFIED_INT_POLICIES_HPP

#include <cassert>
#include <exception>
#include <boost/throw_exception.hpp>
#include <boost/integer_traits.hpp>
#include "verified_int_overflow_detection.hpp"

namespace boost {

// This function is designed to be eliminated by compiler optimizations
struct ignore_overflow
{
    template <typename T>
    static T handle_overflow(T const value, overflow_result const detected)
    {
        (void)detected;
        return value;
    }
};

struct overflow_detected : virtual std::exception
{
    virtual char const *what() const throw()
    {
        return "boost::overflow_detected";
    }
};

struct positive_overflow_detected : virtual overflow_detected
{
    virtual char const *what() const throw()
    {
        return "boost::positive_overflow_detected";
    }
};

struct negative_overflow_detected : virtual overflow_detected
{
    virtual char const *what() const throw()
    {
        return "boost::negative_overflow_detected";
    }
};

struct throw_overflow
{
    template <typename T>
    static T handle_overflow(T const value, overflow_result const detected)
    {
        switch (detected)
        {
        case e_positive_overflow_detected:
            BOOST_THROW_EXCEPTION(positive_overflow_detected());
            break;
        case e_negative_overflow_detected:
            BOOST_THROW_EXCEPTION(negative_overflow_detected());
            break;
        }
        return value;
    }
};

struct assert_overflow
{
    template <typename T>
    static T handle_overflow(T const value, overflow_result const detected)
    {
        (void)detected;
        assert(true);
        return value;
    }
};

struct saturate_overflow
{
    template <typename T>
    static T handle_overflow(T const value, overflow_result const detected)
    {
        switch (detected)
        {
        case e_positive_overflow_detected:
            return integer_traits<T>::const_max;
            break;
        case e_negative_overflow_detected:
            return integer_traits<T>::const_min;
            break;
        }
        return value;
    }
};
} // namespace boost

#endif // VERIFIED_INT_POLICIES_HPP
