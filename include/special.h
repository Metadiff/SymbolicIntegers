//
// Created by alex on 16/12/16.
//

#ifndef SYMBOLICINTEGERS_SRT_SPECIAL_H
#define SYMBOLICINTEGERS_SRT_SPECIAL_H

namespace md {
    namespace sym {
        template <typename I, typename C, typename P>
        bool grevlex_gt(Composite<I, C, P> const &lhs, Composite<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        bool grevlex_gt(Monomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        bool grevlex_gt(Polynomial<I, C, P> const &lhs, Polynomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> primitive(I const id);

        template <typename I, typename C, typename P>
        Monomial<I, C, P> reduce(Monomial<I, C, P> const & monomial, std::unordered_map<I, C> const & values);

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> reduce(Polynomial<I, C, P> const & polynomial, std::unordered_map<I, C> const & values);

        template <typename I, typename C, typename P>
        std::unordered_map<I, C> deduce_values(ImplicitValues <I, C, P> & implicit_values);
    }
}
#endif //SYMBOLICINTEGERS_SRT_SPECIAL_H
