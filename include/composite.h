//
// Created by alex on 16/12/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_COMPOSITE_H
#define METADIFF_SYMBOLIC_INTEGERS_COMPOSITE_H

namespace md {
    namespace sym {
        // Forward declaration
        template <typename I, typename C, typename P>
        class Polynomial;

        // Types of composite
        enum CompositeType {
            Id = 0,
            Max = 1,
            Min = 2,
            Ceil = 3,
            Floor = 4
        };

        // Encapsulation of composite
        template <typename I, typename C, typename P>
        class Composite {
        public:
            CompositeType type;
            I id;
            std::pair<std::shared_ptr<Polynomial<I, C, P>>, std::shared_ptr<Polynomial<I, C, P>>> compound;

            Composite(CompositeType type, I id):
                    type(type), id(id) {}

            Composite(CompositeType type, std::shared_ptr<Polynomial<I, C, P>> const left,
                      std::shared_ptr<Polynomial<I, C, P>> const right):
                    type(type), compound({left, right}) {}

            Composite(Composite const & composite):
                    type(composite.type), id(composite.id), compound(composite.compound) {}

            C eval(std::unordered_map<I, C> const &values) const;
        };

        /** @brief Returns a humanly presentable string representation of the Composite
         *
         * @param composite
         * @param print - print function for primitive I
         * @return
         */
        template <typename I, typename C, typename P>
        std::string to_string(Composite<I, C, P> const & composite, id_print<I> print);

        /** @brief Returns a code equivalent string representation of the Composite
         *
         * @param composite
         * @param print - print function for primitive I
         * @return
         */
        template <typename I, typename C, typename P>
        std::string to_code(Composite<I, C, P> const & composite, id_print<I> print);

        template <typename C, typename P>
        std::ostream &operator<<(std::ostream &f, Composite<std::string, C, P> const &composite){
                std::function<std::string(std::string)> identity = [](std::string id) { return id; };
                return  f << to_string(composite,  identity);
        }

        template <typename I, typename C, typename P>
        bool operator==(Composite<I, C, P> const &lhs, Composite<I, C, P> const &rhs);
    }
}

#endif //METADIFF_SYMBOLIC_INTEGERS_COMPOSITE_H
