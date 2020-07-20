STL Vector
==========
Problem statement
-----------------
The elements of STL vector I plan to implement in round 1.

* Constant-time element access

* Amortized time growth with `vector.push_back()`

* Compatibility with STL algorithms through implementation of
  iterators.

* `push_back(val)`, `operator[]`, `size()`, `resize(sz)`, 
  `allocate(sz), the most useful constructors.

Timing
------
* Round 1 above took approximately 1 hour and 35 minutes.

TODO
----
Remaining to be implemented.

* The iterator on STL vector should be bidirectional.

* Probably due to the above, the vector is not working with algorithms from
  `<algorithms>`. We should fix this.
