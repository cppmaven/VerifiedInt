
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

TEST(verified_intConstruction_TDD, DefaultConstructor) {
    verified_int<uint8_t, throw_overflow> testA;
    EXPECT_ANY_THROW(({
        --testA;
    }));

    verified_int<int8_t, throw_overflow> testB;
    EXPECT_NO_THROW(({
        --testB;
    }));
}

TEST(verified_intConstruction_TDD, Construct_Fromverified_int) {
    verified_int<uint8_t, throw_overflow> testA(static_cast<uint8_t>(0));
    verified_int<uint8_t, throw_overflow> testB(testA);
}

// --------------------------------

TEST(verified_intConstruction_TDD, Construct_uint8_from_uint8) {
    verified_int<uint8_t, throw_overflow> test(static_cast<uint8_t>(0));
}

TEST(verified_intConstruction_TDD, Construct_uint8_from_uint16) {
    verified_int<uint8_t, throw_overflow> test(static_cast<uint16_t>(0));
}

TEST(verified_intConstruction_TDD, Construct_uint8_from_uint32) {
    verified_int<uint8_t, throw_overflow> test(static_cast<uint32_t>(0xFF));
}

TEST(verified_intConstruction_TDD, Construct_uint8_from_int8) {
    verified_int<uint8_t, throw_overflow> test(static_cast<int8_t>(0));
}

TEST(verified_intConstruction_TDD, Construct_uint8_from_int16) {
    verified_int<uint8_t, throw_overflow> test(static_cast<int16_t>(0xFF));
}

TEST(verified_intConstruction_TDD, Construct_uint8_from_int32) {
    verified_int<uint8_t, throw_overflow> test(static_cast<int32_t>(0xFF));
}

// -----------------------------------

TEST(verified_intConstruction_TDD, Construct_uint8_from_uint16_Overflow) {
    EXPECT_ANY_THROW(({
        verified_int<uint8_t, throw_overflow> test(static_cast<uint16_t>(256));
    }));
}

TEST(verified_intConstruction_TDD, Construct_uint8_from_uint32_Overflow) {
    EXPECT_ANY_THROW(({
        verified_int<uint8_t, throw_overflow> test(static_cast<uint32_t>(256));
    }));
}

TEST(verified_intConstruction_TDD, Construct_uint8_from_int8_BelowOverflow) {
    EXPECT_ANY_THROW(({
        verified_int<uint8_t, throw_overflow> test(static_cast<int8_t>(-1));
    }));
}

TEST(verified_intConstruction_TDD, Construct_uint8_from_int16_BelowOverflow) {
    EXPECT_ANY_THROW(({
        verified_int<uint8_t, throw_overflow> test(static_cast<int16_t>(-1));
    }));
}

TEST(verified_intConstruction_TDD, Construct_uint8_from_int16_Overflow) {
    EXPECT_ANY_THROW(({
        verified_int<uint8_t, throw_overflow> test(static_cast<int16_t>(0x0100));
    }));
}

TEST(verified_intConstruction_TDD, Construct_uint8_from_int32_BelowOverflow) {
    EXPECT_ANY_THROW(({
        verified_int<uint8_t, throw_overflow> test(static_cast<int32_t>(-1));
    }));
}

TEST(verified_intConstruction_TDD, Construct_uint8_from_int32_Overflow) {
    EXPECT_ANY_THROW(({
        verified_int<uint8_t, throw_overflow> test(static_cast<int32_t>(0x0100));
    }));
}

// =======================================================================================

TEST(verified_intConstruction_TDD, Construct_int8_from_uint8) {
    verified_int<int8_t, throw_overflow> test(static_cast<uint8_t>(0));
}

TEST(verified_intConstruction_TDD, Construct_int8_from_uint16) {
    verified_int<int8_t, throw_overflow> test(static_cast<uint16_t>(0x7F));
}

TEST(verified_intConstruction_TDD, Construct_int8_from_uint32) {
    verified_int<int8_t, throw_overflow> test(static_cast<uint32_t>(0x7F));
}

TEST(verified_intConstruction_TDD, Construct_int8_from_int8) {
    verified_int<int8_t, throw_overflow> test(static_cast<int8_t>(0));
}

TEST(verified_intConstruction_TDD, Construct_int8_from_int16) {
    verified_int<int8_t, throw_overflow> test(static_cast<int16_t>(-0x80));
}

TEST(verified_intConstruction_TDD, Construct_int8_from_int32) {
    verified_int<int8_t, throw_overflow> test(static_cast<int32_t>(0x7F));
}

// -----------------------------------

