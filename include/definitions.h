//
// Created by alex on 20/12/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_DEFINITIONS_H
#define METADIFF_SYMBOLIC_INTEGERS_DEFINITIONS_H

// External includes
#include <type_traits>
#include <limits>
#include "vector"
#include "unordered_map"
#include "memory"
#include "math.h"
#include "exception"

namespace md {
    namespace sym {
        // Forward declarations of classes
        template <typename I, typename C, typename P>
        class Composite;
        template <typename I, typename C, typename P>
        class Monomial;
        template <typename I, typename C, typename P>
        class Polynomial;

        /** The type represent a mapping from a Polynomial to a value, used for variable deduction. */
        template <typename I, typename C, typename P>
        using ImplicitValues = std::vector <std::pair<Polynomial<I, C, P>, C>>;

        /** The type represents a function which specifies how to convert an identifier type `I` to string. */
        template <typename I>
        using id_print = std::function<std::string(I id)>;

        // Helper functions for exceptions
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

            template<typename I, typename C, typename P>
            inline std::runtime_error incompatible_values(Polynomial<I, C, P> const &poly, C expected, C deduced) {
                return std::runtime_error("Automatic value deduction failed for " +
                                          to_string(poly, id_print<I>([](std::string id) { return id; })) +
                                          " = " + std::to_string(expected) + ", but deduced it to be "
                                          + std::to_string(deduced) + ".");
            }
        }
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_DEFINITIONS_H
