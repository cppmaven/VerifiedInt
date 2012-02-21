
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

TEST(verified_intModulus_TDD, ModulusPositiveEven) {
    verified_int<int8_t, throw_overflow> test(0x40);
    EXPECT_NO_THROW(({
        test %= 2;
    }));
    EXPECT_EQ(0, test) << ::test_system::toStdString(test);
}

TEST(verified_intModulus_TDD, ModulusPositiveOdd) {
    verified_int<int8_t, throw_overflow> test(0x41);
    EXPECT_NO_THROW(({
        test %= 2;
    }));
    EXPECT_EQ(1, test) << ::test_system::toStdString(test);
}

TEST(verified_intModulus_TDD, ModulusNegativeEven) {
    verified_int<int8_t, throw_overflow> test(-0x40);
    EXPECT_NO_THROW(({
        test %= 2;
    }));
    EXPECT_EQ(0, test) << ::test_system::toStdString(test);
}

TEST(verified_intModulus_TDD, ModulusNegativeOdd) {
    verified_int<int8_t, throw_overflow> test(-0x41);
    EXPECT_NO_THROW(({
        test %= 2;
    }));
    EXPECT_EQ(-1, test) << ::test_system::toStdString(test);
}
} // namespace anonymous
