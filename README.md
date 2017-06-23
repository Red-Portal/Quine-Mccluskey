# Quine-Mccluskey Boolean Function Reducer

## Current version is under refactoring. IT DOESN'T WORK

## Introduction
Quine-Mccluskey algorithm C++ implementation.

## How to use

```c++
#include "QM.hpp"

auto reducer = QM::Reducer<uT>{inputSize, minTerms, dontCareTerms};
auto result = reducer.getBooleanfunction();
```

QM::Reducer offers initialization by std::vector, std::initializer_list
the result is type is std::vector<std::vector<int>>.
uT is an unsigned integer type,
Because this implementation uses bit masking/shifting.

* Each term in the boolean function are std::vector<int>.
* Each variable in a boolean term is represented as an integer.
* The integer is the input number.
* Negative integer values are negative inputs.

```
 A B C  is represented as  1  2  3
 A'B'C  is represented as -1 -2 -3
 B C D' is represented as  2  3 -4
```

## Dependency

* boost libraries

This library currently uses boost::dynamic_bitset.
No boost static library dependencies.
Thus only boost headers are required.
Because of boost cross-dependency, I recommend providing all of boost.


## TODO

* further optimization 

