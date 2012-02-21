
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

TEST(verified_intAssignment_TDD, Assign_Fromverified_int) {
    verified_int<uint8_t, throw_overflow> testA(static_cast<uint8_t>(0));
    verified_int<uint8_t, throw_overflow> testB(static_cast<uint8_t>(0));

    testB = testA;
}

// -------------------------------

TEST(verified_intAssignment_TDD, Assign_uint8_from_uint8) {
    verified_int<uint8_t, throw_overflow> test(0);
    EXPECT_NO_THROW(({
        test = static_cast<uint8_t>(0);
    }));
}
TEST(verified_intAssignment_TDD, Assign_uint8_from_uint16) {
    verified_int<uint8_t, throw_overflow> test(0);
    EXPECT_NO_THROW(({
        test = static_cast<uint16_t>(0);
    }));
}
TEST(verified_intAssignment_TDD, Assign_uint8_from_uint32) {
    verified_int<uint8_t, throw_overflow> test(0);
    EXPECT_NO_THROW(({
        test = static_cast<uint32_t>(0xFF);
    }));
}
TEST(verified_intAssignment_TDD, Assign_uint8_from_int8) {
    verified_int<uint8_t, throw_overflow> test(0);
    EXPECT_NO_THROW(({
        test = static_cast<int8_t>(0);
    }));
}
TEST(verified_intAssignment_TDD, Assign_uint8_from_int16) {
    verified_int<uint8_t, throw_overflow> test(0);
    EXPECT_NO_THROW(({
        test = static_cast<int16_t>(0xFF);
    }));
}
TEST(verified_intAssignment_TDD, Assign_uint8_from_int32) {
    verified_int<uint8_t, throw_overflow> test(0);
    EXPECT_NO_THROW(({
        test = static_cast<int32_t>(0);
    }));
}

// -----------------------------------

TEST(verified_intAssignment_TDD, Assign_uint8_from_uint16_Overflow) {
    verified_int<uint8_t, throw_overflow> test(0);
    EXPECT_ANY_THROW(({
        test = static_cast<uint16_t>(256);
    }));
}
TEST(verified_intAssignment_TDD, Assign_uint8_from_uint32_Overflow) {
    verified_int<uint8_t, throw_overflow> test(0);
    EXPECT_ANY_THROW(({
        test = static_cast<uint32_t>(256);
    }));
}
TEST(verified_intAssignment_TDD, Assign_uint8_from_int8_BelowOverflow) {
    verified_int<uint8_t, throw_overflow> test(0);
    EXPECT_ANY_THROW(({
        test = static_cast<int8_t>(-1);
    }));
}
TEST(verified_intAssignment_TDD, Assign_uint8_from_int16_BelowOverflow) {
    verified_int<uint8_t, throw_overflow> test(0);
    EXPECT_ANY_THROW(({
        test = static_cast<int16_t>(-1);
    }));
}
TEST(verified_intAssignment_TDD, Assign_uint8_from_int16_Overflow) {
    verified_int<uint8_t, throw_overflow> test(0);
    EXPECT_ANY_THROW(({
        test = static_cast<int16_t>(0x0100);
    }));
}
TEST(verified_intAssignment_TDD, Assign_uint8_from_int32_BelowOverflow) {
    verified_int<uint8_t, throw_overflow> test(0);
    EXPECT_ANY_THROW(({
        test = static_cast<int32_t>(-1);
    }));
}
TEST(verified_intAssignment_TDD, Assign_uint8_from_int32_Overflow) {
    verified_int<uint8_t, throw_overflow> test(0);
    EXPECT_ANY_THROW(({
        test = static_cast<int32_t>(0x0100);
    }));
}

// --------------------------------------

// --------------------------------------

// =======================================================================================

TEST(verified_intAssignment_TDD, Assign_int8_from_uint8) {
    verified_int<int8_t, throw_overflow> test(0);
    EXPECT_NO_THROW(({
        test = static_cast<uint8_t>(0);
    }));
}
TEST(verified_intAssignment_TDD, Assign_int8_from_uint16) {
    verified_int<int8_t, throw_overflow> test(0);
    EXPECT_NO_THROW(({
        test = static_cast<uint16_t>(0x7F);
    }));
}
TEST(verified_intAssignment_TDD, Assign_int8_from_uint32) {
    verified_int<int8_t, throw_overflow> test(0);
    EXPECT_NO_THROW(({
        test = static_cast<uint32_t>(0x7F);
    }));
}
TEST(verified_intAssignment_TDD, Assign_int8_from_int8) {
    verified_int<int8_t, throw_overflow> test(0);
    EXPECT_NO_THROW(({
        test = static_cast<int8_t>(0);
    }));
}
TEST(verified_intAssignment_TDD, Assign_int8_from_int16) {
    verified_int<int8_t, throw_overflow> test(0);
    EXPECT_NO_THROW(({
        test = static_cast<int16_t>(-0x80);
    }));
}
TEST(verified_intAssignment_TDD, Assign_int8_from_int32) {
    verified_int<int8_t, throw_overflow> test(0);
    EXPECT_NO_THROW(({
        test = static_cast<int32_t>(0x7F);
    }));
}

// -----------------------------------

