//
// Created by alex on 21/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_H
#define METADIFF_SYMBOLIC_INTEGERS_H

// External includes
#include <type_traits>
#include <limits>
#include "vector"
#include "unordered_map"
#include "memory"
#include "math.h"
#include "exception"

namespace md{
    namespace sym{
        template <typename I>
        using id_print = std::function<std::string(I id)>;

#define ZERO_DIVISION() {throw std::runtime_error("Attempted division by zero.");}
#define NON_INTEGER_DIVISION() {throw std::runtime_error("The division leads to a non integer monomial/polynomial.");}
#define MISSING_VALUE() {throw std::runtime_error("Not enough values provided to evaluate the monomial/polynomial.");}
#define INCOMPATIBLE_VALUES(VAL1, VAL2) {throw std::runtime_error("Automatic value deduction reached to "\
         + std::to_string(VAL1) + " = " + std::to_string(VAL2) + ".");}

    }
}

#include "composite.h"
#include "monomial.h"
#include "polynomial.h"
#include "composite_ops.h"
#include "monomial_ops.h"
#include "polynomial_ops.h"
#include "extra_ops.h"

#include "impl/composite_impl.h"
#include "impl/monomial_impl.h"
#include "impl/polynomial_impl.h"
#include "impl/composite_ops_impl.h"
#include "impl/monomial_ops_impl.h"
#include "impl/polynomial_ops_impl.h"
#include "impl/extra_ops_impl.h"

#endif //METADIFF_SYMBOLIC_INTEGERS_H
