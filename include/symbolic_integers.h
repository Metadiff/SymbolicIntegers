//
// Created by alex on 21/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_SRT_H
#define METADIFF_SYMBOLIC_INTEGERS_SRT_H

// External includes
#include <type_traits>
#include <limits>
#include "vector"
#include "memory"
#include "math.h"
#include "exception"

namespace md{
    namespace sym{
#define ZERO_DIVISION() {throw std::runtime_error("Attempted division by zero.");}
#define NON_INTEGER_DIVISION() {throw std::runtime_error("The division leads to a non integer monomial/polynomial.");}
#define MISSING_VALUE() {throw std::runtime_error("Missing a symbolic integer value when evaluating the monomial/polynomial.");}
    }
}

#include "monomial.h"
#include "polynomial.h"
#include "registry.h"
#include "monomial_ops.h"
#include "polynomial_ops.h"
#include "extra_ops.h"

#include "impl/monomial_impl.h"
#include "impl/polynomial_impl.h"
#include "impl/registry_impl.h"
#include "impl/monomial_ops_impl.h"
#include "impl/polynomial_ops_impl.h"
#include "impl/extra_ops_impl.h"

#endif //METADIFF_SYMBOLIC_INTEGERS_SRT_H
