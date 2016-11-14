# Symbolic Integers - Static Registry Non Templated [SRNT]
A small library for manipulation and calculation of symbolic 
integer polynomials.

## Branches
The repository contains four branches all of which implement the same
functionality, but in slightly different way. Half of them are fully 
templated, thus they are header only, while the other two use 
preprocessor macros to define variable types. 

There are three main numeric types for the polynomials:

   1. *C* - the type of the coefficients in the polynomial
   2. *I* - the type of the ids for each symbolic variable. 
   3. *P* - the type of the powers used for monomials

The second division is made by whether there is a static global 
**Registry** or all functionality is implemented via provided dynamic one.

## Install
If you intend to use one of the templated branches you need only to copy
all of the header files. For the other two branches you will need to 
build to include the header files and link with the corresponding library.

If you want to run the tests or compile the example you will need to 
build the project. Don't forget to initialize the googletest submodule 
via `git submodule update --init --recursive`. 
 
## Example usage [SRNT]

Below is the code for a simple example which can also
be found in the `examples` directory for the Static Registry Non Templated branch.

```c++
#include "symbolic_integers.h"
#include "iostream"

typedef md::sym::Polynomial SymInt;
typedef std::vector<std::pair<md::sym::I, md::sym::C>> VecValues;
typedef std::vector<std::pair<SymInt, md::sym::C>> ImplicitValues;

int main(){
    // Make a reg
    auto reg = md::sym::registry();

    // Get just the individual symbolic variables
    auto a = reg->new_variable();
    auto b = reg->new_variable();
    auto c = reg->new_variable();

    // Build polynomials
    auto poly1 = a * a - a * b + 12;
    auto poly2 = (b + c) * (a + 1);
    auto poly3 = a * b;
    auto poly4 = (a + b + 1) * (c*2 + 3);
    auto poly5 = floor(b * b, a * a);
    auto poly6 = ceil(b * b, a * a);
    auto poly7 = min(a * b + 12, a * b + a);
    auto poly8 = max(a * b + 12, a * b + a);

    // Evaluate using a vector
    std::vector<md::sym::C> vals0 {1, 7, 4};
    std::cout << "Evaluating for " << a << " = " << a.eval(vals0)
              << ", " << b << " = " << b.eval(vals0)
              << ", " << c << " = " << c.eval(vals0) << std::endl;
    std::cout << poly1 << " = " << poly1.eval(vals0) << " [Expected " << 6 << "]" << std::endl
              << poly2 << " = " << poly2.eval(vals0) << " [Expected " << 22 << "]" << std::endl
              << poly3 << " = " << poly3.eval(vals0) << " [Expected " << 7 << "]" << std::endl
              << poly4 << " = " << poly4.eval(vals0) << " [Expected " << 99 << "]" << std::endl
              << poly5 << " = " << poly5.eval(vals0) << " [Expected " << 49 << "]" << std::endl
              << poly6 << " = " << poly6.eval(vals0) << " [Expected " << 49 << "]" << std::endl
              << poly7 << " = " << poly7.eval(vals0) << " [Expected " << 8 << "]" << std::endl
              << poly8 << " = " << poly8.eval(vals0) << " [Expected " << 19 << "]" << std::endl
              << "==================================================" << std::endl;

    // Evaluating using a vector of pairs
    VecValues vals1 {{0, 3}, {1, 2}, {2, 5}};
    std::cout << "Evaluating for " << a << " = " << a.eval(vals1)
              << ", " << b << " = " << b.eval(vals1)
              << ", " << c << " = " << c.eval(vals1) << std::endl;
    std::cout << poly1 << " = " << poly1.eval(vals1) << " [Expected " << 15 << "]" << std::endl
              << poly2 << " = " << poly2.eval(vals1) << " [Expected " << 28 << "]" << std::endl
              << poly3 << " = " << poly3.eval(vals1) << " [Expected " << 6 << "]" << std::endl
              << poly4 << " = " << poly4.eval(vals1) << " [Expected " << 78 << "]" << std::endl
              << poly5 << " = " << poly5.eval(vals1) << " [Expected " << 0 << "]" << std::endl
              << poly6 << " = " << poly6.eval(vals1) << " [Expected " << 1 << "]" << std::endl
              << poly7 << " = " << poly7.eval(vals1) << " [Expected " << 9 << "]" << std::endl
              << poly8 << " = " << poly8.eval(vals1) << " [Expected " << 18 << "]" << std::endl
              << "==================================================" << std::endl;

    // Deducing variable values from polynomials
    auto a_val = 5;
    auto b_val = 3;
    auto c_val = 8;
    ImplicitValues implicit_values{{5*b + 2, 17}, {poly3, 15}, {poly2, 66}};
    VecValues deduced_values = reg->deduce_values(implicit_values);
    std::cout << "Deduced values: " << std::endl
              << "a = " << a.eval(deduced_values) << " [Expected: " << a_val << "]" <<  std::endl
              << "b = " << b.eval(deduced_values) << " [Expected: " << b_val << "]" <<  std::endl
              << "c = " << c.eval(deduced_values) << " [Expected: " << c_val << "]" <<  std::endl;
    return 0;
}
```

Output of the program:
```c++
Evaluating for a = 1, b = 7, c = 4
a^2-ab+12 = 6 [Expected 6]
ab+ac+b+c = 22 [Expected 22]
ab = 7 [Expected 7]
2ac+3a+2bc+3b+2c+3 = 99 [Expected 99]
floor(b^2 / a^2) = 49 [Expected 49]
ceil(b^2 / a^2) = 49 [Expected 49]
min(ab+12 / ab+a) = 8 [Expected 8]
max(ab+12 / ab+a) = 19 [Expected 19]
==================================================
Evaluating for a = 3, b = 2, c = 5
a^2-ab+12 = 15 [Expected 15]
ab+ac+b+c = 28 [Expected 28]
ab = 6 [Expected 6]
2ac+3a+2bc+3b+2c+3 = 78 [Expected 78]
floor(b^2 / a^2) = 0 [Expected 0]
ceil(b^2 / a^2) = 1 [Expected 1]
min(ab+12 / ab+a) = 9 [Expected 9]
max(ab+12 / ab+a) = 18 [Expected 18]
==================================================
Deduced values: 
a = 5 [Expected: 5]
b = 3 [Expected: 3]
c = 8 [Expected: 8]
```

You can check out the tests in the `tests` folder for more examples.

## Limitations

Currently, the variable's values deduction algorithm is pretty weak. 
The main reason is that for the purposes that I'm using it this is enough. 
Otherwise a more complicated and functional algorithm would probably use
something like [Grobner basis](https://en.wikipedia.org/wiki/Gr%C3%B6bner_basis).

## License
The project is distrusted under the MIT License.

## Contributing
If you want to contribute in any way please make an Issue or submit a PR
request describing its functionality.
