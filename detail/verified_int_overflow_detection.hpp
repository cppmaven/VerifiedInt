
//               Copyright Ben Robinson 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//! \brief
// Taken from: http://www.airs.com/blog/archives/327
//
// C has always permitted comparisons between any integer type, and C++ follows its lead. Comparing
// signed types to signed types is straightforward: you sign extend the smaller type. Likewise, when
// comparing unsigned types to unsigned types, you zero extend. When comparing signed and unsigned
// types, the rules are less clear.
//
// The C standard specifies a type ordering: long long > long > int > short > char. If the unsigned
// type appears in that ordering before the signed type, then the signed value is converted to the
// unsigned type. Note that this happens even if the types are the same size (e.g., either
// long long and long or long and int are often the same size). Otherwise, if the signed type
// is larger than the unsigned type, in the sense of having more bits, then the unsigned value
// is converted to the signed type. Otherwise both values are converted to the unsigned type
// which corresponds to the signed type.
//----------------------------------------------------------------------------

#ifndef VERIFIED_INT_OVERFLOW_DETECTION_HPP
#define VERIFIED_INT_OVERFLOW_DETECTION_HPP

#include <boost/cstdint.hpp>
#include <boost/integer_traits.hpp>
#include <boost/type_traits/is_signed.hpp>

namespace boost {

enum overflow_result {
    e_no_overflow = 0,
    e_positive_overflow,
    e_negative_overflow
};

template <
    typename L, bool is_left_signed, bool is_left_larger,
    typename R, bool is_right_signed, bool is_right_larger
>
struct detect_overflow_impl_assignment;

template <
    typename L, bool is_left_signed, bool is_left_larger,
    typename R, bool is_right_signed, bool is_right_larger
>
struct detect_overflow_impl_addition;

template <
    typename L, bool is_left_signed, bool is_left_larger,
    typename R, bool is_right_signed, bool is_right_larger
>
struct detect_overflow_impl_subtraction;

template <
    typename L, bool is_left_signed,
    typename R, bool is_right_signed
>
struct detect_overflow_impl_multiplication;

template <typename L, typename R>
struct detect_overflow {
    static bool const is_left_signed = is_signed<L>::value;
    static bool const is_right_signed = is_signed<R>::value;
    static bool const is_left_larger = sizeof(L) > sizeof(R);
    static bool const is_right_larger = sizeof(L) < sizeof(R);

