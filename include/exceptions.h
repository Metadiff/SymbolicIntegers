//
// Created by alex on 18/12/16.
//

#ifndef SYMBOLICINTEGERS_EXCEPTIONS_H
#define SYMBOLICINTEGERS_EXCEPTIONS_H

namespace md {
    namespace sym{
        namespace exceptions {

            inline std::runtime_error division_by_zero(){
                return std::runtime_error("Attempted division by zero.");
            }

            inline std::runtime_error non_integer_division() {
                return std::runtime_error("The division leads to a non integer monomial/polynomial.");
            }

            inline std::runtime_error missing_value(){
                return std::runtime_error("Not enough values provided to evaluate the monomial/polynomial.");
            }

            template <typename I, typename C, typename P>
            inline std::runtime_error incompatible_values(Polynomial<I, C, P> & poly, C expected, C deduced) {
                return std::runtime_error("Automatic value deduction failed for " +
                                          to_string(poly, id_print<I>([] (std::string id) {return id;})) +
                                          " = " + std::to_string(expected) + ", but deduced it to be "
                                          + std::to_string(deduced) + ".");
            }
        }
    }
}
#endif //SYMBOLICINTEGERS_EXCEPTIONS_H
