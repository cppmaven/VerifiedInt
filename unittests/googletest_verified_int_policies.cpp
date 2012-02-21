
//               Copyright Ben Robinson 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_METAASSERT_UNITTEST defined

#include <testsystem.hpp>
#include <stringutils.hpp>
#include <boost/integer_traits.hpp>
#include "verified_int.hpp"

namespace {

using boost::integer_traits;
using boost::saturate_int;
using boost::verified_int;
using boost::nan_overflow;
using boost::saturate_overflow;

TEST(verified_int_TDD, Conversion) {
    typedef verified_int<uint8_t, saturate_overflow> conversion;

    int16_t valueA;
    uint8_t valueB;

    valueA = -1;
    valueB = conversion(valueA);
    EXPECT_EQ(valueB, 0);

    valueA = 0;
    valueB = conversion(valueA);
    EXPECT_EQ(valueB, 0);

    valueA = 255;
    valueB = conversion(valueA);
    EXPECT_EQ(valueB, 255);

    valueA = 256;
    valueB = conversion(valueA);
    EXPECT_EQ(valueB, 255);
}

TEST(verified_int_TDD, Conversion2) {
    int16_t valueA;
    uint8_t valueB;

    valueA = -1;
    valueB = verified_int<uint8_t, saturate_overflow>(valueA);
    EXPECT_EQ(valueB, 0);

    valueA = 0;
    valueB = verified_int<uint8_t, saturate_overflow>(valueA);
    EXPECT_EQ(valueB, 0);

    valueA = 255;
    valueB = verified_int<uint8_t, saturate_overflow>(valueA);
    EXPECT_EQ(valueB, 255);

    valueA = 256;
    valueB = verified_int<uint8_t, saturate_overflow>(valueA);
    EXPECT_EQ(valueB, 255);
}

#define bounded_cast  verified_int

TEST(verified_int_TDD, Conversion3) {
    int16_t valueA;
    uint8_t valueB;

    valueA = -1;
    valueB = bounded_cast<uint8_t, saturate_overflow>(valueA);
    EXPECT_EQ(valueB, 0);

    valueA = 0;
    valueB = bounded_cast<uint8_t, saturate_overflow>(valueA);
    EXPECT_EQ(valueB, 0);

    valueA = 255;
    valueB = bounded_cast<uint8_t, saturate_overflow>(valueA);
    EXPECT_EQ(valueB, 255);

    valueA = 256;
    valueB = bounded_cast<uint8_t, saturate_overflow>(valueA);
    EXPECT_EQ(valueB, 255);
}

TEST(verified_int_TDD, Conversion4) {
    int16_t valueA;
    uint8_t valueB;

    valueA = -1;
    valueB = saturate_int<uint8_t>::type(valueA);
    EXPECT_EQ(valueB, 0);

    valueA = 0;
    valueB = saturate_int<uint8_t>::type(valueA);
    EXPECT_EQ(valueB, 0);

    valueA = 255;
    valueB = saturate_int<uint8_t>::type(valueA);
    EXPECT_EQ(valueB, 255);

    valueA = 256;
    valueB = saturate_int<uint8_t>::type(valueA);
    EXPECT_EQ(valueB, 255);
}

TEST(BoundingPolicies_TDD, nan_overflow) {
    verified_int<uint8_t, nan_overflow> valueA(130U);
    verified_int<uint8_t, nan_overflow> valueB(130U);
    verified_int<uint8_t, nan_overflow> valueC(0U);

    EXPECT_NO_THROW(valueC = valueA + valueB);
    uint8_t NANValue = integer_traits<uint8_t>::const_max;
    EXPECT_EQ(NANValue, valueC);

    EXPECT_NO_THROW(valueC += 5U);
    EXPECT_EQ(NANValue, valueC);
}

TEST(BoundingPolicies_TDD, SaturateAddition) {
    verified_int<uint8_t, saturate_overflow> test(250U);
    EXPECT_EQ(250U, test) << ::test_system::toStdString(test);
    test += 2U;
    EXPECT_EQ(252U, test) << ::test_system::toStdString(test);
    test += 10U;
    EXPECT_EQ(255U, test) << ::test_system::toStdString(test);
    test += 12U;
    EXPECT_EQ(255U, test) << ::test_system::toStdString(test);
}

TEST(BoundingPolicies_TDD, SaturateSubtraction) {
    verified_int<uint8_t, saturate_overflow> test(14U);
    EXPECT_EQ(14U, test) << ::test_system::toStdString(test);
    test += 2U;
    EXPECT_EQ(16U, test) << ::test_system::toStdString(test);
    test -= 10U;
    EXPECT_EQ(6U, test) << ::test_system::toStdString(test);
    test -= 10U;
    EXPECT_EQ(0U, test) << ::test_system::toStdString(test);
}
} // namespace anonymous
