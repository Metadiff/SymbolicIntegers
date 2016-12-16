//
// Created by alex on 16/12/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_COMPOSITE_OPS_IMPL_H
#define METADIFF_SYMBOLIC_INTEGERS_COMPOSITE_OPS_IMPL_H

namespace md {
    namespace sym {
        template <typename I, typename C, typename P>
        bool operator==(Composite<I, C, P> const &lhs, Composite<I, C, P> const &rhs){
            if(lhs.type != rhs.type) {
                return false;
            }
            switch (lhs.type) {
                case Id: return lhs.id == rhs.id;
                default: return *lhs.compound.first == *rhs.compound.first &&
                                *lhs.compound.second == *rhs.compound.second;
            }
        }

        template <typename I, typename C, typename P>
        bool operator!=(Composite<I, C, P> const &lhs, Composite<I, C, P> const &rhs){
            return ! (lhs == rhs);
        }

        template <typename I, typename C, typename P>
        bool operator>(Composite<I, C, P> const &lhs, Composite<I, C, P> const &rhs){
            switch (lhs.type) {
                case Id: switch (rhs.type) {
                        case Id: return lhs.id > rhs.id;
                        default: return true;
                    }
                case Max: switch (rhs.type) {
                        case Id: return false;
                        case Max: {
                            if (*lhs.compound.first == *rhs.compound.first) {
//                                return *lhs.compound.second > *rhs.compound.second;
                                // TODO
                                return true;
                            } else {
                                // TODO
                                return true;
//                                return *lhs.compound.first > *rhs.compound.first;
                            }
                        }
                        default: return true;
                    }
                case Min: switch (rhs.type) {
                        case Id: return false;
                        case Max: return false;
                        case Min: {
                            if (*lhs.compound.first == *rhs.compound.first) {
                                // TODO
                                return true;
//                                return *lhs.compound.second > *rhs.compound.second;
                            } else {
                                // TODO
                                return true;
//                                return *lhs.compound.first > *rhs.compound.first;
                            }
                        }
                        default: return true;
                    }
                case Ceil: switch (rhs.type) {
                        case Floor: return true;
                        case Ceil: {
                            if (*lhs.compound.first == *rhs.compound.first) {
                                // TODO
                                return true;
//                                return *lhs.compound.second > *rhs.compound.second;
                            } else {
                                // TODO
                                return true;
//                                return *lhs.compound.first > *rhs.compound.first;
                            }
                        }
                        default: return false;
                    }
                default: switch (rhs.type) {
                        case Floor: {
                            if (*lhs.compound.first == *rhs.compound.first) {
                                // TODO
                                return true;
//                                return *lhs.compound.second > *rhs.compound.second;
                            } else {
                                // TODO
                                return true;
//                                return *lhs.compound.first > *rhs.compound.first;
                            }
                        }
                        default: return false;
                    }
            }
        }

        template <typename I, typename C, typename P>
        bool operator<(Composite<I, C, P> const &lhs, Composite<I, C, P> const &rhs){
            return rhs > lhs;
        }

        template <typename I, typename C, typename P>
        bool operator>=(Composite<I, C, P> const &lhs, Composite<I, C, P> const &rhs){
            return (lhs > rhs) || lhs == rhs;
        }

        template <typename I, typename C, typename P>
        bool operator<=(Composite<I, C, P> const &lhs, Composite<I, C, P> const &rhs) {
            return (lhs < rhs) || lhs == rhs;
        }
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_COMPOSITE_OPS_IMPL_H
