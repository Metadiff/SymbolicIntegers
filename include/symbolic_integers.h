//
// Created by alex on 21/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_SRNT_H
#define METADIFF_SYMBOLIC_INTEGERS_SRNT_H

// External includes
#include <cinttypes>
#include "vector"
#include "memory"
#include "math.h"
#include "exception"

namespace md{
    namespace sym{
        // Define C type
#ifndef C_WIDTH
        typedef int64_t C;
#elif C_WIDTH == 8
        typedef int8_t C;
#elif C_WIDTH == 16
typedef int16_t C;
#elif C_WIDTH == 32
typedef int32_t C;
#else
typedef int64_t C;
#endif

// Define I type
#ifndef I_WIDTH
        typedef uint16_t I;
#elif I_WIDTH == 64
        typedef uint64_t I;
#elif I_WIDTH == 32
typedef uint32_t I;
#elif I_WIDTH == 8
typedef uint8_t I;
#else
typedef uint16_t I;
#endif

// Define P type
#ifndef P_WIDTH
        typedef uint8_t P;
#elif P_WIDTH == 64
        typedef uint64_t P;
#elif P_WIDTH == 32
typedef uint32_t P;
#elif P_WIDTH == 16
typedef uint16_t P;
#else
typedef uint8_t P;
#endif

#define ZERO_DIVISION() {throw std::runtime_error("Attempted division by zero.");}
#define NON_INTEGER_DIVISION() {throw std::runtime_error("The division leads to a non integer monomial/polynomial.");}
#define MISSING_VALUE() {throw std::runtime_error("Missing a symbolic integer value when evaluating the monomial/polynomial.");}

    }
}

#include "base_monomial.h"
#include "base_polynomial.h"
#include "base_registry.h"
#include "monomial_ops.h"
#include "polynomial_ops.h"
#include "extra_ops.h"

#endif //METADIFF_SYMBOLIC_INTEGERS_SRNT_H
