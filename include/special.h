//
// Created by alex on 20/12/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_SPECIAL_H
#define METADIFF_SYMBOLIC_INTEGERS_SPECIAL_H

namespace md {
    namespace sym {
        /** Returns a polynomial representing 1 * x^1 + 0,
         * where 'x' is a variable uniquely identifiable by the provided id. */
        template <typename I, typename C, typename P>
        Polynomial<I, C, P> variable(I const id);

        /** True if lhs > rhs according to grevlex ordering (see README). **/
        template <typename I, typename C, typename P>
        bool grevlex_gt(Composite<I, C, P> const &lhs, Composite<I, C, P> const &rhs);

        /** True if lhs > rhs according to grevlex ordering (see README). **/
        template <typename I, typename C, typename P>
        bool grevlex_gt(Monomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs);

        /** True if lhs > rhs according to grevlex ordering (see README). **/
        template <typename I, typename C, typename P>
        bool grevlex_gt(Polynomial<I, C, P> const &lhs, Polynomial<I, C, P> const &rhs);

        /** Reduces the monomial, given the variable assignments provided. */
        template <typename I, typename C, typename P>
        Monomial<I, C, P> reduce(Monomial<I, C, P> const & monomial, std::unordered_map<I, C> const & values);

        /** Reduces the polynomial, given the variable assignments provided. */
        template <typename I, typename C, typename P>
        Polynomial<I, C, P> reduce(Polynomial<I, C, P> const & polynomial, std::unordered_map<I, C> const & values);

        /** Automatically deduces the individual variable assignments based on the
         * system of equations specified by the mapping of Polynomial to a constant value.*/
        template <typename I, typename C, typename P>
        std::unordered_map<I, C> deduce_values(ImplicitValues <I, C, P> const & implicit_values);
    }
}

#endif //METADIFF_SYMBOLIC_INTEGERS_SPECIAL_H
