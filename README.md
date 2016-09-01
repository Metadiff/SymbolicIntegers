# Symbolic Integers

A small header only library for manipulation and calculation 
of symbolic integer polynomials.

## Install

All you need to do is copy all of the header files. No other installation needed.

If you want to run the tests or compile the example you will need to 
build the project. Don't forget to initialize the googletest submodule 
via `git submodule update --init --recursive`. 
 
## Branches

The repository contains four branches, which implement the same thing 
with small variations. Below are outlined these differences
  
  1. **master** - All classes are templated. `C` is the type of the 
  coefficient, `I` is the type of the variable id's and 
  `P` is the type of the powers. The registry for symbolic 
   variables is static attached to the corresponding class.
   
  2. **registry** - Same as **master**, however there is a `Registry` class
  which keeps information for all created variables. This allows to have
  different registries at the same time.
  
  3. **no_template** - Same as **master**, however the classes are not templated.
  You can define the preprocessor variables `C_WIDTH`, `I_WIDTH` and `P_WIDTH`
  which specify how many bits (8, 16, 32 or 64) they will take. The 
  default values are `C_WIDTH=32`, `I_WIDTH=16`, `P_WIDTH=8`.
  
  4. **no_template_registry** - **2.** and **3.** combined.
  

## Example usage

Below is the code for a simple example which can also
be found in the `examples` directory.

```c++
#include "symbolic_integers.h"
#include "iostream"

typedef md::sym::Registry Registry;
typedef md::sym::Polynomial SymInt;
typedef std::vector<std::pair<I, C>> VecValues;
typedef std::vector<std::pair<SymInt, C>> ImplicitValues;

int main(){
    // Make a registry
    auto registry = std::make_shared<Registry>();
    registry->init();

    // Get just the individual symbolic variables
    auto a = registry->new_variable();
    auto b = registry->new_variable();
    auto c = registry->new_variable();

    // Build polynomials
    auto poly1 = a * a - a * b + 12;
    auto poly2 = (b + c) * (a + 1);
    auto poly3 = a * b;
    auto poly4 = (a + b + 1) * (c*2 + 3);

    // Evaluate using a vector
    std::vector<int> vals0 {1, 7, 4};
    std::cout << "Evaluating for " << a << " = " << a.eval(vals0)
              << ", " << b << " = " << b.eval(vals0)
              << ", " << c << " = " << c.eval(vals0) << std::endl;
    std::cout << poly1 << " = " << poly1.eval(vals0) << " [Expected " << 6 << "]" << std::endl
              << poly2 << " = " << poly2.eval(vals0) << " [Expected " << 22 << "]" << std::endl
              << poly3 << " = " << poly3.eval(vals0) << " [Expected " << 7 << "]" << std::endl
              << poly4 << " = " << poly4.eval(vals0) << " [Expected " << 99 << "]" << std::endl
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
              << "==================================================" << std::endl;

    // Deducing variable values from polynomials
    auto a_val = 5;
    auto b_val = 3;
    auto c_val = 8;
    ImplicitValues implicit_values{{5*b + 2, 17}, {poly3, 15}, {poly2, 66}};
    VecValues deduced_values = registry->deduce_values(implicit_values);
    std::cout << "Deduced values: " << std::endl
              << "a = " << a.eval(deduced_values) << " [Expected: " << a_val << "]" <<  std::endl
              << "b = " << b.eval(deduced_values) << " [Expected: " << b_val << "]" <<  std::endl
              << "c = " << c.eval(deduced_values) << " [Expected: " << c_val << "]" <<  std::endl;
    return 0;
}
```

Output of the program:
```c++
Evaluating for a¹ = 1, b¹ = 7, c¹ = 4
a²-a¹b¹+12 = 6 [Expected 6]
a¹b¹+a¹c¹+b¹+c¹ = 22 [Expected 22]
a¹b¹ = 7 [Expected 7]
2a¹c¹+3a¹+2b¹c¹+3b¹+2c¹+3 = 99 [Expected 99]
==================================================
Evaluating for a¹ = 3, b¹ = 2, c¹ = 5
a²-a¹b¹+12 = 15 [Expected 15]
a¹b¹+a¹c¹+b¹+c¹ = 28 [Expected 28]
a¹b¹ = 6 [Expected 6]
2a¹c¹+3a¹+2b¹c¹+3b¹+2c¹+3 = 78 [Expected 78]
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
