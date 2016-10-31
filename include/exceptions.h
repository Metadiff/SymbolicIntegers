//
// Created by alex on 21/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_EXCEPTIONS_H
#define METADIFF_SYMBOLIC_INTEGERS_EXCEPTIONS_H

#include "exception"

namespace md {
    namespace sym {
        class NonIntegerDivision : public std::exception {
            const char *what() const throw() {
                return "The requested division leads to a non integer monomial/polynomial";
            }
        };

        class EvaluationFailure : public std::exception {
            const char *what() const throw() {
                return "Trying to evaluate a monomial/polynomial without providing all of the values needed";
            }
        };

        class DivisionByZero : public std::exception {
            const char *what() const throw() {
                return "Attempting division by zero";
            }
        };

        class DifferentRegistries : public std::exception {
            const char *what() const throw() {
                return "Operating on variables from different registries";
            }
        };
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_EXCEPTIONS_H
