//
// Created by alex on 21/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_NON_TEMPLATED_H
#define METADIFF_SYMBOLIC_INTEGERS_NON_TEMPLATED_H

#include <cinttypes>

// Define C type
#ifndef C_WIDTH
typedef int32_t C;
#elif C_WIDTH == 8
typedef int8_t C;
#elif C_WIDTH == 16
typedef int16_t C;
#elif C_WIDTH == 64
typedef int64_t C;
#else
typedef int32_t C;
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
#elif I_WIDTH == 64
typedef uint64_t P;
#elif I_WIDTH == 32
typedef uint32_t P;
#elif I_WIDTH == 16
typedef uint16_t P;
#else
typedef uint8_t P;
#endif

#include "string"
#include "math.h"
#include "limits"
#include "vector"
#include "memory"
#include "exceptions.h"
#include "base_monomial.h"
#include "base_polynomial.h"
#include "base_registry.h"
#include "monomial_ops.h"
#include "polynomial_ops.h"
#include "extra_ops.h"

#endif //METADIFF_SYMBOLIC_INTEGERS_NON_TEMPLATED_H
