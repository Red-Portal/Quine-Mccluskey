# Quine-Mccluskey Boolean Function Reducer
## Introduction
Quine-Mccluskey algorithm C++ implementation.

## How to use

```c++
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

* A B C  =  1  2  3
* A'B'C  = -1 -2 -3
* B C D' =  2  3 -4

## TODO

* msvc support 
  msvc currently has problems with auto return type deduction
* use boot::dynamic_bitset instead of user provided bit array
* further optimization 