    static overflow_result detect_assignment_overflow(R const right) {
        return detect_overflow_impl_assignment<L, is_left_signed, is_left_larger,
                                        R, is_right_signed, is_right_larger>::detect_assignment_overflow(right);
    }
    static overflow_result detect_addition_overflow(L const left, R const right) {
        return detect_overflow_impl_addition<L, is_left_signed, is_left_larger,
                                      R, is_right_signed, is_right_larger>::detect_addition_overflow(left, right);
    }
    static overflow_result detect_subtraction_overflow(L const left, R const right) {
        return detect_overflow_impl_subtraction<L, is_left_signed, is_left_larger,
                                         R, is_right_signed, is_right_larger>::detect_subtraction_overflow(left, right);
    }
    static overflow_result detect_multiplication_overflow(L const left, R const right) {
        return detect_overflow_impl_multiplication<L, is_left_signed,
                                      R, is_right_signed>::detect_multiplication_overflow(left, right);
    }
};

// Primary template
template <
    typename L, bool is_left_signed, bool is_left_larger,
    typename R, bool is_right_signed, bool is_right_larger
>
struct detect_overflow_impl_assignment {
    static overflow_result detect_assignment_overflow(R const right) {
        (void)right;
        return e_no_overflow;
    }
};

template <typename L, bool is_left_larger, typename R>
struct detect_overflow_impl_assignment<
    L, false, is_left_larger,
    R, false, true
> {
    static overflow_result detect_assignment_overflow(R const right) {
        overflow_result result = e_no_overflow;
        if (right > integer_traits<L>::const_max) {
            result = e_positive_overflow;
        }
        return result;
    }
};

template <typename L, bool is_left_larger, typename R>
struct detect_overflow_impl_assignment<
    L, true, is_left_larger,
    R, true, true
> {
    static overflow_result detect_assignment_overflow(R const right) {
        overflow_result result = e_no_overflow;
        if (right > integer_traits<L>::const_max) {
            result = e_positive_overflow;
        } else if (right < integer_traits<L>::const_min) {
            result = e_negative_overflow;
        }
        return result;
    }
};

template <typename L, bool is_left_larger, typename R>
struct detect_overflow_impl_assignment<
    L, false, is_left_larger,
    R, true, false
> {
    static overflow_result detect_assignment_overflow(R const right) {
        overflow_result result = e_no_overflow;
        if (right < 0) {
            result = e_negative_overflow;
        }
        return result;
    }
};

template <typename L, bool is_left_larger, typename R>
struct detect_overflow_impl_assignment<
    L, false, is_left_larger,
    R, true, true
> {
    static overflow_result detect_assignment_overflow(R const right) {
        overflow_result result = e_no_overflow;
        if (right > integer_traits<L>::const_max) {
            result = e_positive_overflow;
        } else if (right < 0) {
            result = e_negative_overflow;
        }
        return result;
    }
};

template <typename L, typename R, bool is_right_larger>
struct detect_overflow_impl_assignment<
    L, true, false,
    R, false, is_right_larger
> {
    static overflow_result detect_assignment_overflow(R const right) {
        overflow_result result = e_no_overflow;
        if (right > static_cast<R>(integer_traits<L>::const_max)) {
            result = e_positive_overflow;
        }
        return result;
    }
};

template <typename L, bool is_left_larger, typename R>
struct detect_overflow_impl_addition<
    L, false, is_left_larger,
    R, false, false
> {
    static overflow_result detect_addition_overflow(L const left, R const right) {
        overflow_result result = e_no_overflow;
        if (static_cast<L>(right) > integer_traits<L>::const_max - left) {
            result = e_positive_overflow;
        }
        return result;
    }
};

template <typename L, bool is_left_larger, typename R>
struct detect_overflow_impl_addition<
    L, false, is_left_larger,
    R, false, true
> {
    static overflow_result detect_addition_overflow(L const left, R const right) {
        overflow_result result = e_no_overflow;
        if (right > static_cast<R>(integer_traits<L>::const_max - left)) {
            result = e_positive_overflow;
        }
        return result;
    }
};

template <typename L, typename R, bool is_right_larger>
struct detect_overflow_impl_addition<
    L, true, false,
    R, true, is_right_larger
> {
    static overflow_result detect_addition_overflow(L const left, R const right) {
        overflow_result result = e_no_overflow;
        if (right > 0 && left > integer_traits<L>::const_max - right) {
            result = e_positive_overflow;
        } else if (right < 0 && right < integer_traits<L>::const_min - left) {
            result = e_negative_overflow;
        }
        return result;
    }
};

// For additional performance optimization, this specialization is be provided.
// When the Lhs type is larger at compile time, and the Lhs value is negative at run time,
// positive overflow is impossible and therefore does not need to be further checked at run time.
// Also, when the Lhs type is larger at compile time, and the Lhs value is positive at run time,
// negative underflow is impossible and therefore does not need to be further checked at run time.
template <typename L, typename R, bool is_right_larger>
struct detect_overflow_impl_addition<
    L, true, true,
    R, true, is_right_larger
> {
    static overflow_result detect_addition_overflow(L const left, R const right) {
        overflow_result result = e_no_overflow;
        if (left >= 0) {
            // Negative overflow is impossible here.  Only check for positive overflow.
            if (right > 0 && right > integer_traits<L>::const_max - left) {
                result = e_positive_overflow;
            }
        } else { // left < 0
            // Positive overflow is impossible here.  Only check for negative overflow.
            if (right < 0 && right < integer_traits<L>::const_min - left) {
                result = e_negative_overflow;
            }
        }
        return result;
    }
};

template <typename L, bool is_left_larger, typename R>
struct detect_overflow_impl_addition<
    L, false, is_left_larger,
    R, true, true
> {
    static overflow_result detect_addition_overflow(L const left, R const right) {
        overflow_result result = e_no_overflow;
        if (right > 0 && right > static_cast<R>(integer_traits<L>::const_max - left)) {
            result = e_positive_overflow;
        } else if (right < 0 && right < static_cast<R>(integer_traits<L>::const_min - left)) {
            result = e_negative_overflow;
        }
        return result;
    }
};

template <typename L, bool is_left_larger, typename R>
struct detect_overflow_impl_addition<
    L, false, is_left_larger,
    R, true, false
> {
    static overflow_result detect_addition_overflow(L const left, R const right) {
        overflow_result result = e_no_overflow;
        if (right > 0 && static_cast<L>(right) > integer_traits<L>::const_max - left) {
            result = e_positive_overflow;
        } else if (right < 0 && left < static_cast<L>(integer_traits<L>::const_min - right)) {
            result = e_negative_overflow;
        }
        return result;
    }
};

template <typename L, typename R, bool is_right_larger>
struct detect_overflow_impl_addition<
    L, true, false,
    R, false, is_right_larger
> {
    static overflow_result detect_addition_overflow(L const left, R const right) {
        overflow_result result = e_no_overflow;
        if (right > static_cast<R>(integer_traits<L>::const_max - left)) {
            result = e_positive_overflow;
        }
        return result;
    }
};

template <typename L, typename R, bool is_right_larger>
struct detect_overflow_impl_addition<
    L, true, true,
    R, false, is_right_larger
> {
    static overflow_result detect_addition_overflow(L const left, R const right) {
        overflow_result result = e_no_overflow;
        if (left > 0) {
            if (static_cast<L>(right) > integer_traits<L>::const_max - left) {
                result = e_positive_overflow;
            }
        } // Impossible to cause overflow when left <= 0
        return result;
    }
};

template <typename L, bool is_left_larger, typename R, bool is_right_larger>
struct detect_overflow_impl_subtraction<
    L, false, is_left_larger,
    R, false, is_right_larger
> {
    static overflow_result detect_subtraction_overflow(L const left, R const right) {
        overflow_result result = e_no_overflow;
        if (left < right + integer_traits<L>::const_min) {
            result = e_negative_overflow;
        }
        return result;
    }
};

template <typename L, bool is_left_larger, typename R, bool is_right_larger>
struct detect_overflow_impl_subtraction<
    L, true, is_left_larger,
    R, true, is_right_larger
> {
    static overflow_result detect_subtraction_overflow(L const left, R const right) {
        overflow_result result = e_no_overflow;
        if (right > 0 && left < right + integer_traits<L>::const_min) {
            result = e_negative_overflow;
        } else if (right < 0 && left > integer_traits<L>::const_max + right) {
            result = e_positive_overflow;
        }
        return result;
    }
};

template <typename L, bool is_left_larger, typename R>
struct detect_overflow_impl_subtraction<
    L, false, is_left_larger,
    R, true, false
> {
    static overflow_result detect_subtraction_overflow(L const left, R const right) {
        overflow_result result = e_no_overflow;
        if (right > 0 && left < static_cast<L>(right + integer_traits<L>::const_min + right)) {
            result = e_negative_overflow;
        } else if (right < 0 && left > static_cast<L>(integer_traits<L>::const_max + right)) {
            result = e_positive_overflow;
        }
        return result;
    }
};

template <typename L, bool is_left_larger, typename R>
struct detect_overflow_impl_subtraction<
    L, false, is_left_larger,
    R, true, true
> {
    static overflow_result detect_subtraction_overflow(L const left, R const right) {
        overflow_result result = e_no_overflow;
        if (right > 0 && right > static_cast<R>(left - integer_traits<L>::const_min)) {
            result = e_negative_overflow;
        } else if (right < 0 && static_cast<R>(left) > static_cast<R>(integer_traits<L>::const_max + right)) {
            result = e_positive_overflow;
        }
        return result;
    }
};

template <typename L, bool is_left_larger, typename R>
struct detect_overflow_impl_subtraction<
    L, true, is_left_larger,
    R, false, false
> {
    static overflow_result detect_subtraction_overflow(L const left, R const right) {
        overflow_result result = e_no_overflow;
        if (left >= 0 && left < static_cast<L>(integer_traits<L>::const_min + right)) {
            result = e_negative_overflow;
        } else if (left < 0 && right > static_cast<R>(left - integer_traits<L>::const_min)) {
            result = e_positive_overflow;
        }
        return result;
    }
};

template <typename L, bool is_left_larger, typename R>
struct detect_overflow_impl_subtraction<
    L, true, is_left_larger,
    R, false, true
> {
    static overflow_result detect_subtraction_overflow(L const left, R const right) {
        overflow_result result = e_no_overflow;
        if (right > static_cast<R>(left - integer_traits<L>::const_min)) {
            result = e_negative_overflow;
        }
        return result;
    }
};

template <typename L, typename R>
struct detect_overflow_impl_multiplication<
    L, true,
    R, true
> {
    static overflow_result detect_multiplication_overflow(L const left, R const right) {
        overflow_result result = e_no_overflow;
        if (left != 0 && right != 0) {
            if ((left ^ right) > 0) {
                if (abs(right) > abs(integer_traits<L>::const_max / left)) {
                    result = e_positive_overflow;
                }
            } else {
                if (abs(right) > abs(integer_traits<L>::const_min / left)) {
                    result = e_negative_overflow;
                }
            }
        }
        return result;
    }
};

template <typename L, typename R>
struct detect_overflow_impl_multiplication<
    L, false,
    R, false
> {
    static overflow_result detect_multiplication_overflow(L const left, R const right) {
        overflow_result result = e_no_overflow;
        if (left != 0 && right != 0) {
            if (right > integer_traits<L>::const_max / left) {
                result = e_positive_overflow;
            }
        }
        return result;
    }
};

template <typename L, typename R>
struct detect_overflow_impl_multiplication<
    L, false,
    R, true
> {
    static overflow_result detect_multiplication_overflow(L const left, R const right) {
        overflow_result result = e_no_overflow;
        if (left != 0 && right != 0) {
            if ((left ^ right) > 0) {
                if (abs(right) > integer_traits<L>::const_max / left) {
                    result = e_positive_overflow;
                }
            } else {
                if (abs(right) > integer_traits<L>::const_min / left) {
                    result = e_negative_overflow;
                }
            }
        }
        return result;
    }
};

template <typename L, typename R>
struct detect_overflow_impl_multiplication<
    L, true,
    R, false
> {
    static overflow_result detect_multiplication_overflow(L const left, R const right) {
        overflow_result result = e_no_overflow;
        if (left != 0 && right != 0) {
            if ((left ^ right) > 0) {
                if (right > integer_traits<L>::const_max / left) {
                    result = e_positive_overflow;
                }
            } else {
                if (right > integer_traits<L>::const_min / left) {
                    result = e_negative_overflow;
                }
            }
        }
        return result;
    }
};
} // namespace boost

#endif // VERIFIED_INT_OVERFLOW_DETECTION_HPP
