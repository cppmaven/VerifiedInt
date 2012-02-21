
//               Copyright Ben Robinson 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MAIN defined
#define BOOST_METAASSERT_UNITTEST defined

#include <boost/test/unit_test.hpp>
#include <boost/integer_traits.hpp>
#include <iostream>
#include "verified_int.hpp"

namespace {

using boost::integer_traits;
using boost::metaassert_exception;

using boost::verified_uint8_t;
using boost::verified_uint16_t;
using boost::verified_uint32_t;
using boost::verified_uint64_t;
using boost::verified_int8_t;
using boost::verified_int16_t;
using boost::verified_int32_t;
using boost::verified_int64_t;

static verified_uint8_t const static_testA(5U);
static verified_uint8_t const static_testB(7U);
static verified_uint8_t const static_test2(static_testA + static_testB);
static verified_uint8_t const static_test3(static_testA + 7U);
static verified_uint8_t const static_test4(5U + 7U);
static verified_uint8_t const static_test5 = static_testA + static_testB;
static verified_uint8_t const static_test6 = static_testA + 7U;
static verified_uint8_t const static_test7 = verified_uint8_t(5U + 7U); // should explicit cast be required?
static verified_uint8_t const static_test8 = 5U + 7U;

BOOST_AUTO_TEST_CASE(test_invalid_assignment) { \
    uint16_t pod = 0;
    verified_uint16_t verified(0);
    verified_uint32_t lhs;
    lhs = pod;
    verified_uint16_t verifiedA = 0;
    BOOST_CHECK_THROW( verified_uint16_t verifiedB = verified_uint32_t(0);, metaassert_exception ); // This line should fail to compile.
    BOOST_CHECK_THROW( lhs = verified;, metaassert_exception ); // This line should fail to compile.
    BOOST_CHECK_THROW( verified_uint32_t lhs2 = verified;, metaassert_exception ); // This line should fail to compile.
    BOOST_CHECK_THROW( verifiedA = 6 + verifiedA;, metaassert_exception ); // This line should fail to compile.
//    BOOST_CHECK_THROW( verified_uint32_t lhs2 = verified;, boost::overflow_detected ); // This line should fail to compile.
//    BOOST_CHECK_THROW( verifiedA = 6 + verifiedA;, boost::overflow_detected ); // This line should fail to compile.
}
} // namespace anonymous
