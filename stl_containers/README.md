C++ STL Practice and Review
============
Introduction
-----------
The C++ STL is an important part of C++, and not only is it important to understand
what different elements of it do, it's important to demonstrate this to companies
that might be looking to hire you.

This directory contains implementations of some STL containers in C++. The
general rule is that no std namespace functions can be used in these implementations
(aside from things like std::iterator, which defines an interface). 

* Before doing each implementation, I brushed up on some fundamentals such as
  what data structures and algorithms backed each STL container. For example,
  I wondered what hash function tended to be used for each type in the STL, so
  I looked it up beforehand.

* After adding a rough plan for implementation of each container, the commits
  following that are in real-time, so the Git history reflects the time it took
  me.

* During the implementation period, I only refer to standard library documentation on
  https://en.cppreference.com/w/. I don't read any implementations, or any references 
  elsewhere. And of course, no copying & pasting code from any other sources.

* In some cases, I might refrain from using the exact implementation or standard, because
  it would be out of scope for the goal here. An example would be using a simple
  algorithm to rebalance BSTs instead of an ideal one like a Red Black Tree (as is
  used in std::list's implementations in the major compilers).

Instructions
------------
Run this to test this library.

```
git clone https://github.com/indianajohn/practice
cd practice/stl_containers
mkdir build
cd build
cmake ..
make -j16 && make test
```
