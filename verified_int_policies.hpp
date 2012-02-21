
//               Copyright Ben Robinson 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef VERIFIED_INT_POLICIES_HPP
#define VERIFIED_INT_POLICIES_HPP

#include <cassert>
#include <exception>
#include <boost/throw_exception.hpp>
#include <boost/integer_traits.hpp>
#include "detail/verified_int_overflow_detection.hpp"

namespace boost {

template <typename L>
struct ignore_overflow {
    template <typename R>
    static L verify_assignment(R const right) {
        return right;
    }
    template <typename R>
    static L verify_addition(L const left, R const right) {
        return (left + right);
    }
    template <typename R>
    static L verify_subtraction(L const left, R const right) {
        return (left - right);
    }
    template <typename R>
    static L verify_multiplication(L const left, R const right) {
        return (left * right);
    }
    template <typename R>
    static L verify_division(L const left, R const right) {
        return (left / right);
    }
    template <typename R>
    static L verify_modulus(L const left, R const right) {
        return (left % right);
    }
};

struct overflow_detected : virtual std::exception
{
    virtual char const *what() const throw()
    {
        return "boost::overflow_detected";
    }
};

template <typename L>
struct throw_overflow {
    template <typename R>
    static L verify_assignment(R const right) {
        if (detect_overflow<L, R>::detect_assignment_overflow(right) != e_no_overflow) {
            BOOST_THROW_EXCEPTION(overflow_detected());
        }
        return right;
    }
    template <typename R>
    static L verify_addition(L const left, R const right) {
        if (detect_overflow<L, R>::detect_addition_overflow(left, right) != e_no_overflow) {
            BOOST_THROW_EXCEPTION(overflow_detected());
        }
        return left + right;
    }
    template <typename R>
    static L verify_subtraction(L const left, R const right) {
        if (detect_overflow<L, R>::detect_subtraction_overflow(left, right) != e_no_overflow) {
            BOOST_THROW_EXCEPTION(overflow_detected());
        }
        return left - right;
    }
    template <typename R>
    static L verify_multiplication(L const left, R const right) {
        if (detect_overflow<L, R>::detect_multiplication_overflow(left, right) != e_no_overflow) {
            BOOST_THROW_EXCEPTION(overflow_detected());
        }
        return left * right;
    }
    template <typename R>
    static L verify_division(L const left, R const right) {
        return left / right;
    }
    template <typename R>
    static L verify_modulus(L const left, R const right) {
        return left % right;
    }
};

template <typename L>
struct assert_overflow {
    template <typename R>
    static L verify_assignment(R const right) {
        assert((!detect_overflow<L, R>::detect_assignment_overflow(right) == e_no_overflow));
        return right;
    }
    template <typename R>
    static L verify_addition(L const left, R const right) {
        assert((detect_overflow<L, R>::detect_addition_overflow(left, right) == e_no_overflow));
        return left + right;
    }
    template <typename R>
    static L verify_subtraction(L const left, R const right) {
        assert((detect_overflow<L, R>::detect_subtraction_overflow(left, right) == e_no_overflow));
        return left - right;
    }
    template <typename R>
    static L verify_multiplication(L const left, R const right) {
        assert((detect_overflow<L, R>::detect_multiplication_overflow(left, right) == e_no_overflow));
        return left * right;
    }
    template <typename R>
    static L verify_division(L const left, R const right) {
        return left / right;
    }
    template <typename R>
    static L verify_modulus(L const left, R const right) {
        return left % right;
    }
};

template <typename L>
struct saturate_overflow {
    template <typename R>
    static L verify_assignment(R const right) {
        L result;
        overflow_result overflowResult = detect_overflow<L, R>::detect_assignment_overflow(right);
        if (overflowResult == e_positive_overflow) {
            result = integer_traits<L>::const_max;
        } else if (overflowResult == e_negative_overflow) {
            result = integer_traits<L>::const_min;
        } else {
            result = right;
        }
        return result;
    }
    template <typename R>
    static L verify_addition(L const left, R const right) {
        L result;
        overflow_result overflowResult = detect_overflow<L, R>::detect_addition_overflow(left, right);
        if (overflowResult == e_positive_overflow) {
            result = integer_traits<L>::const_max;
        } else if (overflowResult == e_negative_overflow) {
            result = integer_traits<L>::const_min;
        } else {
            result = left + right;
        }
        return result;
    }
    template <typename R>
    static L verify_subtraction(L const left, R const right) {
        L result;
        overflow_result overflowResult = detect_overflow<L, R>::detect_subtraction_overflow(left, right);
        if (overflowResult == e_positive_overflow) {
            result = integer_traits<L>::const_max;
        } else if (overflowResult == e_negative_overflow) {
            result = integer_traits<L>::const_min;
        } else {
            result = left - right;
        }
        return result;
    }
    template <typename R>
    static L verify_multiplication(L const left, R const right) {
        L result;
        overflow_result overflowResult = detect_overflow<L, R>::detect_multiplication_overflow(left, right);
        if (overflowResult == e_positive_overflow) {
            result = integer_traits<L>::const_max;
        } else if (overflowResult == e_negative_overflow) {
            result = integer_traits<L>::const_min;
        } else {
            result = left * right;
        }
        return result;
    }
    template <typename R>
    static L verify_division(L const left, R const right) {
        return left / right;
    }
    template <typename R>
    static L verify_modulus(L const left, R const right) {
        return left % right;
    }
};

template <typename L>
struct nan_overflow {
    template <typename R>
    static L verify_assignment(R const right) {
        L result;
        if (detect_overflow<L, R>::detect_assignment_overflow(right) != e_no_overflow) {
            result = integer_traits<L>::const_max;
        } else {
            result = right;
        }
        return result;
    }
    template <typename R>
    static L verify_addition(L const left, R const right) {
        L result = integer_traits<L>::const_max;
        if (detect_overflow<L, R>::detect_addition_overflow(left, right) == e_no_overflow
                && left != result) {
            result = left + right;
        }
        return result;
    }
    template <typename R>
    static L verify_subtraction(L const left, R const right) {
        L result = integer_traits<L>::const_max;
        if (detect_overflow<L, R>::detect_subtraction_overflow(left, right) == e_no_overflow
                && left != result) {
            result = left - right;
        }
        return result;
    }
    template <typename R>
    static L verify_multiplication(L const left, R const right) {
        L result = integer_traits<L>::const_max;
        if (detect_overflow<L, R>::detect_multiplication_overflow(left, right) == e_no_overflow
                && left != result) {
            result = left * right;
        }
        return result;
    }
    template <typename R>
    static L verify_division(L const left, R const right) {
        L result;
        if (left == integer_traits<L>::const_max) {
            result = integer_traits<L>::const_max;
        } else {
            result = left / right;
        }
        return result;
    }
    template <typename R>
    static L verify_modulus(L const left, R const right) {
        L result;
        if (left == integer_traits<L>::const_max) {
            result = integer_traits<L>::const_max;
        } else {
            result = left % right;
        }
        return result;
    }
};
} // namespace boost

#endif // VERIFIED_INT_POLICIES_HPP
