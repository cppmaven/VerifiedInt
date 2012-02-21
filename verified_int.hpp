
//               Copyright Ben Robinson 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef VERIFIED_INT_HPP
#define VERIFIED_INT_HPP

#include <boost/cstdint.hpp>
#include "metaassert.hpp"
#include "verified_int_policies.hpp"
#include "detail/verified_int_overflow_detection.hpp"

namespace boost {

template <typename T, template <typename T> class P>
class verified_int {
public:
    // Default constructor.
    verified_int() : value_(0) {
    }

    // Copy constructor (to avoid conversion to T, then conversion constructor).
    verified_int(verified_int const & verified) :
        value_(verified.value_) {
    }
    // Conversion constructors
    #define GEN_CONVERSION_CONSTRUCTOR(TYPE) \
    verified_int(TYPE const value) : \
        value_(P<T>::verify_assignment(value)) { \
    }
    GEN_CONVERSION_CONSTRUCTOR(uint8_t)
    GEN_CONVERSION_CONSTRUCTOR(uint16_t)
    GEN_CONVERSION_CONSTRUCTOR(uint32_t)
    GEN_CONVERSION_CONSTRUCTOR(uint64_t)
    GEN_CONVERSION_CONSTRUCTOR(int8_t)
    GEN_CONVERSION_CONSTRUCTOR(int16_t)
    GEN_CONVERSION_CONSTRUCTOR(int32_t)
    GEN_CONVERSION_CONSTRUCTOR(int64_t)
    #undef GEN_CONVERSION_CONSTRUCTOR
    // Prevent implicit conversion from one verified type to another
    // on assignment via operator T() on the right-hand-side.
    template <class R>
    verified_int(R const prevented) {
        BOOST_METAASSERT_MSG(sizeof(R) == 0, CANNOT_CONSTRUCT_FROM_A_DIFFERENTLY_TYPED_VERIFIED_INT, (R));
    }

    // Conversion back to a builtin type
    operator T() const {
        return value_;
    }

    // Copy assignment operators
    verified_int& operator=(verified_int const verified) {
        value_ = verified.value_;
        return *this;
    }
    #define GEN_COPY_ASSIGNMENT(TYPE) \
    verified_int& operator=(TYPE const right) { \
        value_ = P<T>::verify_assignment(right); \
        return *this; \
    }
    GEN_COPY_ASSIGNMENT(uint8_t)
    GEN_COPY_ASSIGNMENT(uint16_t)
    GEN_COPY_ASSIGNMENT(uint32_t)
    GEN_COPY_ASSIGNMENT(uint64_t)
    GEN_COPY_ASSIGNMENT(int8_t)
    GEN_COPY_ASSIGNMENT(int16_t)
    GEN_COPY_ASSIGNMENT(int32_t)
    GEN_COPY_ASSIGNMENT(int64_t)
    #undef GEN_COPY_ASSIGNMENT
    // Prevent implicit conversion from one verified type to another
    // on assignment via operator T() on the right-hand-side.
    template <class R>
    verified_int& operator=(R const prevented) {
        BOOST_METAASSERT_MSG(sizeof(R) == 0, CANNOT_ASSIGN_DIFFERENTLY_TYPED_VERIFIED_INTS, (R));
        return *this;
    }

    // Prefix increment operator.
    verified_int & operator++() {
        *this += 1;
        return *this;
    }

    // Postfix increment operator.
    verified_int const operator++(int postfix_signature) {
        (void)postfix_signature;
        verified_int before_increment(*this);
        *this += 1;
        return before_increment;
    }

    // Unary addition operator.
    verified_int const operator+() {
        verified_int copied_int(this->value_);
        return copied_int;
    }

    // Prefix decrement operator.
    verified_int & operator--() {
        *this -= 1;
        return *this;
    }

    // Postfix decrement operator.
    verified_int const operator--(int postfix_signature) {
        (void)postfix_signature;
        verified_int before_decrement(*this);
        *this -= 1;
        return before_decrement;
    }

    verified_int const operator-() {
        verified_int negated_int(-this->value_);
        return negated_int;
    }

