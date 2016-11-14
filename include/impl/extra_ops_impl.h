//
// Created by alex on 29/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_SRT_EXTRA_OPS_IMPL_H
#define METADIFF_SYMBOLIC_INTEGERS_SRT_EXTRA_OPS_IMPL_H

namespace md {
    namespace sym {
        template<typename C1, typename C2,
                typename = std::enable_if<std::is_integral<C1>::value>,
                typename = std::enable_if<std::is_integral<C2>::value>>
        auto floor(C1 const dividend, C2 const divisor) -> decltype(dividend / divisor) {
            if(divisor == 0){
                ZERO_DIVISION()
            }
            if((dividend >= 0 and divisor > 0)
               or (dividend <= 0 and divisor < 0)
               or (dividend % divisor == 0)){
                return (dividend / divisor);
            }
            return dividend / divisor - 1;
        };

        template<typename C1, typename C2,
                typename = std::enable_if<std::is_integral<C1>::value>,
                typename = std::enable_if<std::is_integral<C2>::value>>
        auto ceil(C1 const dividend, C2 const divisor) -> decltype(dividend / divisor) {
            if(divisor == 0){
                ZERO_DIVISION()
            }
            if((dividend >= 0 and divisor < 0) or (dividend <= 0 and divisor > 0)){
                return dividend / divisor;
            }
            if(dividend % divisor == 0){
                return dividend / divisor;
            }
            return dividend / divisor + 1;
        };

        template<typename C1, typename C2,
                typename = std::enable_if<std::is_integral<C1>::value>,
                typename = std::enable_if<std::is_integral<C2>::value>>
        auto min(C1 const left, C2 const right) -> decltype(left + right){
            return left < right ? left : right;
        };

        template<typename C1, typename C2,
                typename = std::enable_if<std::is_integral<C1>::value>,
                typename = std::enable_if<std::is_integral<C2>::value>>
        auto max(C1 const left, C2 const right) -> decltype(left + right){
            return left > right ? left : right;
        };

        template <typename C, typename I, typename P>
        Monomial<C, I, P> floor(Monomial<C, I, P> const &dividend, Monomial<C, I, P> const &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                auto dividend_value = dividend.eval();
                auto divisor_value = divisor.eval();
                return Monomial<C, I, P>(floor(dividend_value, divisor_value));
            }
            try {
                return dividend / divisor;
            } catch (const std::runtime_error& e) {
                registry<C, I, P>()->floor_registry.push_back({registry<C, I, P>()->total_ids, {dividend, divisor}});
                return registry<C, I, P>()->new_monomial_variable();
            }
        };

        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<C, I, P> floor(Monomial<C, I, P> const &dividend, T const divisor) {
            if (dividend.is_constant()) {
                return Monomial<C, I, P>(floor(dividend.eval(), divisor));
            }
            if (dividend.coefficient % divisor == 0) {
                return dividend / divisor;
            }
            registry<C, I, P>()->floor_registry.push_back(
                    {registry<C, I, P>()->total_ids, {dividend, divisor}});
            return registry<C, I, P>()->new_monomial_variable();
        };

        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<C, I, P> floor(T const dividend, Monomial<C, I, P> const &divisor) {
            if (divisor.is_constant()) {
                return Monomial<C, I, P>(floor(dividend, divisor.eval()));
            }
            registry<C, I, P>()->floor_registry.push_back(
                    {registry<C, I, P>()->total_ids, {dividend, divisor}});
            return registry<C, I, P>()->new_monomial_variable();
        };

