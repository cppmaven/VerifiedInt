
//               Copyright Ben Robinson 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_METAASSERT_UNITTEST defined

#include <testsystem.hpp>
#include <stringutils.hpp>
#include <climits>
#include "verified_int.hpp"

namespace {

using boost::verified_int;
using boost::throw_overflow;

TEST(verified_intSubtraction_TDD, Subtract_Verified_To_Verified) {
    verified_int<int32_t, throw_overflow> testA(0);
    verified_int<int32_t, throw_overflow> testB(0);
    EXPECT_NO_THROW(({
        testA -= testB;
    }));
}

//TEST(verified_int_TDD, Subtract_Verified_To_Verified_MismatchBounds) {
//    verified_int<int32_t, throw_overflow> testA(0);
//    verified_int<int32_t, throw_overflow, -0x80000000, 0x7FFFFFF0> testB(0);
//    EXPECT_NO_THROW(({
//        testA -= testB;
//    }));
//}
//
//TEST(verified_int_TDD, Subtract_Verified_To_Verified_MismatchType) {
//    verified_int<int32_t, throw_overflow> testA(0);
//    verified_int<uint32_t, throw_overflow> testB(0);
//    EXPECT_ANY_THROW(({
//        testA -= testB;
//    }));
//}
//
//TEST(verified_int_TDD, Subtract_Verified_To_Verified_MismatchPolicy) {
//    verified_int<int32_t, throw_overflow> testA(0);
//    verified_int<int32_t, AssertOutOfBounds, -0x80000000, 0x7FFFFFF0> testB(0);
//    EXPECT_ANY_THROW(({
//        testA -= testB;
//    }));
//}

// ----------------------------------
TEST(verified_int_TDD, Subtract_uint8_from_uint8) {
    verified_int<uint8_t, throw_overflow> test(0xFF);
    EXPECT_NO_THROW(({
        test -= static_cast<uint8_t>(0xFF);
    }));
}

TEST(verified_int_TDD, Subtract_uint8_from_uint16) {
    verified_int<uint8_t, throw_overflow> test(0xFF);
    EXPECT_NO_THROW(({
        test -= static_cast<uint16_t>(0xFF);
    }));
}

TEST(verified_int_TDD, Subtract_uint8_from_uint32) {
    verified_int<uint8_t, throw_overflow> test(0xFF);
    EXPECT_NO_THROW(({
        test -= static_cast<uint32_t>(0xFF);
    }));
}

TEST(verified_int_TDD, Subtract_uint8_from_int8) {
    verified_int<uint8_t, throw_overflow> test(0xFF);
    EXPECT_NO_THROW(({
        test -= static_cast<int8_t>(0x7F);
    }));
}

TEST(verified_int_TDD, Subtract_uint8_from_int16) {
    verified_int<uint8_t, throw_overflow> test(0xFF);
    EXPECT_NO_THROW(({
        test -= static_cast<int16_t>(0xFF);
    }));}

TEST(verified_int_TDD, Subtract_uint8_from_int32) {
    verified_int<uint8_t, throw_overflow> test(0xFF);
    EXPECT_NO_THROW(({
        test -= static_cast<int32_t>(0xFF);
    }));}

// -----------------------------------

TEST(verified_int_TDD, Subtract_uint8_from_int8_Negative) {
    verified_int<uint8_t, throw_overflow> test(0x7F);
    EXPECT_NO_THROW(({
        test -= static_cast<int8_t>(-0x80);
    }));
}

TEST(verified_int_TDD, Subtract_uint8_from_int16_Negative) {
    verified_int<uint8_t, throw_overflow> test(0x7F);
    EXPECT_NO_THROW(({
        test -= static_cast<int16_t>(-0x80);
    }));
}

TEST(verified_int_TDD, Subtract_uint8_from_int32_Negative) {
    verified_int<uint8_t, throw_overflow> test(0x7F);
    EXPECT_NO_THROW(({
        test -= static_cast<int32_t>(-0x80);
    }));
}

//------------------------------------

TEST(verified_int_TDD, Subtract_uint8_from_uint16_Input_Overflow) {
    verified_int<uint8_t, throw_overflow> test(0xFF);
    EXPECT_ANY_THROW(({
        test -= static_cast<uint16_t>(0x0100);
    }));
}

TEST(verified_int_TDD, Subtract_uint8_from_uint32_Input_Overflow) {
    verified_int<uint8_t, throw_overflow> test(0xFF);
    EXPECT_ANY_THROW(({
        test -= static_cast<uint32_t>(0x0100);
    }));
}

TEST(verified_int_TDD, Subtract_uint8_from_int16_Input_Overflow) {
    verified_int<uint8_t, throw_overflow> test(0xFF);
    EXPECT_ANY_THROW(({
        test -= static_cast<int16_t>(0x0100);
    }));
}

TEST(verified_int_TDD, Subtract_uint8_from_int32_Input_Overflow) {
    verified_int<uint8_t, throw_overflow> test(0xFF);
    EXPECT_ANY_THROW(({
        test -= static_cast<int32_t>(0x0100);
    }));
}

// --------------------------------------

TEST(verified_int_TDD, Subtract_uint8_from_uint16_Sum_BelowOverflow) {
    verified_int<uint8_t, throw_overflow> test(0xFE);
    EXPECT_ANY_THROW(({
        test -= static_cast<uint16_t>(0xFF);
    }));
}

TEST(verified_int_TDD, Subtract_uint8_from_uint32_Sum_BelowOverflow) {
    verified_int<uint8_t, throw_overflow> test(0xFE);
    EXPECT_ANY_THROW(({
        test -= static_cast<uint32_t>(0xFF);
    }));
}

TEST(verified_int_TDD, Subtract_uint8_from_int8_Sum_Overflow) {
    verified_int<uint8_t, throw_overflow> test(0x80);
    EXPECT_ANY_THROW(({
        test -= static_cast<int8_t>(-0x80);
    }));
}

TEST(verified_int_TDD, Subtract_uint8_from_int16_Sum_Overflow) {
    verified_int<uint8_t, throw_overflow> test(0x80);
    EXPECT_ANY_THROW(({
        test -= static_cast<int16_t>(-0x80);
    }));
}

TEST(verified_int_TDD, Subtract_uint8_from_int16_Sum_BelowOverflow) {
    verified_int<uint8_t, throw_overflow> test(0xFE);
    EXPECT_ANY_THROW(({
        test -= static_cast<int16_t>(0xFF);
    }));
}

TEST(verified_int_TDD, Subtract_uint8_from_int32_Sum_Overflow) {
    verified_int<uint8_t, throw_overflow> test(1);
    EXPECT_ANY_THROW(({
        test -= static_cast<int32_t>(-0xFF);
    }));
}

TEST(verified_int_TDD, Subtract_uint8_from_int32_Sum_BelowOverflow) {
    verified_int<uint8_t, throw_overflow> test(0xFE);
    EXPECT_ANY_THROW(({
        test -= static_cast<int32_t>(0xFF);
    }));
}
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

TEST(verified_int_TDD, Subtract_int8_from_uint8) {
    verified_int<int8_t, throw_overflow> test(0x7F);
    EXPECT_NO_THROW(({
        test -= static_cast<uint8_t>(0xFF);
    }));
}

TEST(verified_int_TDD, Subtract_int8_from_uint16) {
    verified_int<int8_t, throw_overflow> test(0x7F);
    EXPECT_NO_THROW(({
        test -= static_cast<uint16_t>(0xFF);
    }));
}

TEST(verified_int_TDD, Subtract_int8_from_uint32) {
    verified_int<int8_t, throw_overflow> test(0x7F);
    EXPECT_NO_THROW(({
        test -= static_cast<uint32_t>(0xFF);
    }));
}

TEST(verified_int_TDD, Subtract_int8_from_int8) {
    verified_int<int8_t, throw_overflow> test(-1);
    EXPECT_NO_THROW(({
        test -= static_cast<int8_t>(0x7F);
    }));
}

TEST(verified_int_TDD, Subtract_int8_from_int16) {
    verified_int<int8_t, throw_overflow> test(0x7F);
    EXPECT_NO_THROW(({
        test -= static_cast<int16_t>(0xFF);
    }));
}

TEST(verified_int_TDD, Subtract_int8_from_int32) {
    verified_int<int8_t, throw_overflow> test(0x7F);
    EXPECT_NO_THROW(({
        test -= static_cast<int32_t>(0xFF);
    }));
}

// -----------------------------------

TEST(verified_int_TDD, Subtract_int8_from_int8_Negative) {
    verified_int<int8_t, throw_overflow> test(-1);
    EXPECT_NO_THROW(({
        test -= static_cast<int8_t>(-0x80);
    }));
}

TEST(verified_int_TDD, Subtract_int8_from_int16_Negative) {
    verified_int<int8_t, throw_overflow> test(-1);
    EXPECT_NO_THROW(({
        test -= static_cast<int16_t>(-0x80);
    }));
}

TEST(verified_int_TDD, Subtract_int8_from_int32_Negative) {
    verified_int<int8_t, throw_overflow> test(-1);
    EXPECT_NO_THROW(({
        test -= static_cast<int32_t>(-0x80);
    }));
}

// -------------------------------------------------------
TEST(verified_int_TDD, Subtract_int8_from_uint16_Input_Overflow) {
    verified_int<int8_t, throw_overflow> test(0x7F);
    EXPECT_ANY_THROW(({
        test -= static_cast<uint16_t>(0x100);
    }));
}

TEST(verified_int_TDD, Subtract_int8_from_uint32_Input_Overflow) {
    verified_int<int8_t, throw_overflow> test(0x7F);
    EXPECT_ANY_THROW(({
        test -= static_cast<uint32_t>(0x100);
    }));
}

TEST(verified_int_TDD, Subtract_int8_from_int16_Input_BelowOverflow) {
    verified_int<int8_t, throw_overflow> test(-0x80);
    EXPECT_ANY_THROW(({
        test -= static_cast<int16_t>(-0x0100);
    }));
}

TEST(verified_int_TDD, Subtract_int8_from_int16_Input_Overflow) {
    verified_int<int8_t, throw_overflow> test(0x7F);
    EXPECT_ANY_THROW(({
        test -= static_cast<int16_t>(0x0100);
    }));
}

TEST(verified_int_TDD, Subtract_int8_from_int32_Input_BelowOverflow) {
    verified_int<int8_t, throw_overflow> test(-0x80);
    EXPECT_ANY_THROW(({
        test -= static_cast<int32_t>(-0x0100);
    }));
}

TEST(verified_int_TDD, Subtract_int8_from_int32_Input_Overflow) {
    verified_int<int8_t, throw_overflow> test(0x7F);
    EXPECT_ANY_THROW(({
        test -= static_cast<int32_t>(0x0100);
    }));
}

// -------------------------------------------------------

TEST(verified_int_TDD, Subtract_int8_from_uint8_Sum_Overflow) {
    verified_int<int8_t, throw_overflow> test(-2);
    EXPECT_ANY_THROW(({
        test -= static_cast<uint8_t>(0x7F);
    }));
}

TEST(verified_int_TDD, Subtract_int8_from_uint16_Sum_Overflow) {
    verified_int<int8_t, throw_overflow> test(-2);
    EXPECT_ANY_THROW(({
        test -= static_cast<uint16_t>(0x7F);
    }));
}

TEST(verified_int_TDD, Subtract_int8_from_uint32_Sum_Overflow) {
    verified_int<int8_t, throw_overflow> test(-2);
    EXPECT_ANY_THROW(({
        test -= static_cast<uint32_t>(0x7F);
    }));
}

TEST(verified_int_TDD, Subtract_int8_from_int16_Sum_BelowOverflow) {
    verified_int<int8_t, throw_overflow> test(0);
    EXPECT_ANY_THROW(({
        test -= static_cast<int16_t>(-0x80);
    }));
}

TEST(verified_int_TDD, Subtract_int8_from_int16_Sum_Overflow) {
    verified_int<int8_t, throw_overflow> test(-2);
    EXPECT_ANY_THROW(({
        test -= static_cast<int16_t>(0x7F);
    }));
}

TEST(verified_int_TDD, Subtract_int8_from_int32_Sum_BelowOverflow) {
    verified_int<int8_t, throw_overflow> test(0);
    EXPECT_ANY_THROW(({
        test -= static_cast<int32_t>(-0x80);
    }));
}

TEST(verified_int_TDD, Subtract_int8_from_int32_Sum_Overflow) {
    verified_int<int8_t, throw_overflow> test(-2);
    EXPECT_ANY_THROW(({
        test -= static_cast<int32_t>(0x7F);
    }));
}

// --------------------------------------

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

TEST(verified_int_TDD, Subtract_uint16_from_uint8) {
    verified_int<uint16_t, throw_overflow> test(0xFFFF);
    EXPECT_NO_THROW(({
        test -= static_cast<uint8_t>(0xFF);
    }));
}

TEST(verified_int_TDD, Subtract_uint16_from_uint16) {
    verified_int<uint16_t, throw_overflow> test(0xFFFF);
    EXPECT_NO_THROW(({
        test -= static_cast<uint16_t>(0xFFFF);
    }));
}

TEST(verified_int_TDD, Subtract_uint16_from_uint32) {
    verified_int<uint16_t, throw_overflow> test(0xFFFF);
    EXPECT_NO_THROW(({
        test -= static_cast<uint32_t>(0xFFFF);
    }));
}

TEST(verified_int_TDD, Subtract_uint16_from_int8) {
    verified_int<uint16_t, throw_overflow> test(0xFFFF);
    EXPECT_NO_THROW(({
        test -= static_cast<int8_t>(0x7F);
    }));
}

TEST(verified_int_TDD, Subtract_uint16_from_int16) {
    verified_int<uint16_t, throw_overflow> test(0xFFFF);
    EXPECT_NO_THROW(({
        test -= static_cast<int16_t>(0x7FFF);
    }));
}

TEST(verified_int_TDD, Subtract_uint16_from_int32) {
    verified_int<uint16_t, throw_overflow> test(0xFFFF);
    EXPECT_NO_THROW(({
        test -= static_cast<int32_t>(0x7FFF);
    }));
}

// -----------------------------------

TEST(verified_int_TDD, Subtract_uint16_from_int8_Negative) {
    verified_int<uint16_t, throw_overflow> test(0x80);
    EXPECT_NO_THROW(({
        test -= static_cast<int8_t>(-0x80);
    }));
}

TEST(verified_int_TDD, Subtract_uint16_from_int16_Negative) {
    verified_int<uint16_t, throw_overflow> test(0x7FFF);
    EXPECT_NO_THROW(({
        test -= static_cast<int16_t>(-0x8000);
    }));
}

TEST(verified_int_TDD, Subtract_uint16_from_int32_Negative) {
    verified_int<uint16_t, throw_overflow> test(0x7FFF);
    EXPECT_NO_THROW(({
        test -= static_cast<int32_t>(-0x8000);
    }));
}

// -----------------------------------

TEST(verified_int_TDD, Subtract_int16_from_uint8) {
    verified_int<int16_t, throw_overflow> test(-1);
    EXPECT_NO_THROW(({
        test -= static_cast<uint8_t>(0x7F);
    }));
}

TEST(verified_int_TDD, Subtract_int16_from_uint16) {
    verified_int<int16_t, throw_overflow> test(-1);
    EXPECT_NO_THROW(({
        test -= static_cast<uint16_t>(0x7FFF);
    }));
}

TEST(verified_int_TDD, Subtract_int16_from_uint32) {
    verified_int<int16_t, throw_overflow> test(-1);
    EXPECT_NO_THROW(({
        test -= static_cast<uint32_t>(0x7FFF);
    }));
}

TEST(verified_int_TDD, Subtract_int16_from_int8) {
    verified_int<int16_t, throw_overflow> test(-1);
    EXPECT_NO_THROW(({
        test -= static_cast<int8_t>(0x7F);
    }));
}

TEST(verified_int_TDD, Subtract_int16_from_int16) {
    verified_int<int16_t, throw_overflow> test(-1);
    EXPECT_NO_THROW(({
        test -= static_cast<int16_t>(0x7FFF);
    }));
}

TEST(verified_int_TDD, Subtract_int16_from_int32) {
    verified_int<int16_t, throw_overflow> test(-1);
    EXPECT_NO_THROW(({
        test -= static_cast<int32_t>(0x7FFF);
    }));
}
// -----------------------------------
TEST(verified_int_TDD, Subtract_int16_from_int8_Negative) {
    verified_int<int16_t, throw_overflow> test(0x7F7F);
    EXPECT_NO_THROW(({
        test -= static_cast<int8_t>(-0x80);
    }));
}

TEST(verified_int_TDD, Subtract_int16_from_int16_Negative) {
    verified_int<int16_t, throw_overflow> test(-1);
    EXPECT_NO_THROW(({
        test -= static_cast<int16_t>(-0x8000);
    }));
}

TEST(verified_int_TDD, Subtract_int16_from_int32_Negative) {
    verified_int<int16_t, throw_overflow> test(-1);
    EXPECT_NO_THROW(({
        test -= static_cast<int32_t>(-0x8000);
    }));
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

TEST(verified_int_TDD, Subtract_uint32_from_uint32_withUpperLimit) {
    verified_int<uint32_t, throw_overflow> test(0xFFFFFFFF);
    EXPECT_NO_THROW(({
        test -= static_cast<uint32_t>(0xFFFFFFFF);
    }));
}
TEST(verified_int_TDD, Subtract_uint32_from_uint32_Sum_Overflow) {
    verified_int<uint32_t, throw_overflow> test(0xFFFFFFFE);
    EXPECT_ANY_THROW(({
        test -= static_cast<uint32_t>(0xFFFFFFFF);
    }));
}
TEST(verified_int_TDD, Subtract_uint32_from_int32_withUpperLimit_Negative) {
    verified_int<uint32_t, throw_overflow> test(0x7FFFFFFF);
    EXPECT_NO_THROW(({
        test -= static_cast<int32_t>(-0x80000000);
    }));
}
TEST(verified_int_TDD, Subtract_uint32_from_int32_BelowOverflow_Negative) {
    verified_int<uint32_t, throw_overflow> test(0x80000000);
    EXPECT_ANY_THROW(({
        test -= static_cast<int32_t>(-0x80000000);
    }));
}
TEST(verified_int_TDD, Subtract_int32_from_uint32_withUpperLimit) {
    verified_int<int32_t, throw_overflow> test(-1);
    EXPECT_NO_THROW(({
        test -= static_cast<uint32_t>(0x7FFFFFFF);
    }));
}
TEST(verified_int_TDD, Subtract_int32_from_uint32_Sum_Overflow) {
    verified_int<int32_t, throw_overflow> test(-2);
    EXPECT_ANY_THROW(({
        test -= static_cast<uint32_t>(0x7FFFFFFF);
    }));
}
TEST(verified_int_TDD, Subtract_int32_from_int32_withLowerLimit) {
    verified_int<int32_t, throw_overflow> test(-1);
    EXPECT_NO_THROW(({
        test -= static_cast<int32_t>(-0x80000000);
    }));
}
TEST(verified_int_TDD, Subtract_int32_from_int32_Sum_BelowOverflow) {
    verified_int<int32_t, throw_overflow> test(0);
    EXPECT_ANY_THROW(({
        test -= static_cast<int32_t>(-0x80000000);
    }));
}
TEST(verified_intDivision_TDD, SignedMaxSubtractNegOne) {
    verified_int<int8_t, throw_overflow> lhs(boost::integer_traits<int8_t>::const_max);
    verified_int<int8_t, throw_overflow> rhs(-1);
    EXPECT_ANY_THROW(({
        lhs -= rhs;
    }));
}

TEST(verified_intDivision_TDD, UnSignedMaxSubtractNegOne) {
    verified_int<uint8_t, throw_overflow> lhs(boost::integer_traits<uint8_t>::const_max);
    verified_int<int8_t, throw_overflow> rhs(-1);
    EXPECT_ANY_THROW(({
        lhs -= rhs;
    }));
}

TEST(verified_intDivision_TDD, SignedMinSubtractNegOne) {
    verified_int<int8_t, throw_overflow> lhs(boost::integer_traits<int8_t>::const_min);
    verified_int<int8_t, throw_overflow> rhs(-1);
    EXPECT_NO_THROW(({
        lhs -= rhs;
    }));
}

TEST(verified_intDivision_TDD, UnSignedMinSubtractNegOne) {
    verified_int<uint8_t, throw_overflow> lhs(boost::integer_traits<uint8_t>::const_min);
    verified_int<int8_t, throw_overflow> rhs(-1);
    EXPECT_NO_THROW(({
        lhs -= rhs;
    }));
}
TEST(verified_intDivision_TDD, SignedMaxSubtractOne) {
    verified_int<int8_t, throw_overflow> lhs(boost::integer_traits<int8_t>::const_max);
    verified_int<int8_t, throw_overflow> rhs(1);
    EXPECT_NO_THROW(({
        lhs -= rhs;
    }));
}

TEST(verified_intDivision_TDD, UnSignedMaxSubtractOne) {
    verified_int<uint8_t, throw_overflow> lhs(boost::integer_traits<uint8_t>::const_max);
    verified_int<int8_t, throw_overflow> rhs(1);
    EXPECT_NO_THROW(({
        lhs -= rhs;
    }));
}

TEST(verified_intDivision_TDD, SignedMinSubtractOne) {
    verified_int<int8_t, throw_overflow> lhs(boost::integer_traits<int8_t>::const_min);
    verified_int<int8_t, throw_overflow> rhs(1);
    EXPECT_ANY_THROW(({
        lhs -= rhs;
    }));
}

TEST(verified_intDivision_TDD, UnSignedMinSubtractOne) {
    verified_int<uint8_t, throw_overflow> lhs(boost::integer_traits<uint8_t>::const_min);
    verified_int<int8_t, throw_overflow> rhs(1);
    EXPECT_ANY_THROW(({
        lhs -= rhs;
    }));
}
} // namespace anonymous