    #define GEN_OPERATOR_PLUS_EQUALS(TYPE, RHS) \
    verified_int& operator+=(TYPE const right) { \
        value_ = P<T>::verify_addition(value_, RHS); \
        return *this; \
    }
    GEN_OPERATOR_PLUS_EQUALS(verified_int, right.value_)
    GEN_OPERATOR_PLUS_EQUALS(uint8_t, right)
    GEN_OPERATOR_PLUS_EQUALS(uint16_t, right)
    GEN_OPERATOR_PLUS_EQUALS(uint32_t, right)
    GEN_OPERATOR_PLUS_EQUALS(uint64_t, right)
    GEN_OPERATOR_PLUS_EQUALS(int8_t, right)
    GEN_OPERATOR_PLUS_EQUALS(int16_t, right)
    GEN_OPERATOR_PLUS_EQUALS(int32_t, right)
    GEN_OPERATOR_PLUS_EQUALS(int64_t, right)
    #undef GEN_OPERATOR_PLUS_EQUALS

    #define GEN_OPERATOR_MINUS_EQUALS(TYPE, RHS) \
    verified_int& operator-=(TYPE const right) { \
        value_ = P<T>::verify_subtraction(value_, RHS); \
        return *this; \
    }
    GEN_OPERATOR_MINUS_EQUALS(verified_int, right.value_)
    GEN_OPERATOR_MINUS_EQUALS(uint8_t, right)
    GEN_OPERATOR_MINUS_EQUALS(uint16_t, right)
    GEN_OPERATOR_MINUS_EQUALS(uint32_t, right)
    GEN_OPERATOR_MINUS_EQUALS(uint64_t, right)
    GEN_OPERATOR_MINUS_EQUALS(int8_t, right)
    GEN_OPERATOR_MINUS_EQUALS(int16_t, right)
    GEN_OPERATOR_MINUS_EQUALS(int32_t, right)
    GEN_OPERATOR_MINUS_EQUALS(int64_t, right)
    #undef GEN_OPERATOR_MINUS_EQUALS

    #define GEN_OPERATOR_TIMES_EQUALS(TYPE, RHS) \
    verified_int& operator*=(TYPE const right) { \
        value_ = P<T>::verify_multiplication(value_, RHS); \
        return *this; \
    }
    GEN_OPERATOR_TIMES_EQUALS(verified_int, right.value_)
    GEN_OPERATOR_TIMES_EQUALS(uint8_t, right)
    GEN_OPERATOR_TIMES_EQUALS(uint16_t, right)
    GEN_OPERATOR_TIMES_EQUALS(uint32_t, right)
    GEN_OPERATOR_TIMES_EQUALS(uint64_t, right)
    GEN_OPERATOR_TIMES_EQUALS(int8_t, right)
    GEN_OPERATOR_TIMES_EQUALS(int16_t, right)
    GEN_OPERATOR_TIMES_EQUALS(int32_t, right)
    GEN_OPERATOR_TIMES_EQUALS(int64_t, right)
    #undef GEN_OPERATOR_TIMES_EQUALS

    #define GEN_OPERATOR_DIVIDE_EQUALS(TYPE, RHS) \
    verified_int& operator/=(TYPE const right) { \
        value_ = P<T>::verify_division(value_, RHS); \
        return *this; \
    }
    GEN_OPERATOR_DIVIDE_EQUALS(verified_int, right.value_)
    GEN_OPERATOR_DIVIDE_EQUALS(uint8_t, right)
    GEN_OPERATOR_DIVIDE_EQUALS(uint16_t, right)
    GEN_OPERATOR_DIVIDE_EQUALS(uint32_t, right)
    GEN_OPERATOR_DIVIDE_EQUALS(uint64_t, right)
    GEN_OPERATOR_DIVIDE_EQUALS(int8_t, right)
    GEN_OPERATOR_DIVIDE_EQUALS(int16_t, right)
    GEN_OPERATOR_DIVIDE_EQUALS(int32_t, right)
    GEN_OPERATOR_DIVIDE_EQUALS(int64_t, right)
    #undef GEN_OPERATOR_DIVIDE_EQUALS

