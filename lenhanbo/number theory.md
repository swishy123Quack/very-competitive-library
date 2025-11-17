1. When work with both or and and: if there exist a subset of which sum (|, &) is X, exists a subset with size <= log2(A_i). So when work with these type of problems, we just need to maintain a small number of candidates.
2. There are no data structures for OR and AND problems, when encountered, just look for essensial observations.
3. And, or, gcd as f : F(i) = j that f[j..i] <= X, F(i) <= F(i+1) so we can do some magical things like binary search on this function.
4. Mex : In a permutation, mex(l,r) = min(mex(1,r), mex(l,n))
5. X = $\sum_{D} \phi(D)$ for all Divisor D of X. In some cases we can use this property to calculate gcd(a,b).
6. $A[i] = -A[i]$ mod M so we can abuse this property which such problems related  to (a[i] + b[i])%M
