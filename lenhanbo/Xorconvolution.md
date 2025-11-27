We want to transform a[x] -> b[x] to perform pure multiple operation.

a[x] with contribute a[x] to b[y] if bitcount(x ^ y) % 2 == 0

a[x] with contribute -a[x] to b[y] if bitcount(x ^ y) % 2 == 1

So we can use dp sos to compute dp[mask][j] = number of y that bitcount(mask ^ y) == j with principle of inclusive and exclusive.

