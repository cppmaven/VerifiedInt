
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
} // namespace anonymous
