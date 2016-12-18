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

// Forward declarations and types
namespace md {
    namespace sym {
        template <typename I, typename C, typename P>
        class Composite;
        template <typename I, typename C, typename P>
        class Monomial;
        template <typename I, typename C, typename P>
        class Polynomial;

        template <typename I, typename C, typename P>
        using ImplicitValues = std::vector <std::pair<Polynomial<I, C, P>, C>>;

        template <typename I, typename C, typename P>
        using EntryPair = std::pair<Composite<I, C, P>, P>;

        template <typename I>
        using id_print = std::function<std::string(I id)>;
    }
}

// Headers
#include "composite.h"
#include "monomial.h"
#include "polynomial.h"
#include "monomial_ops.h"
#include "polynomial_ops.h"
#include "extra_ops.h"
#include "special.h"
#include "exceptions.h"
// Implementations
#include "impl/composite_impl.h"
#include "impl/monomial_impl.h"
#include "impl/polynomial_impl.h"
#include "impl/monomial_ops_impl.h"
#include "impl/polynomial_ops_impl.h"
#include "impl/extra_ops_impl.h"
#include "impl/special_impl.h"

#endif //METADIFF_SYMBOLIC_INTEGERS_H