        template <typename C, typename I, typename P>
        Polynomial<C, I, P> floor(Polynomial<C, I, P> const &dividend, Polynomial<C, I, P> const &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Polynomial<C, I, P>(dividend.eval() / divisor.eval());
            }
            try {
                return dividend / divisor;
            } catch (const std::runtime_error& e) {
                registry<C, I, P>()->floor_registry.push_back({registry<C, I, P>()->total_ids, {dividend, divisor}});
                return registry<C, I, P>()->new_variable();
            }
        };

        template <typename C, typename I, typename P>
        Polynomial<C, I, P> floor(Polynomial<C, I, P> const &dividend, Monomial<C, I, P> const &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Polynomial<C, I, P>(floor(dividend.eval(), divisor.eval()));
            }
            try {
                return dividend / divisor;
            } catch (const std::runtime_error& e) {
                registry<C, I, P>()->floor_registry.push_back({registry<C, I, P>()->total_ids, {dividend, divisor}});
                return registry<C, I, P>()->new_variable();
            }
        };

        template <typename C, typename I, typename P>
        Polynomial<C, I, P> floor(Monomial<C, I, P> const &dividend, Polynomial<C, I, P> const &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Polynomial<C, I, P>(floor(dividend.eval(), divisor.eval()));
            }
            try {
                return dividend / divisor;
            } catch (const std::runtime_error& e) {
                registry<C, I, P>()->floor_registry.push_back({registry<C, I, P>()->total_ids, {dividend, divisor}});
                return registry<C, I, P>()->new_variable();
            }
        };

        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<C, I, P> floor(Polynomial<C, I, P> const &dividend, T const divisor) {
            if (dividend.is_constant()) {
                return Polynomial<C, I, P>(floor(dividend.eval(), divisor));
            }
            bool all_divisible = true;
            for(auto i=0;i<dividend.monomials.size();++i){
                if(dividend.monomials[i].coefficient % divisor != 0){
                    all_divisible = false;
                }
            }
            if(all_divisible){
                return dividend / divisor;
            }
            registry<C, I, P>()->floor_registry.push_back(
                    {registry<C, I, P>()->total_ids, {dividend, divisor}});
            return registry<C, I, P>()->new_variable();
        };

        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<C, I, P> floor(T const dividend, Polynomial<C, I, P> const &divisor) {
            if (divisor.is_constant()) {
                return Polynomial<C, I, P>(floor(dividend, divisor.eval()));
            }
            registry<C, I, P>()->floor_registry.push_back(
                    {registry<C, I, P>()->total_ids, {dividend, divisor}});
            return registry<C, I, P>()->new_variable();
        };

        template <typename C, typename I, typename P>
        Monomial<C, I, P> ceil(Monomial<C, I, P> const &dividend, Monomial<C, I, P> const &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Monomial<C, I, P>(ceil(dividend.eval(), divisor.eval()));
            }
            try {
                return dividend / divisor;
            } catch (const std::runtime_error& e) {
                registry<C, I, P>()->ceil_registry.push_back({registry<C, I, P>()->total_ids, {dividend, divisor}});
                return registry<C, I, P>()->new_monomial_variable();
            }
        };

        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<C, I, P> ceil(Monomial<C, I, P> const &dividend, T const divisor) {
            if (dividend.is_constant()) {
                return Monomial<C, I, P>(ceil(dividend.eval(), divisor));
            }
            if (dividend.coefficient % divisor == 0) {
                return dividend / divisor;
            }
            registry<C, I, P>()->ceil_registry.push_back(
                    {registry<C, I, P>()->total_ids, {dividend, divisor}});
            return registry<C, I, P>()->new_monomial_variable();
        };

        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<C, I, P> ceil(T const dividend, Monomial<C, I, P> const &divisor) {
            if (divisor.is_constant()) {
                return Monomial<C, I, P>(ceil(dividend, divisor.eval()));
            }
            registry<C, I, P>()->ceil_registry.push_back(
                    {registry<C, I, P>()->total_ids, {dividend, divisor}});
            return registry<C, I, P>()->new_monomial_variable();
        };

        template <typename C, typename I, typename P>
        Polynomial<C, I, P> ceil(Polynomial<C, I, P> const &dividend, Polynomial<C, I, P> const &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Polynomial<C, I, P>(ceil(dividend.eval(), divisor.eval()));
            }
            try {
                return dividend / divisor;
            } catch (const std::runtime_error& e) {
                registry<C, I, P>()->ceil_registry.push_back({registry<C, I, P>()->total_ids, {dividend, divisor}});
                return registry<C, I, P>()->new_variable();
            }
        };

        template <typename C, typename I, typename P>
        Polynomial<C, I, P> ceil(Polynomial<C, I, P> const &dividend, Monomial<C, I, P> const &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Polynomial<C, I, P>(ceil(dividend.eval(), divisor.eval()));
            }
            try {
                return dividend / divisor;
            } catch (const std::runtime_error& e) {
                registry<C, I, P>()->ceil_registry.push_back({registry<C, I, P>()->total_ids, {dividend, divisor}});
                return registry<C, I, P>()->new_variable();
            }
        };

        template <typename C, typename I, typename P>
        Polynomial<C, I, P> ceil(Monomial<C, I, P> const &dividend, Polynomial<C, I, P> const &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Polynomial<C, I, P>(ceil(dividend.eval(), divisor.eval()));
            }
            try {
                return dividend / divisor;
            } catch (const std::runtime_error& e) {
                registry<C, I, P>()->ceil_registry.push_back({registry<C, I, P>()->total_ids, {dividend, divisor}});
                return registry<C, I, P>()->new_variable();
            }
        };

        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<C, I, P> ceil(Polynomial<C, I, P> const &dividend, T const divisor) {
            if (dividend.is_constant()) {
                return Polynomial<C, I, P>(ceil(dividend.eval(), divisor));
            }
            bool all_divisible = true;
            for(auto i=0;i<dividend.monomials.size();++i){
                if(dividend.monomials[i].coefficient % divisor != 0){
                    all_divisible = false;
                }
            }
            if(all_divisible){
                return dividend / divisor;
            }
            registry<C, I, P>()->ceil_registry.push_back(
                    {registry<C, I, P>()->total_ids, {dividend, divisor}});
            return registry<C, I, P>()->new_variable();
        };

        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<C, I, P> ceil(T const dividend, Polynomial<C, I, P> const &divisor) {
            if (divisor.is_constant()) {
                return Polynomial<C, I, P>(ceil(dividend, divisor.eval()));
            }
            registry<C, I, P>()->ceil_registry.push_back(
                    {registry<C, I, P>()->total_ids, {dividend, divisor}});
            return registry<C, I, P>()->new_variable();
        };

        template <typename C, typename I, typename P>
        Monomial<C, I, P> min(Monomial<C, I, P> const  &left, Monomial<C, I, P> const  &right){
            if (left.is_constant() and right.is_constant()) {
                return Monomial<C, I, P>(min(left.coefficient, right.coefficient));
            } else {
                registry<C, I, P>()->min_registry.push_back({registry<C, I, P>()->total_ids, {left, right}});
                return registry<C, I, P>()->new_monomial_variable();
            }
        }

        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<C, I, P> min(Monomial<C, I, P> const  &left, T const  &right){
            if (left.is_constant()) {
                return Monomial<C, I, P>(min(left.coefficient, right));
            } else {
                registry<C, I, P>()->min_registry.push_back({registry<C, I, P>()->total_ids, {left, right}});
                return registry<C, I, P>()->new_monomial_variable();
            }
        }

        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<C, I, P> min(T const  &left, Monomial<C, I, P> const  &right){
            if (right.is_constant()) {
                return Monomial<C, I, P>(min(left, right.coefficient));
            } else {
                registry<C, I, P>()->min_registry.push_back({registry<C, I, P>()->total_ids, {left, right}});
                return registry<C, I, P>()->new_monomial_variable();
            }
        }

        template <typename C, typename I, typename P>
        Polynomial<C, I, P> min(Polynomial<C, I, P> const  &left, Polynomial<C, I, P> const  &right){
            if (left.is_constant() and right.is_constant()) {
                return Polynomial<C, I, P>(min(left.eval(), right.eval()));
            } else {
                registry<C, I, P>()->min_registry.push_back({registry<C, I, P>()->total_ids, {left, right}});
                return registry<C, I, P>()->new_variable();
            }
        }

        template <typename C, typename I, typename P>
        Polynomial<C, I, P> min(Polynomial<C, I, P> const  &left, Monomial<C, I, P> const  &right){
            if (left.is_constant() and right.is_constant()) {
                return Polynomial<C, I, P>(min(left.eval(), right.coefficient));
            } else {
                registry<C, I, P>()->min_registry.push_back({registry<C, I, P>()->total_ids, {left, right}});
                return registry<C, I, P>()->new_variable();
            }
        }

        template <typename C, typename I, typename P>
        Polynomial<C, I, P> min(Monomial<C, I, P> const  &left, Polynomial<C, I, P> const  &right){
            if (left.is_constant() and right.is_constant()) {
                return Polynomial<C, I, P>(min(left.coefficient, right.eval()));
            } else {
                registry<C, I, P>()->min_registry.push_back({registry<C, I, P>()->total_ids, {left, right}});
                return registry<C, I, P>()->new_variable();
            }
        }

        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<C, I, P> min(Polynomial<C, I, P> const  &left, T const  &right){
            if (left.is_constant()) {
                return Polynomial<C, I, P>(min(left.eval(), right));
            } else {
                registry<C, I, P>()->min_registry.push_back({registry<C, I, P>()->total_ids, {left, right}});
                return registry<C, I, P>()->new_variable();
            }
        }

        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<C, I, P> min(T const  &left, Polynomial<C, I, P> const  &right){
            if (right.is_constant()) {
                return Polynomial<C, I, P>(min(left, right.eval()));
            } else {
                registry<C, I, P>()->min_registry.push_back({registry<C, I, P>()->total_ids, {left, right}});
                return registry<C, I, P>()->new_variable();
            }
        }

        template <typename C, typename I, typename P>
        Monomial<C, I, P> max(Monomial<C, I, P> const  &left, Monomial<C, I, P> const  &right){
            if (left.is_constant() and right.is_constant()) {
                return Monomial<C, I, P>(max(left.coefficient, right.coefficient));
            } else {
                registry<C, I, P>()->max_registry.push_back({registry<C, I, P>()->total_ids, {left, right}});
                return registry<C, I, P>()->new_monomial_variable();
            }
        }

        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<C, I, P> max(Monomial<C, I, P> const  &left, T const  &right){
            if (left.is_constant()) {
                return Monomial<C, I, P>(max(left.coefficient, right));
            } else {
                registry<C, I, P>()->max_registry.push_back({registry<C, I, P>()->total_ids, {left, right}});
                return registry<C, I, P>()->new_monomial_variable();
            }
        }

        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<C, I, P> max(T const  &left, Monomial<C, I, P> const  &right){
            if (right.is_constant()) {
                return Monomial<C, I, P>(max(left, right.coefficient));
            } else {
                registry<C, I, P>()->max_registry.push_back({registry<C, I, P>()->total_ids, {left, right}});
                return registry<C, I, P>()->new_monomial_variable();
            }
        }

        template <typename C, typename I, typename P>
        Polynomial<C, I, P> max(Polynomial<C, I, P> const  &left, Polynomial<C, I, P> const  &right){
            if (left.is_constant() and right.is_constant()) {
                return Polynomial<C, I, P>(max(left.eval(), right.eval()));
            } else {
                registry<C, I, P>()->max_registry.push_back({registry<C, I, P>()->total_ids, {left, right}});
                return registry<C, I, P>()->new_variable();
            }
        }

        template <typename C, typename I, typename P>
        Polynomial<C, I, P> max(Polynomial<C, I, P> const  &left, Monomial<C, I, P> const  &right){
            if (left.is_constant() and right.is_constant()) {
                return Polynomial<C, I, P>(max(left.eval(), right.coefficient));
            } else {
                registry<C, I, P>()->max_registry.push_back({registry<C, I, P>()->total_ids, {left, right}});
                return registry<C, I, P>()->new_variable();
            }
        }

        template <typename C, typename I, typename P>
        Polynomial<C, I, P> max(Monomial<C, I, P> const  &left, Polynomial<C, I, P> const  &right){
            if (left.is_constant() and right.is_constant()) {
                return Polynomial<C, I, P>(max(left.coefficient, right.eval()));
            } else {
                registry<C, I, P>()->max_registry.push_back({registry<C, I, P>()->total_ids, {left, right}});
                return registry<C, I, P>()->new_variable();
            }
        }

        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<C, I, P> max(Polynomial<C, I, P> const  &left, T const  &right){
            if (left.is_constant()) {
                return Polynomial<C, I, P>(max(left.eval(), right));
            } else {
                registry<C, I, P>()->max_registry.push_back({registry<C, I, P>()->total_ids, {left, right}});
                return registry<C, I, P>()->new_variable();
            }
        }

        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<C, I, P> max(T const  &left, Polynomial<C, I, P> const  &right){
            if (right.is_constant()) {
                return Polynomial<C, I, P>(max(left, right.eval()));
            } else {
                registry<C, I, P>()->max_registry.push_back({registry<C, I, P>()->total_ids, {left, right}});
                return registry<C, I, P>()->new_variable();
            }
        }
    }
}

#endif //METADIFF_SYMBOLIC_INTEGERS_SRT_EXTRA_OPS_IMPL_H
