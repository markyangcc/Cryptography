# Playfair cipher in C++

C++ implementation of playfair encryption



## Include files
`main.cpp` : drive program

`playfair.h` : Header file for encapsulating le playfair cipher

`maketable.h` : Build playfair 5*5 table

`msgtreat.h` : Preprocessing the user input key

`encrytext.h` : Substitution encryption of user input text

`dependfunc.h` : dependence functions like remove spaces and duplicates in key(string)

## How to run?
```bash
g++ main.cpp -o main && ./main
```

## What I say

This simple playfair cipher written in C++ was implemented by myself from zero.

It takes me a bit long time to handle the bugs and try to make the program more strong.

This is a small project, but it make me have a better grasp of C++ syntax d learn more about the STL Library.

### Environment
```bash
OS  : Ubuntu 20.10 64-bit
Compiler : g++ (version 10.2.0)
C++ standard ：C11
```
### Bright spots

* Encapsulation

emove duplicates and spaces in key

* Add special characters 'x' and 'q' to make program more strong when use enter text like "helloworldxxxxx"


