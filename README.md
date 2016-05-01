# Programs for finding polydivisible numbers

A number in base b with (b-1) digits d_0 .. d_(b-2) is polydivisible
if and only if each left subset of digits is divisible the size of the subset i.e.

d_0 % 1 == 0 (trivially true)
( d_0 * b + d_1 ) % 2 == 0
( d_0 * b^2 + d_1 * b + d_2 ) % 3 == 0
...
( d_0 * b^(b-3) + ... + d_(b-2) % (b-2) ) % (b-2) == 0

## poly - Test an individual number for polydivisibility
```
./poly b d_0 d_1 d_2 d_3 ...
```
i.e. the base followed by the digits in that base.

## polyb - Check a given base to find any polydivisible numbers that exist.
```
./poly b alg
```
i.e. the base followed by an integer to select the algorithm:

* 1 : Generate all permutations via Heap's algorithm (iterative version) and test each individually

* 2 : Recursive version of algorithm 1

* 3 : Attempt at 2 with backtracking.  Not currently working

* 4 : Generate permutations recursively left-to-right.  At each depth of the tree, test the subset for partial poly-divisibility.  If the test fails, backtrack to another branch of the tree.

Algorithms 1 & 2 are slow.  Can realistically test up to b=16 in a few hours.

Algorithm 4 is faster.  Currently testing up to b=40.
