
//               Copyright Ben Robinson 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_METAASSERT_UNITTEST defined

#include <testsystem.hpp>
#include <stringutils.hpp>
#include <climits>
#include <boost/integer_traits.hpp>
#include "verified_int.hpp"

namespace {

using boost::verified_int;
using boost::throw_overflow;

TEST(verified_intMultiplication_TDD, MultiplyZero) {
    verified_int<int8_t, throw_overflow> test(0x10);
    EXPECT_NO_THROW(({
        test *= 0;
    }));
}

TEST(verified_intMultiplication_TDD, MultiplyPositive) {
    verified_int<int8_t, throw_overflow> test(0x10);
    EXPECT_NO_THROW(({
        test *= 4;
    }));
}

TEST(verified_intMultiplication_TDD, MultiplyPositiveOutOfBounds) {
    verified_int<int8_t, throw_overflow> test(0x10);
    EXPECT_ANY_THROW(({
        test *= 16;
    }));
}

TEST(verified_intMultiplication_TDD, MultiplyNegative) {
    verified_int<int8_t, throw_overflow> test(0x10);
    EXPECT_NO_THROW(({
        test *= -4;
    }));
}

TEST(verified_intMultiplication_TDD, MultiplyNegativeOutOfBounds) {
    verified_int<int8_t, throw_overflow> test(0x10);
    EXPECT_ANY_THROW(({
        test *= -16;
    }));
}

TEST(verified_intMultiplication_TDD, OverflowPositiveUnsigned) {
    verified_int<uint8_t, throw_overflow> lhs(0x10);
    verified_int<uint8_t, throw_overflow> rhs(0x10);
    EXPECT_ANY_THROW(({
        lhs *= rhs;
    }));
}
TEST(verified_intMultiplication_TDD, OverflowPositiveSigned) {
    verified_int<int8_t, throw_overflow> lhs(0x10);
    verified_int<int8_t, throw_overflow> rhs(0x08);
    EXPECT_ANY_THROW(({
        lhs *= rhs;
    }));
}

TEST(verified_intMultiplication_TDD, OverflowPositiveNegNeg) {
    verified_int<int8_t, throw_overflow> lhs(-0x10);
    verified_int<int8_t, throw_overflow> rhs(-0x08);
    EXPECT_ANY_THROW(({
        lhs *= rhs;
    }));
}

TEST(verified_intMultiplication_TDD, NegativeOverflowPosNeg) {
    verified_int<int8_t, throw_overflow> lhs(13);
    verified_int<int8_t, throw_overflow> rhs(-10);
    EXPECT_ANY_THROW(({
        lhs *= rhs;
    }));
}
TEST(verified_intMultiplication_TDD, NegativeOverflowNegPos) {
    verified_int<int8_t, throw_overflow> lhs(-13);
    verified_int<int8_t, throw_overflow> rhs(10);
    EXPECT_ANY_THROW(({
        lhs *= rhs;
    }));
}

TEST(verified_intMultiplication_TDD, NoOverflowPositiveUnsigned) {
    verified_int<uint8_t, throw_overflow> lhs(0x10);
    verified_int<uint8_t, throw_overflow> rhs(0x0F);
    EXPECT_NO_THROW(({
        lhs *= rhs;
    }));
}
TEST(verified_intMultiplication_TDD, NoOverflowPositiveSigned) {
    verified_int<int8_t, throw_overflow> lhs(0x0F);
    verified_int<int8_t, throw_overflow> rhs(0x08);
    EXPECT_NO_THROW(({
        lhs *= rhs;
    }));
}

TEST(verified_intMultiplication_TDD, NoOverflowPositiveNegNeg) {
    verified_int<int8_t, throw_overflow> lhs(-0x0F);
    verified_int<int8_t, throw_overflow> rhs(-0x08);
    EXPECT_NO_THROW(({
        lhs *= rhs;
    }));
}

TEST(verified_intMultiplication_TDD, NoNegativeOverflowPosNeg) {
    verified_int<int8_t, throw_overflow> lhs(12);
    verified_int<int8_t, throw_overflow> rhs(-10);
    EXPECT_NO_THROW(({
        lhs *= rhs;
    }));
}

TEST(verified_intMultiplication_TDD, NoNegativeOverflowNegPos) {
    verified_int<int8_t, throw_overflow> lhs(-12);
    verified_int<int8_t, throw_overflow> rhs(10);
    EXPECT_NO_THROW(({
        lhs *= rhs;
    }));
}

TEST(verified_intMultiplication_TDD, SignedMaxTimesNegOne) {
    verified_int<int8_t, throw_overflow> lhs(boost::integer_traits<int8_t>::const_max);
    verified_int<int8_t, throw_overflow> rhs(-1);
    EXPECT_NO_THROW(({
        lhs *= rhs;
    }));
    EXPECT_EQ(lhs, boost::integer_traits<int8_t>::const_min + 1);
}

TEST(verified_intMultiplication_TDD, UnSignedMaxTimesNegOne) {
    verified_int<uint8_t, throw_overflow> lhs(boost::integer_traits<uint8_t>::const_max);
    verified_int<int8_t, throw_overflow> rhs(-1);
    EXPECT_ANY_THROW(({
        lhs *= rhs;
    }));
}

TEST(verified_intMultiplication_TDD, SignedMinTimesNegOne) {
    verified_int<int8_t, throw_overflow> lhs(boost::integer_traits<int8_t>::const_min);
    verified_int<int8_t, throw_overflow> rhs(-1);
    EXPECT_ANY_THROW(({
        lhs *= rhs;
    }));
}

TEST(verified_intMultiplication_TDD, UnSignedMinTimesNegOne) {
    verified_int<uint8_t, throw_overflow> lhs(boost::integer_traits<uint8_t>::const_min);
    verified_int<int8_t, throw_overflow> rhs(-1);
    EXPECT_NO_THROW(({
        lhs *= rhs;
    }));
    EXPECT_EQ(lhs, 0);
}

} // namespace anonymous
