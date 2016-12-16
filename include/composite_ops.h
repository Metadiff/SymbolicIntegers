//
// Created by alex on 16/12/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_COMPOSITE_OPS_H
#define METADIFF_SYMBOLIC_INTEGERS_COMPOSITE_OPS_H

namespace md {
    namespace sym {
        template <typename I, typename C, typename P>
        bool operator==(Composite<I, C, P> const &lhs, Composite<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        bool operator!=(Composite<I, C, P> const &lhs, Composite<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        bool operator>(Composite<I, C, P> const &lhs, Composite<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        bool operator<(Composite<I, C, P> const &lhs, Composite<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        bool operator>=(Composite<I, C, P> const &lhs, Composite<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        bool operator<=(Composite<I, C, P> const &lhs, Composite<I, C, P> const &rhs);
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_COMPOSITE_OPS_H