TEST(verified_intConstruction_TDD, Construct_int8_from_uint8_Overflow) {
    EXPECT_ANY_THROW(({
        verified_int<int8_t, throw_overflow> test(static_cast<uint8_t>(0x80));
    }));
}

TEST(verified_intConstruction_TDD, Construct_int8_from_uint16_Overflow) {
    EXPECT_ANY_THROW(({
        verified_int<int8_t, throw_overflow> test(static_cast<uint16_t>(0x80));
    }));
}

TEST(verified_intConstruction_TDD, Construct_int8_from_uint32_Overflow) {
    EXPECT_ANY_THROW(({
        verified_int<int8_t, throw_overflow> test(static_cast<uint32_t>(0x80));
    }));
}

TEST(verified_intConstruction_TDD, Construct_int8_from_int16_BelowOverflow) {
    EXPECT_ANY_THROW(({
        verified_int<int8_t, throw_overflow> test(static_cast<int16_t>(-0x81));
    }));
}

TEST(verified_intConstruction_TDD, Construct_int8_from_int16_Overflow) {
    EXPECT_ANY_THROW(({
        verified_int<int8_t, throw_overflow> test(static_cast<int16_t>(0x80));
    }));
}

TEST(verified_intConstruction_TDD, Construct_int8_from_int32_BelowOverflow) {
    EXPECT_ANY_THROW(({
        verified_int<int8_t, throw_overflow> test(static_cast<int32_t>(-0x81));
    }));
}

TEST(verified_intConstruction_TDD, Construct_int8_from_int32_Overflow) {
    EXPECT_ANY_THROW(({
        verified_int<int8_t, throw_overflow> test(static_cast<int32_t>(0x80));
    }));
}

// --------------------------------------

// -----------------------------------

TEST(verified_intConstruction_TDD, Construct_uint16_from_uint8) {
    verified_int<uint16_t, throw_overflow> test(static_cast<uint8_t>(0));
}

TEST(verified_intConstruction_TDD, Construct_uint16_from_uint16) {
    verified_int<uint16_t, throw_overflow> test(static_cast<uint16_t>(0));
}

TEST(verified_intConstruction_TDD, Construct_uint16_from_uint32) {
    verified_int<uint16_t, throw_overflow> test(static_cast<uint32_t>(0xFFFF));
}

TEST(verified_intConstruction_TDD, Construct_uint16_from_int8) {
    verified_int<uint16_t, throw_overflow> test(static_cast<int8_t>(0));
}

TEST(verified_intConstruction_TDD, Construct_uint16_from_int16) {
    verified_int<uint16_t, throw_overflow> test(static_cast<int16_t>(0x7FFF));
}

TEST(verified_intConstruction_TDD, Construct_uint16_from_int32) {
    verified_int<uint16_t, throw_overflow> test(static_cast<int32_t>(0));
}

// -----------------------------------

TEST(verified_intConstruction_TDD, Construct_int16_from_uint8) {
    verified_int<int16_t, throw_overflow> test(static_cast<uint8_t>(0));
}

TEST(verified_intConstruction_TDD, Construct_int16_from_uint16) {
    verified_int<int16_t, throw_overflow> test(static_cast<uint16_t>(0));
}

TEST(verified_intConstruction_TDD, Construct_int16_from_uint32) {
    verified_int<int16_t, throw_overflow> test(static_cast<uint32_t>(0x7FFF));
}

TEST(verified_intConstruction_TDD, Construct_int16_from_int8) {
    verified_int<int16_t, throw_overflow> test(static_cast<int8_t>(0));
}

TEST(verified_intConstruction_TDD, Construct_int16_from_int16) {
    verified_int<int16_t, throw_overflow> test(static_cast<int16_t>(0x7FFF));
}

TEST(verified_intConstruction_TDD, Construct_int16_from_int32) {
    verified_int<int16_t, throw_overflow> test(static_cast<int32_t>(0));
}

// -----------------------------------

// =======================================================================================
TEST(verified_intConstruction_TDD, Construct_int32_from_uint32_withUpperLimit) {
    verified_int<int32_t, throw_overflow> test(static_cast<uint32_t>(0x7FFFFFFF));
}
TEST(verified_intConstruction_TDD, Construct_int32_from_uint32_Overflow) {
    EXPECT_ANY_THROW(({
        verified_int<int32_t, throw_overflow> test(static_cast<uint32_t>(0x80000000));
    }));
}
TEST(verified_intConstruction_TDD, Construct_int32_from_int32_withLowerLimit) {
    verified_int<int32_t, throw_overflow> test(static_cast<int32_t>(-0x80000000));
}
} // namespace anonymous
