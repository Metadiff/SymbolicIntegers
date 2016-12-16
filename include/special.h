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
        Polynomial<I, C, P> primitive(I id);

        template <typename I, typename C, typename P>
        void reduce_polynomials(std::vector <std::pair<Polynomial<I, C, P>, C>> &implicit_values,
        std::unordered_map<I, C> const & values);

        template <typename I, typename C, typename P>
        std::unordered_map<I, C> deduce_values(std::vector <std::pair<Polynomial<I, C, P>, C>> implicit_values);
    }
}
#endif //SYMBOLICINTEGERS_SRT_SPECIAL_H
