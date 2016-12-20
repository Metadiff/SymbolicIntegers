//
// Created by alex on 16/12/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_COMPOSITE_H
#define METADIFF_SYMBOLIC_INTEGERS_COMPOSITE_H

namespace md {
    namespace sym {
        /** Enum for possible types of a Composite expression */
        enum CompositeType {
            Variable = 0,
            Max = 1,
            Min = 2,
            Ceil = 3,
            Floor = 4
        };

        /** A composite expression (tagged union) of a variable or an irreducible function (floor, ceil, max, min) */
        template <typename I, typename C, typename P>
        class Composite {
        public:
            /** The type of the expression */
            CompositeType type;
            /** If the expression is a Variable, the actual identifier of the variable */
            I id;
            /** If the expression is an irreducible function, the two arguments of the function */
            std::pair<std::shared_ptr<Polynomial<I, C, P>>, std::shared_ptr<Polynomial<I, C, P>>> compound;

            /** Constructs a Variable Composite expression with the provided identifier. */
            Composite(I id):
                    type(Variable), id(id) {}

            /** Constructs a Composite expression of irreducible function with the provided arguments. */
            Composite(CompositeType type, std::shared_ptr<Polynomial<I, C, P>> const left,
                      std::shared_ptr<Polynomial<I, C, P>> const right):
                    type(type), compound({left, right}) {
                    if(type == Variable){
                            throw std::runtime_error("Trying to create a Composite expression of a function, "
                                                             "but the type provided is Variable.");
                    }
            }

            /** Copy constructor */
            Composite(Composite const & composite):
                    type(composite.type), id(composite.id), compound(composite.compound) {}

            /** Evaluates the Composite given the provided mapping of identifier to value assignment. */
            C eval(std::unordered_map<I, C> const &values) const;
        };

        /** @brief Returns a humanly presentable string representation of the Composite
         *
         * @param composite
         * @param print - print function for how to convert the identifier of type `I` to string
         * @return
         */
        template <typename I, typename C, typename P>
        std::string to_string(Composite<I, C, P> const & composite, id_print<I> print);

        /** @brief Returns a code equivalent string representation of the Composite
         *
         * @param composite
         * @param print - print function for how to convert the identifier of type `I` to string
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