    #define GEN_OPERATOR_MOD_EQUALS(TYPE, RHS) \
    verified_int& operator%=(TYPE const right) { \
        value_ = P<T>::verify_modulus(value_, RHS); \
        return *this; \
    }
    GEN_OPERATOR_MOD_EQUALS(verified_int, right.value_)
    GEN_OPERATOR_MOD_EQUALS(uint8_t, right)
    GEN_OPERATOR_MOD_EQUALS(uint16_t, right)
    GEN_OPERATOR_MOD_EQUALS(uint32_t, right)
    GEN_OPERATOR_MOD_EQUALS(uint64_t, right)
    GEN_OPERATOR_MOD_EQUALS(int8_t, right)
    GEN_OPERATOR_MOD_EQUALS(int16_t, right)
    GEN_OPERATOR_MOD_EQUALS(int32_t, right)
    GEN_OPERATOR_MOD_EQUALS(int64_t, right)
    #undef GEN_OPERATOR_MOD_EQUALS

private:
    T value_;
};

// ***********************************************
// Binary math operators
// ***********************************************

// Performs math on two verified_ints.
// Both must share the same T, xLower, xUpper and P.
#define GEN_BINARY_OPERATORS_VERIFIED_SAME(OPERATOR_MATH, MATH_ASSIGN) \
    template <typename T, template <typename T> class P> \
    verified_int<T, P> OPERATOR_MATH( \
            verified_int<T, P> const & left, \
            verified_int<T, P> const & right) { \
        verified_int<T, P> copied_int(left); \
        copied_int MATH_ASSIGN right; \
        return copied_int; \
    }
GEN_BINARY_OPERATORS_VERIFIED_SAME(operator+, +=)
GEN_BINARY_OPERATORS_VERIFIED_SAME(operator-, -=)
GEN_BINARY_OPERATORS_VERIFIED_SAME(operator*, *=)
GEN_BINARY_OPERATORS_VERIFIED_SAME(operator/, /=)
GEN_BINARY_OPERATORS_VERIFIED_SAME(operator%, %=)
#undef GEN_BINARY_OPERATORS_VERIFIED_SAME

#define GEN_BINARY_OPERATORS_VERIFIED_ON_LEFT(OPERATOR_MATH, MATH_ASSIGN) \
    template <typename L, typename R, template <typename L> class P> \
    verified_int<L, P> OPERATOR_MATH( \
            verified_int<L, P> const & left, \
            R const & right) { \
        verified_int<L, P> copied_int(left); \
        copied_int MATH_ASSIGN right; \
        return copied_int; \
    }
GEN_BINARY_OPERATORS_VERIFIED_ON_LEFT(operator+, +=)
GEN_BINARY_OPERATORS_VERIFIED_ON_LEFT(operator-, -=)
GEN_BINARY_OPERATORS_VERIFIED_ON_LEFT(operator*, *=)
GEN_BINARY_OPERATORS_VERIFIED_ON_LEFT(operator/, /=)
GEN_BINARY_OPERATORS_VERIFIED_ON_LEFT(operator%, %=)
#undef GEN_BINARY_OPERATORS_VERIFIED_ON_LEFT

#define GEN_BINARY_OPERATORS_VERIFIED_ON_RIGHT(OPERATOR_MATH, MATH_ASSIGN) \
    template <typename L, typename R, template <typename R> class P> \
    verified_int<R, P> OPERATOR_MATH( \
             L const & left, \
             verified_int<R, P> const & right) { \
        BOOST_METAASSERT_MSG(sizeof(R) == 0, VERIFIED_INT_PLUS_POD_INT_NOT_SUPPORTED, (R)); \
        return right; \
    }
GEN_BINARY_OPERATORS_VERIFIED_ON_RIGHT(operator+, +=)
GEN_BINARY_OPERATORS_VERIFIED_ON_RIGHT(operator-, -=)
GEN_BINARY_OPERATORS_VERIFIED_ON_RIGHT(operator*, *=)
GEN_BINARY_OPERATORS_VERIFIED_ON_RIGHT(operator/, /=)
GEN_BINARY_OPERATORS_VERIFIED_ON_RIGHT(operator%, %=)
#undef GEN_BINARY_OPERATORS_VERIFIED_ON_RIGHT

// ***********************************************
// Convenience type wrappers
// ***********************************************
template <typename T>
struct throw_int {
    typedef verified_int<T, throw_overflow> type;
};

template <typename T>
struct assert_int {
    typedef verified_int<T, assert_overflow> type;
};

template <typename T>
struct saturate_int {
    typedef verified_int<T, saturate_overflow> type;
};

template <typename T>
struct nan_int {
    typedef verified_int<T, nan_overflow> type;
};

// ***********************************************
// Even simpler usable types.  These can also be
// used for metaassert unittests.
// ***********************************************
typedef throw_int<uint8_t>::type  verified_uint8_t;
typedef throw_int<uint16_t>::type verified_uint16_t;
typedef throw_int<uint32_t>::type verified_uint32_t;
typedef throw_int<uint64_t>::type verified_uint64_t;
typedef throw_int<int8_t>::type   verified_int8_t;
typedef throw_int<int16_t>::type  verified_int16_t;
typedef throw_int<int32_t>::type  verified_int32_t;
typedef throw_int<int64_t>::type  verified_int64_t;

typedef throw_int<unsigned int>::type verified_uint_t;
typedef throw_int<signed int>::type   verified_int_t;

} // namespace boost

#endif // VERIFIED_INT_HPP
