
//               Copyright Ben Robinson 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_METAASSERT_UNITTEST defined

#include <testsystem.hpp>
#include <stringutils.hpp>
#include "verified_int.hpp"
#include "PrimitiveTraits.hpp"

#include <boost/type_traits/common_type.hpp>
#include <boost/integer_traits.hpp>

namespace {

using boost::verified_int;
using boost::throw_overflow;
using boost::overflow_detected;
using respiratory::MaxValue;
using respiratory::MinValue;
using boost::verified_uint8_t;
using boost::verified_uint16_t;
using boost::verified_uint32_t;
using boost::verified_int8_t;
using boost::verified_int16_t;
using boost::verified_int32_t;
using boost::common_type;
using boost::integer_traits;

TEST(verified_int_TDD, t64bitSanityCheck) {
    EXPECT_NO_THROW(({
        verified_int<uint64_t, throw_overflow> var(integer_traits<uint64_t>::const_max);
    }));
    EXPECT_NO_THROW(({
        verified_int<uint64_t, throw_overflow> var(integer_traits<uint64_t>::const_min);
    }));
    EXPECT_NO_THROW(({
        verified_int<int64_t, throw_overflow> var(integer_traits<int64_t>::const_max);
    }));
    EXPECT_NO_THROW(({
        verified_int<int64_t, throw_overflow> var(integer_traits<int64_t>::const_min);
    }));

    EXPECT_THROW(({
        verified_int<int64_t, throw_overflow> var(integer_traits<uint64_t>::const_max);
    }), overflow_detected);
    EXPECT_THROW(({
        verified_int<uint64_t, throw_overflow> var(integer_traits<int64_t>::const_min);
    }), overflow_detected);
}

TEST(verified_int_TDD, CommonTypeGoesUnsigned64) {
    typedef common_type<uint64_t, int64_t>::type TheType;

    EXPECT_NO_THROW(({
        verified_int<TheType, throw_overflow> var(integer_traits<uint64_t>::const_max);
    }));
    EXPECT_NO_THROW(({
        verified_int<TheType, throw_overflow> var(integer_traits<uint64_t>::const_min);
    }));

    EXPECT_NO_THROW(({
        verified_int<TheType, throw_overflow> var(integer_traits<int64_t>::const_max);
    }));
    EXPECT_THROW(({
        verified_int<TheType, throw_overflow> var(integer_traits<int64_t>::const_min);
    }), overflow_detected);
}

TEST(verified_int_TDD, VariousForms) {
    // Detect overflow for an int8_t (these expressions all produce identical compiler optimized dissassembly).
    verified_int<int8_t, throw_overflow> testA1(0U);

    // Detect bounds exceeded and overflow.
    verified_int<int8_t, throw_overflow> testB1(0U);
}

TEST(verified_int_TDD, Typedef) {
    verified_uint8_t test(uint8_t(0U));
    verified_uint8_t test2(uint8_t(0xF000U));
    EXPECT_THROW(({
        verified_uint8_t test3(0xF000U);
    }), boost::positive_overflow_detected);
    EXPECT_THROW(({
        test = 0x100;
    }), boost::positive_overflow_detected);
}

TEST(verified_int_TDD, Negation) {
    verified_int8_t valueA(5);
    verified_int8_t valueB(7);
    verified_int8_t valueC(0);

    valueC = valueA + -valueB;
    EXPECT_EQ(-2, valueC) << ::test_system::toStdString(valueC);

    valueC = -valueA;
    EXPECT_EQ(-5, valueC) << ::test_system::toStdString(valueC);
}

TEST(verified_int_TDD, Unsigned8WithNegative) {
    EXPECT_THROW(({
        verified_uint8_t valueA(-0x80);
    }), boost::negative_overflow_detected);
}

TEST(verified_int_TDD, Unsigned8WithNegative1) {
    EXPECT_THROW(({
        verified_uint8_t valueA(-0x80000);
    }), boost::negative_overflow_detected);
}

TEST(verified_int_TDD, Unsigned16WithNegative) {
    EXPECT_THROW(({
        verified_uint16_t valueA(-0x8000);
    }), boost::negative_overflow_detected);
}

TEST(verified_int_TDD, Signed8WithUnsigned) {
    EXPECT_THROW(({
        verified_int8_t valueA(0x80U);
    }), boost::positive_overflow_detected);
}

TEST(verified_int_TDD, Signed16WithUnsigned) {
    EXPECT_THROW(({
        verified_int16_t valueA(0x8000U);
    }), boost::positive_overflow_detected);
}

TEST(verified_int_TDD, Signed32WithUnsigned) {
    EXPECT_THROW(({
        verified_int32_t valueA(0x80000000U);
    }), boost::positive_overflow_detected);
}

TEST(verified_int_TDD, UnaryMinusOperator) {
    verified_int8_t valueA(120);
    verified_int8_t valueB(0);

    EXPECT_NO_THROW(valueB = -valueA);
    EXPECT_EQ(-120, valueB);
}

TEST(verified_int_TDD, UnaryMinusOperator2) {
    verified_int8_t valueA(60);
    verified_int8_t valueB(60);
    verified_int8_t valueC(0);

    EXPECT_NO_THROW(valueC = -valueA + -valueB);
    EXPECT_EQ(-120, valueC);
}

TEST(verified_int_TDD, UnaryMinusOperatorNegateUnsigned) {
    verified_uint8_t valueA(120);
    verified_int32_t valueB(0);

    EXPECT_THROW(valueB = -valueA, boost::negative_overflow_detected);
}

TEST(verified_int_TDD, UnaryMinusOperatorNegateMaxSigned) {
    verified_int8_t valueA(0x7F);
    verified_int8_t valueB(0);

    EXPECT_NO_THROW(valueB = -valueA);
}

TEST(verified_int_TDD, UnaryMinusOperatorNegateMinSigned) {
    verified_int8_t valueA(-0x80);
    verified_int32_t valueB(0);

    EXPECT_THROW(valueB = -valueA, boost::positive_overflow_detected);
}

//TEST(verified_int_TDD, MixedTypes1) {
//    verified_uint8_t valueA(2U);
//    verified_uint16_t valueB(3U);
//    verified_uint16_t valueC(7U);
//
//    EXPECT_ANY_THROW(valueC = valueA + valueB);
//}

TEST(verified_int_TDD, MixedTypes2) {
    verified_uint8_t valueA(2U);
    verified_uint16_t valueB(3U);
    verified_uint16_t valueC(7U);

    valueC = valueA + static_cast<uint8_t>(valueA);
    valueC = valueA + uint8_t(valueA);

    valueC = static_cast<verified_uint16_t>(valueA) + valueB;
}

TEST(verified_int_TDD, MixedTypes3) {
    verified_uint32_t valueZ(0xF0000000U);

    verified_uint32_t valueA(valueZ);
    EXPECT_THROW(({
        verified_uint8_t valueB(valueZ);
    }), boost::positive_overflow_detected);
    EXPECT_THROW(({
        verified_uint8_t valueC(valueA);
    }), boost::positive_overflow_detected);
}

TEST(verified_int_TDD, MixedTypes4) {
    verified_uint8_t valueA(2U);
    verified_uint16_t valueB(3U);
    verified_uint16_t valueC(7U);

    valueC = static_cast<verified_uint16_t>(valueA) + valueB;
}

TEST(verified_int_TDD, TestTypedefAssignment) {
    verified_uint8_t test(15U);
    test = 0U;
}

TEST(verified_int_TDD, ShouldThrowOnConstruction) {
    EXPECT_THROW(({
        verified_int<uint8_t, throw_overflow> test(256U);
    }), boost::positive_overflow_detected);
}

TEST(verified_int_TDD, TestTypedefOverflow) {
    verified_uint8_t test(254U);
    EXPECT_THROW(test += verified_uint8_t(254), boost::positive_overflow_detected);
}

TEST(verified_int_TDD, ReallyLargeInteger1) {
    verified_int<int32_t, throw_overflow> test(0);
}

TEST(verified_int_TDD, ReallyLargeUnsignedInteger1) {
    verified_int<uint32_t, throw_overflow> test(100U);
}

//TEST(verified_int_TDD, CompileTimeError_Backwards) {
//    verified_int<uint8_t, throw_overflow, 255, 0> test(0);
//}

TEST(verified_int_TDD, PrefixDecrementOperator) {
    uint_t temp;
    verified_int<uint8_t, throw_overflow> test(9U);
    EXPECT_NO_THROW(temp = --test);
    EXPECT_EQ(8U, temp);
}

TEST(verified_int_TDD, PostfixDecrementOperator) {
    uint_t temp;
    verified_int<uint8_t, throw_overflow> test(9U);
    EXPECT_NO_THROW(temp = test--);
    EXPECT_EQ(9U, temp);
    EXPECT_EQ(8U, test);
}

TEST(verified_int_TDD, DecrementOperatorOverflow) {
    verified_int<uint8_t, throw_overflow> test(1);
    EXPECT_NO_THROW(--test);
    EXPECT_THROW(--test, boost::negative_overflow_detected);
}

TEST(verified_int_TDD, WrapAroundOverflow) {
    verified_int<uint8_t, throw_overflow> test(10);
    EXPECT_THROW(test += static_cast<verified_uint8_t>(0xFF), boost::positive_overflow_detected);
}

TEST(verified_int_TDD, WrapAroundBelowOverflow) {
    verified_int<uint8_t, throw_overflow> test(10);
    EXPECT_THROW(test -= verified_uint8_t(0xFF), boost::negative_overflow_detected);
}
TEST(verified_int_TDD, WrapAroundBelowOverflowNeg) {
    verified_int<uint8_t, throw_overflow> test(10);
    EXPECT_THROW(test -= static_cast<verified_uint8_t>(-0x70), boost::negative_overflow_detected);
}

TEST(verified_int_TDD, WrapAroundBelowOverflowPos) {
    verified_int<uint8_t, throw_overflow> test(10);
    EXPECT_THROW(test -= verified_uint8_t(144), boost::negative_overflow_detected);
}

TEST(verified_int_TDD, DownConversionToSmallerTypeFailsIfOutOfBounds) {
    verified_int<uint16_t, throw_overflow> valueA(260);
    verified_int<uint8_t, throw_overflow> valueB(0);
    valueB = valueA - 0x06;
    EXPECT_THROW(valueB = valueA + 0x06, boost::positive_overflow_detected);
}

TEST(verified_int_TDD, PrefixIncrementOperator) {
    uint_t temp;
    verified_int<uint8_t, throw_overflow> test(9U);
    EXPECT_NO_THROW(temp = ++test);
    EXPECT_EQ(10U, temp);
}

TEST(verified_int_TDD, PostfixIncrementOperator) {
    uint_t temp;
    verified_int<uint8_t, throw_overflow> test(9U);
    EXPECT_NO_THROW(temp = test++);
    EXPECT_EQ(9U, temp);
}

TEST(verified_int_TDD, IncrementOperatorOverflow) {
    verified_int<uint8_t, throw_overflow> test(254);
    EXPECT_NO_THROW(++test);
    EXPECT_THROW(++test, boost::positive_overflow_detected);
}

TEST(verified_int_TDD, IncrementWithAnotherVerified) {
    verified_int<uint8_t, throw_overflow> valueA(2U);
    verified_int<uint8_t, throw_overflow> valueB(3U);

    EXPECT_NO_THROW(valueA += valueB);
    EXPECT_EQ(5, valueA);
}

TEST(verified_int_TDD, IncrementWithAnInt) {
    typedef verified_int<uint8_t, throw_overflow> TestType;
    TestType valueA(2U);

    EXPECT_NO_THROW(valueA += TestType(3));
    EXPECT_EQ(5, valueA);
}

TEST(verified_int_TDD, IncrementWithANegativeNegativeOverflow) {
    verified_int<int8_t, throw_overflow> valueA(-0x70);

    EXPECT_THROW(valueA += verified_int8_t(-0x20), boost::negative_overflow_detected);
}

TEST(verified_int_TDD, IncrementWithANegativeNegativeOverflow2) {
    verified_int<uint8_t, throw_overflow> valueA(2U);

    EXPECT_THROW(valueA += verified_uint8_t(-5), boost::negative_overflow_detected);
}

//TEST(verified_int_TDD, IncrementWithANegativeNegativeOverflow3) {
//    verified_int<uint8_t, throw_overflow> valueA(2U);
//    verified_int<int8_t, throw_overflow> valueB(-0x20);
//
//    // This test does not throw because the compiler converts the signed negative to an unsigned positive
//    EXPECT_NO_THROW(valueA += valueB);
//}

TEST(verified_int_TDD, IncrementWithANegativeNegativeOverflow4) {
    verified_int<int8_t, throw_overflow> valueA(2U);
    verified_int<int8_t, throw_overflow> valueB(-0x20);

    // This test does not throw because the compiler converts the signed negative to an unsigned positive
    EXPECT_NO_THROW(valueA = valueA + valueB);
}

TEST(verified_int_TDD, IncrementWithANegativeNegativeOverflow5) {
    verified_int<int8_t, throw_overflow> valueA(2U);
    verified_int<int8_t, throw_overflow> valueB(-0x20);

    // This test does not throw because the compiler converts the signed negative to an unsigned positive
    EXPECT_NO_THROW(valueA = valueB + valueA);
}

//TEST(verified_int_TDD, ConstructNoArgAsLower) {
//    verified_int<uint8_t, throw_overflow, 5U, 9U> valueA;
//
//    EXPECT_EQ(5, valueA);
//}

TEST(verified_int_TDD, AddWithAnotherVerifiedOperatorPlus) {
    verified_int<uint8_t, throw_overflow> valueA(2);
    verified_int<uint8_t, throw_overflow> valueB(3);

    EXPECT_NO_THROW(valueA = valueB + valueB);
    EXPECT_EQ(6, valueA);
}

TEST(verified_int_TDD, AddWithAnotherVerifiedOperatorPlus2) {
    verified_int<uint8_t, throw_overflow> valueA(2);
    verified_int<uint8_t, throw_overflow> valueB(3);

    EXPECT_NO_THROW(valueA = valueA + valueB);
    EXPECT_EQ(5, valueA);
}

TEST(verified_int_TDD, AddWithAnotherVerifiedOperatorPlus3) {
    verified_int<uint8_t, throw_overflow> valueA(2);
    verified_int<uint8_t, throw_overflow> valueB(3);

    EXPECT_NO_THROW(valueA = valueA + valueB);
    EXPECT_EQ(5, valueA);
}

TEST(verified_int_TDD, AddWithAnotherVerifiedOperatorPlus4) {
    verified_int<uint8_t, throw_overflow> valueA(2);
    uint8_t valueB = 3;

    EXPECT_NO_THROW(valueA = valueA + valueB);
    EXPECT_EQ(5, valueA);
}

TEST(verified_int_TDD, AddWithAnotherVerifiedOperatorPlus5) {
    verified_int<uint8_t, throw_overflow> valueA(2);
    int16_t valueB = 3;

    EXPECT_NO_THROW(valueA = valueA + valueB);
    EXPECT_EQ(5, valueA);
}

TEST(verified_int_TDD, AddWithAnotherVerifiedOperatorPlus6) {
    verified_int<uint32_t, throw_overflow> valueA(2U);
    uint16_t valueB = 285U;

    EXPECT_NO_THROW(valueA = valueA + valueB);
    EXPECT_EQ(287U, valueA);
}

//TEST(verified_int_TDD, IncrementWithAnotherVerifiedExceedLimits) {
//    verified_int<uint8_t, throw_overflow, 0U, 4U> valueA(2U);
//    verified_int<uint8_t, throw_overflow, 0U, 9U> valueB(5U);
//
//    EXPECT_ANY_THROW(valueA += valueB);
//}


TEST(verified_int_TDD, IncrementWithAnotherVerifiedExceedDataLimits) {
    verified_int<uint8_t, throw_overflow> valueA(0xF0);
    verified_int<uint8_t, throw_overflow> valueB(0xF0);

    EXPECT_THROW(valueA += valueB, boost::positive_overflow_detected);
}

TEST(verified_int_TDD, AddWithAnotherVerifiedExceedDataLimits) {
    verified_int<uint8_t, throw_overflow> valueA(0xF0);
    verified_int<uint8_t, throw_overflow> valueB(0xF0);

    EXPECT_THROW(valueA = valueA + valueB, boost::positive_overflow_detected);
}

//TEST(verified_int_TDD, DifferentDataTypes) {
//    verified_int<int8_t, throw_overflow> valueA(0xF0);
//    verified_int<uint8_t, throw_overflow> valueB(0xF0);
//
//    EXPECT_ANY_THROW(valueA = valueA + valueB);
//}
//
//TEST(verified_int_TDD, DifferentLimitsPolicies) {
//    verified_int<uint8_t, throw_overflow> valueA(0xF0);
//    verified_int<uint8_t, IgnoreLimits> valueB(0xF0);
//
//    EXPECT_ANY_THROW(valueA = valueA + valueB);
//}
//
//TEST(verified_int_TDD, DifferentLimitsLimits) {
//    verified_int<uint8_t, throw_overflow> valueA(0xF0);
//    verified_int<uint8_t, throw_overflow, 0U, 0xF0U> valueB(0xF0);
//
//    EXPECT_ANY_THROW(valueA = valueA + valueB);
//}

TEST(verified_int_TDD, AddWithAnotherVerifiedOperatorPlus7) {
    uint8_t valueA = 0x80U;
    verified_int<uint8_t, throw_overflow> valueB(0xF0);
    verified_int<uint8_t, throw_overflow> valueC(0U);

    EXPECT_THROW(valueC = valueA + valueB, boost::positive_overflow_detected);
}

TEST(verified_int_TDD, AddWithAnotherVerifiedOperatorPlus8) {
    uint8_t valueA = 0x80U;
    verified_int<uint8_t, throw_overflow> valueB(0xF0);
    verified_int<uint8_t, throw_overflow> valueC(0U);

    EXPECT_THROW(valueC = valueB + valueA, boost::positive_overflow_detected);
}

TEST(verified_int_TDD, AddWithAnotherOverflowExceeded) {
    verified_int<uint8_t, throw_overflow> valueA(0xF0U);
    verified_int<uint8_t, throw_overflow> valueB(0xF0U);
    verified_int<uint8_t, throw_overflow> valueC(0U);

    EXPECT_THROW(valueC = valueA + valueB, boost::positive_overflow_detected);
}

TEST(verified_int_TDD, AddWithAnotherLimitsExceededDuringAdd) {
    verified_int<uint8_t, throw_overflow> valueA(130U);
    verified_int<uint8_t, throw_overflow> valueB(130U);
    verified_int<uint8_t, throw_overflow> valueC(0U);

    EXPECT_THROW(valueC = valueA + valueB, boost::positive_overflow_detected);
}

TEST(verified_int_TDD, AddWithAnotherLimitsExceededOnAssign) {
    verified_int<uint8_t, throw_overflow> valueA(130U);
    verified_int<uint8_t, throw_overflow> valueB(130U);
    verified_int<uint8_t, throw_overflow> valueC(0U);

    EXPECT_THROW(valueC = valueA + valueB, boost::positive_overflow_detected);
}
} // namespace anonymous
