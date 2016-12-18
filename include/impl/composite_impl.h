//
// Created by alex on 16/12/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_COMPOSITE_IMPL_H
#define METADIFF_SYMBOLIC_INTEGERS_COMPOSITE_IMPL_H

namespace md {
    namespace sym {

        template <typename I, typename C, typename P>
        C Composite<I, C, P>::eval(std::unordered_map<I, C> const &values) const {
            if(type == Id) {
                auto const provided = values.find(id);
                if (provided == values.end()) {
                    throw exceptions::missing_value();
                } else {
                    return provided->second;
                }
            }
            else{
                auto const first_val = compound.first->eval(values);
                auto const second_val = compound.second->eval(values);
                if(type == Max) {
                    return std::max(std::move(first_val), std::move(second_val));
                } else if(type == Min) {
                    return std::min(std::move(first_val), std::move(second_val));
                } else if(type == Ceil) {
                    return ceil(std::move(first_val), std::move(second_val));
                } else if(type == Floor){
                    return floor(std::move(first_val), std::move(second_val));
                } else {
                    return 0;
                }
            }
        }

        template <typename I, typename C, typename P>
        std::string to_string(Composite<I, C, P> const & composite, id_print<I> print){
            switch (composite.type) {
                case Max: return "max(" + to_string(*composite.compound.first, print) + ", "
                                 + to_string(*composite.compound.second, print) + ")";
                case Min: return "min(" + to_string(*composite.compound.first, print) + ", "
                                 + to_string(*composite.compound.second, print) + ")";
                case Ceil: return "ceil(" + to_string(*composite.compound.first, print) + ", "
                                  + to_string(*composite.compound.second, print) + ")";
                case Floor: return "floor(" + to_string(*composite.compound.first, print) + ", "
                                   + to_string(*composite.compound.second, print) + ")";
                default: {
                    return print(composite.id);
                }
            }
        }

        template <typename I, typename C, typename P>
        std::string to_code(Composite<I, C, P> const & composite, id_print<I> print){
            switch (composite.type) {
                case Max: return "max(" + to_code(*composite.compound.first, print) + ", "
                                 + to_code(*composite.compound.second, print) + ")";
                case Min: return "min(" + to_code(*composite.compound.first, print) + ", "
                                 + to_code(*composite.compound.second, print) + ")";
                case Ceil: return "ceil(" + to_code(*composite.compound.first, print) + ", "
                                  + to_code(*composite.compound.second, print) + ")";
                case Floor: return "floor(" + to_code(*composite.compound.first, print) + ", "
                                   + to_code(*composite.compound.second, print) + ")";
                default: {
                    return print(composite.id);
                }
            }
        }

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
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_COMPOSITE_IMPL_H
