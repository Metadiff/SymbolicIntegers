//
// Created by alex on 21/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_EXCEPTIONS_H
#define METADIFF_SYMBOLIC_INTEGERS_EXCEPTIONS_H
namespace md {
    namespace sym {
        class NonIntegerDivision : public std::exception {
            virtual const char *what() const throw() {
                return "The requested division leads to a non integer monomial/polynomial";
            }
        };

        class EvaluationFailure : public std::exception {
            virtual const char *what() const throw() {
                return "Trying to evaluate a monomial/polynomial without providing the values for all variables";
            }
        };
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_EXCEPTIONS_H
