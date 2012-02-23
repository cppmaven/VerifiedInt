
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

TEST(verified_intDivision_TDD, DividePositive) {
    verified_int<int8_t, throw_overflow> test(0x40);
    EXPECT_NO_THROW(({
        test /= 2;
    }));
}

TEST(verified_intDivision_TDD, DivideNegative) {
    verified_int<int8_t, throw_overflow> test(-0x40);
    EXPECT_NO_THROW(({
        test /= 2;
    }));
}

TEST(verified_intDivision_TDD, SignedMaxDivideNegOne) {
    verified_int<int8_t, throw_overflow> lhs(boost::integer_traits<int8_t>::const_max);
    verified_int<int8_t, throw_overflow> rhs(-1);
    EXPECT_NO_THROW(({
        lhs /= rhs;
    }));
    EXPECT_EQ(lhs, boost::integer_traits<int8_t>::const_min + 1);
}

TEST(verified_intDivision_TDD, UnSignedMaxDivideNegOne) {
    verified_int<uint8_t, throw_overflow> lhs(boost::integer_traits<uint8_t>::const_max);
    verified_int<int8_t, throw_overflow> rhs(-1);
    EXPECT_THROW(({
        lhs /= rhs;
    }), boost::negative_overflow);
}

TEST(verified_intDivision_TDD, SignedMinDivideNegOne) {
    verified_int<int8_t, throw_overflow> lhs(boost::integer_traits<int8_t>::const_min);
    verified_int<int8_t, throw_overflow> rhs(-1);
    EXPECT_THROW(({
        lhs /= rhs;
    }), boost::positive_overflow);
}

TEST(verified_intDivision_TDD, UnSignedMinDivideNegOne) {
    verified_int<uint8_t, throw_overflow> lhs(boost::integer_traits<uint8_t>::const_min);
    verified_int<int8_t, throw_overflow> rhs(-1);
    EXPECT_NO_THROW(({
        lhs /= rhs;
    }));
    EXPECT_EQ(lhs, 0);
}
} // namespace anonymous
