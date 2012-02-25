
//               Copyright Ben Robinson 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MAIN defined
#define BOOST_METAASSERT_UNITTEST defined

#include <boost/test/unit_test.hpp>
#include <boost/integer_traits.hpp>
#include <verified_int.hpp>
#include <iostream>

namespace {

using boost::integer_traits;

using boost::verified_uint8_t;
using boost::verified_uint16_t;
using boost::verified_uint32_t;
using boost::verified_uint64_t;
using boost::verified_int8_t;
using boost::verified_int16_t;
using boost::verified_int32_t;
using boost::verified_int64_t;

#define GEN_ADDITION_TEST_CASES(TYPE) \
BOOST_AUTO_TEST_CASE(test_addition_verified_##TYPE) { \
    verified_##TYPE value; \
    verified_##TYPE verified_one(1); \
    TYPE temp; \
    \
    /* Check postfix increment */ \
    value = integer_traits<TYPE>::const_min; \
    BOOST_CHECK_NO_THROW( temp = value++; ); \
    BOOST_CHECK_EQUAL(integer_traits<TYPE>::const_min, temp); \
    value = integer_traits<TYPE>::const_max; \
    BOOST_CHECK_THROW( value++, boost::overflow_detected ); \
    \
    /* Check prefix increment */ \
    value = integer_traits<TYPE>::const_min; \
    BOOST_CHECK_NO_THROW( temp = ++value; ); \
    BOOST_CHECK_EQUAL(integer_traits<TYPE>::const_min + 1, temp); \
    \
    value = integer_traits<TYPE>::const_max; \
    BOOST_CHECK_THROW( ++value, boost::overflow_detected ); \
    \
    /* Check += operator */ \
    value = integer_traits<TYPE>::const_min; \
    BOOST_CHECK_NO_THROW( value += 1; ); \
    BOOST_CHECK_EQUAL(integer_traits<TYPE>::const_min + 1, value); \
    \
    value = integer_traits<TYPE>::const_max; \
    BOOST_CHECK_THROW( value += 1, boost::overflow_detected ); \
    \
    /* Check binary + operator with integer */ \
    value = integer_traits<TYPE>::const_min; \
    BOOST_CHECK_NO_THROW( value = value + 1; ); \
    BOOST_CHECK_EQUAL(integer_traits<TYPE>::const_min + 1, value); \
    \
    value = integer_traits<TYPE>::const_max; \
    BOOST_CHECK_THROW( value = value + 1, boost::overflow_detected ); \
    \
    /* Check binary + operator with identical verified_int */ \
    value = integer_traits<TYPE>::const_min; \
    BOOST_CHECK_NO_THROW( value = value + verified_one; ); \
    BOOST_CHECK_EQUAL(integer_traits<TYPE>::const_min + 1, value); \
    \
    value = integer_traits<TYPE>::const_max; \
    BOOST_CHECK_THROW( value = value + verified_one, boost::overflow_detected ); \
}
GEN_ADDITION_TEST_CASES(uint8_t)
GEN_ADDITION_TEST_CASES(uint16_t)
GEN_ADDITION_TEST_CASES(uint32_t)
GEN_ADDITION_TEST_CASES(uint64_t)
GEN_ADDITION_TEST_CASES(int8_t)
GEN_ADDITION_TEST_CASES(int16_t)
GEN_ADDITION_TEST_CASES(int32_t)
GEN_ADDITION_TEST_CASES(int64_t)
#undef GEN_ADDITION_TEST_CASES
} // namespace anonymous