TEST(verified_intAssignment_TDD, Assign_int8_from_uint8_Overflow) {
    verified_int<int8_t, throw_overflow> test(0);
    EXPECT_ANY_THROW(({
        test = static_cast<uint8_t>(0x80);
    }));
}
TEST(verified_intAssignment_TDD, Assign_int8_from_uint16_Overflow) {
    verified_int<int8_t, throw_overflow> test(0);
    EXPECT_ANY_THROW(({
        test = static_cast<uint16_t>(0x80);
    }));
}
TEST(verified_intAssignment_TDD, Assign_int8_from_uint32_Overflow) {
    verified_int<int8_t, throw_overflow> test(0);
    EXPECT_ANY_THROW(({
        test = static_cast<uint32_t>(0x80);
    }));
}
TEST(verified_intAssignment_TDD, Assign_int8_from_int16_BelowOverflow) {
    verified_int<int8_t, throw_overflow> test(0);
    EXPECT_ANY_THROW(({
        test = static_cast<int16_t>(-0x81);
    }));
}
TEST(verified_intAssignment_TDD, Assign_int8_from_int16_Overflow) {
    verified_int<int8_t, throw_overflow> test(0);
    EXPECT_ANY_THROW(({
        test = static_cast<int16_t>(0x80);
    }));
}
TEST(verified_intAssignment_TDD, Assign_int8_from_int32_BelowOverflow) {
    verified_int<int8_t, throw_overflow> test(0);
    EXPECT_ANY_THROW(({
        test = static_cast<int32_t>(-0x81);
    }));
}
TEST(verified_intAssignment_TDD, Assign_int8_from_int32_Overflow) {
    verified_int<int8_t, throw_overflow> test(0);
    EXPECT_ANY_THROW(({
        test = static_cast<int32_t>(0x80);
    }));
}

// --------------------------------------

// --------------------------------------

#ifdef TESTING
// -----------------------------------

TEST(verified_intAssignment_TDD, Assign_uint16_from_uint8) {
    verified_int<throw_overflow, uint16_t, 0U, 0xFFFFU> test(0);
    EXPECT_NO_THROW(({
        test = static_cast<uint8_t>(0);
    }));
}
TEST(verified_intAssignment_TDD, Assign_uint16_from_uint16) {
    verified_int<throw_overflow, uint16_t, 0U, 0xFFFFU> test(0);
    EXPECT_NO_THROW(({
        test = static_cast<uint16_t>(0);
    }));
}
TEST(verified_intAssignment_TDD, Assign_uint16_from_uint32) {
    verified_int<throw_overflow, uint16_t, 0U, 0xFFFFU> test(0);
    EXPECT_NO_THROW(({
        test = static_cast<uint32_t>(0xFFFF);
    }));
}
TEST(verified_intAssignment_TDD, Assign_uint16_from_int8) {
    verified_int<throw_overflow, uint16_t, 0U, 0xFFFFU> test(0);
    EXPECT_NO_THROW(({
        test = static_cast<int8_t>(0);
    }));
}
TEST(verified_intAssignment_TDD, Assign_uint16_from_int16) {
    verified_int<throw_overflow, uint16_t, 0U, 0xFFFFU> test(0);
    EXPECT_NO_THROW(({
        test = static_cast<int16_t>(0x7FFF);
    }));
}
TEST(verified_intAssignment_TDD, Assign_uint16_from_int32) {
    verified_int<throw_overflow, uint16_t, 0U, 0xFFFFU> test(0);
    EXPECT_NO_THROW(({
        test = static_cast<int32_t>(0);
    }));
}

// -----------------------------------

TEST(verified_intAssignment_TDD, Assign_int16_from_uint8) {
    verified_int<throw_overflow, int16_t, -0x8000, 0x7FFF> test(0);
    EXPECT_NO_THROW(({
        test = static_cast<uint8_t>(0);
    }));
}
TEST(verified_intAssignment_TDD, Assign_int16_from_uint16) {
    verified_int<throw_overflow, int16_t, -0x8000, 0x7FFF> test(0);
    EXPECT_NO_THROW(({
        test = static_cast<uint16_t>(0);
    }));
}
TEST(verified_intAssignment_TDD, Assign_int16_from_uint32) {
    verified_int<throw_overflow, int16_t, -0x8000, 0x7FFF> test(0);
    EXPECT_NO_THROW(({
        test = static_cast<uint32_t>(0x7FFF);
    }));
}
TEST(verified_intAssignment_TDD, Assign_int16_from_int8) {
    verified_int<throw_overflow, int16_t, -0x8000, 0x7FFF> test(0);
    EXPECT_NO_THROW(({
        test = static_cast<int8_t>(0);
    }));
}
TEST(verified_intAssignment_TDD, Assign_int16_from_int16) {
    verified_int<throw_overflow, int16_t, -0x8000, 0x7FFF> test(0);
    EXPECT_NO_THROW(({
        test = static_cast<int16_t>(0x7FFF);
    }));
}
TEST(verified_intAssignment_TDD, Assign_int16_from_int32) {
    verified_int<throw_overflow, int16_t, -0x8000, 0x7FFF> test(0);
    EXPECT_NO_THROW(({
        test = static_cast<int32_t>(0);
    }));
}

// =======================================================================================
TEST(verified_intAssignment_TDD, Assign_int32_from_uint32_withUpperLimit) {
    verified_int<int32_t, throw_overflow, -0x80000000, 0x7FFFFFFF> test(0);
        EXPECT_NO_THROW(({ test = static_cast<uint32_t>(0x7FFFFFFF);
    }));
}
TEST(verified_intAssignment_TDD, Assign_int32_from_uint32_Overflow) {
    verified_int<int32_t, throw_overflow, -0x80000000, 0x7FFFFFFF> test(0);
        EXPECT_ANY_THROW(({ test = static_cast<uint32_t>(0x80000000);
    }));
}
TEST(verified_intAssignment_TDD, Assign_int32_from_int32_withLowerLimit) {
    verified_int<int32_t, throw_overflow, -0x80000000, 0x7FFFFFFF> test(0);
        EXPECT_NO_THROW(({ test = static_cast<int32_t>(-0x80000000);
    }));
}
#endif // TESTING
} // namespace anonymous
