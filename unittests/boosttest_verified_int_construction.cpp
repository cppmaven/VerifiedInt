
//               Copyright Ben Robinson 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//#define BOOST_TEST_MAIN defined
#define BOOST_METAASSERT_UNITTEST defined

#include <boost/test/unit_test.hpp>
#include <boost/integer_traits.hpp>
#include <verified_int.hpp>

namespace {

using boost::integer_traits;

using boost::verified_uint8_t;
using boost::verified_uint16_t;
using boost::verified_uint32_t;
using boost::verified_uint64_t;
using boost::verified_int8_t;
using boost::verified_int16_t;
using boost::verified_int32_t;
using boost::verified_int64_t;

BOOST_AUTO_TEST_CASE(test_verified_uint8_t) {
    BOOST_CHECK_NO_THROW( verified_uint8_t value(static_cast<uint8_t>(0)); );
    BOOST_CHECK_NO_THROW( verified_uint8_t value(static_cast<uint16_t>(0)); );
    BOOST_CHECK_NO_THROW( verified_uint8_t value(static_cast<uint32_t>(0)); );
    BOOST_CHECK_NO_THROW( verified_uint8_t value(static_cast<uint64_t>(0)); );
    BOOST_CHECK_NO_THROW( verified_uint8_t value(static_cast<int8_t>(0)); );
    BOOST_CHECK_NO_THROW( verified_uint8_t value(static_cast<int16_t>(0)); );
    BOOST_CHECK_NO_THROW( verified_uint8_t value(static_cast<int32_t>(0)); );
    BOOST_CHECK_NO_THROW( verified_uint8_t value(static_cast<int64_t>(0)); );

    BOOST_CHECK_NO_THROW( verified_uint8_t value(integer_traits<uint8_t>::const_min); );
    BOOST_CHECK_NO_THROW( verified_uint8_t value(integer_traits<uint16_t>::const_min); );
    BOOST_CHECK_NO_THROW( verified_uint8_t value(integer_traits<uint32_t>::const_min); );
    BOOST_CHECK_NO_THROW( verified_uint8_t value(integer_traits<uint64_t>::const_min); );
    BOOST_CHECK_THROW( verified_uint8_t value(integer_traits<int8_t>::const_min), boost::overflow_detected );
    BOOST_CHECK_THROW( verified_uint8_t value(integer_traits<int16_t>::const_min), boost::overflow_detected );
    BOOST_CHECK_THROW( verified_uint8_t value(integer_traits<int32_t>::const_min), boost::overflow_detected );
    BOOST_CHECK_THROW( verified_uint8_t value(integer_traits<int64_t>::const_min), boost::overflow_detected );

    BOOST_CHECK_NO_THROW( verified_uint8_t value(integer_traits<uint8_t>::const_max); );
    BOOST_CHECK_THROW( verified_uint8_t value(integer_traits<uint16_t>::const_max), boost::overflow_detected );
    BOOST_CHECK_THROW( verified_uint8_t value(integer_traits<uint32_t>::const_max), boost::overflow_detected );
    BOOST_CHECK_THROW( verified_uint8_t value(integer_traits<uint64_t>::const_max), boost::overflow_detected );
    BOOST_CHECK_NO_THROW( verified_uint8_t value(integer_traits<int8_t>::const_max); );
    BOOST_CHECK_THROW( verified_uint8_t value(integer_traits<int16_t>::const_max), boost::overflow_detected );
    BOOST_CHECK_THROW( verified_uint8_t value(integer_traits<int32_t>::const_max), boost::overflow_detected );
    BOOST_CHECK_THROW( verified_uint8_t value(integer_traits<int64_t>::const_max), boost::overflow_detected );
}

BOOST_AUTO_TEST_CASE(test_verified_int8_t) {
    BOOST_CHECK_NO_THROW( verified_int8_t value(static_cast<uint8_t>(0)); );
    BOOST_CHECK_NO_THROW( verified_int8_t value(static_cast<uint16_t>(0)); );
    BOOST_CHECK_NO_THROW( verified_int8_t value(static_cast<uint32_t>(0)); );
    BOOST_CHECK_NO_THROW( verified_int8_t value(static_cast<uint64_t>(0)); );
    BOOST_CHECK_NO_THROW( verified_int8_t value(static_cast<int8_t>(0)); );
    BOOST_CHECK_NO_THROW( verified_int8_t value(static_cast<int16_t>(0)); );
    BOOST_CHECK_NO_THROW( verified_int8_t value(static_cast<int32_t>(0)); );
    BOOST_CHECK_NO_THROW( verified_int8_t value(static_cast<int64_t>(0)); );

    BOOST_CHECK_NO_THROW( verified_int8_t value(integer_traits<uint8_t>::const_min); );
    BOOST_CHECK_NO_THROW( verified_int8_t value(integer_traits<uint16_t>::const_min); );
    BOOST_CHECK_NO_THROW( verified_int8_t value(integer_traits<uint32_t>::const_min); );
    BOOST_CHECK_NO_THROW( verified_int8_t value(integer_traits<uint64_t>::const_min); );
    BOOST_CHECK_NO_THROW( verified_int8_t value(integer_traits<int8_t>::const_min); );
    BOOST_CHECK_THROW( verified_int8_t value(integer_traits<int16_t>::const_min), boost::overflow_detected );
    BOOST_CHECK_THROW( verified_int8_t value(integer_traits<int32_t>::const_min), boost::overflow_detected );
    BOOST_CHECK_THROW( verified_int8_t value(integer_traits<int64_t>::const_min), boost::overflow_detected );

    BOOST_CHECK_THROW( verified_int8_t value(integer_traits<uint8_t>::const_max), boost::overflow_detected );
    BOOST_CHECK_THROW( verified_int8_t value(integer_traits<uint16_t>::const_max), boost::overflow_detected );
    BOOST_CHECK_THROW( verified_int8_t value(integer_traits<uint32_t>::const_max), boost::overflow_detected );
    BOOST_CHECK_THROW( verified_int8_t value(integer_traits<uint64_t>::const_max), boost::overflow_detected );
    BOOST_CHECK_NO_THROW( verified_int8_t value(integer_traits<int8_t>::const_max); );
    BOOST_CHECK_THROW( verified_int8_t value(integer_traits<int16_t>::const_max), boost::overflow_detected );
    BOOST_CHECK_THROW( verified_int8_t value(integer_traits<int32_t>::const_max), boost::overflow_detected );
    BOOST_CHECK_THROW( verified_int8_t value(integer_traits<int64_t>::const_max), boost::overflow_detected );
}
//
//#define GENERATE_CONSTRUCTION_MAX_TESTS(TYPE) \
//BOOST_AUTO_TEST_CASE(construct_max_verified_##TYPE) { \
//    promote<TYPE>::type input = integer_traits<TYPE>::const_max; \
//    BOOST_CHECK_NO_THROW( \
//        verified_##TYPE value_good(input); \
//    ); \
//    input += 1; \
//    BOOST_CHECK_THROW( \
//        verified_##TYPE value_bad(input), \
//        boost::overflow_detected \
//    ); \
//}
//GENERATE_CONSTRUCTION_MAX_TESTS(uint8_t)
//GENERATE_CONSTRUCTION_MAX_TESTS(uint16_t)
////GENERATE_CONSTRUCTION_MAX_TESTS(uint32_t)
////GENERATE_CONSTRUCTION_MAX_TESTS(uint64_t)
//GENERATE_CONSTRUCTION_MAX_TESTS(int8_t)
//GENERATE_CONSTRUCTION_MAX_TESTS(int16_t)
////GENERATE_CONSTRUCTION_MAX_TESTS(int32_t)
////GENERATE_CONSTRUCTION_MAX_TESTS(int64_t)
//#undef GENERATE_CONSTRUCTION_MAX_TESTS
} // namespace anonymous
