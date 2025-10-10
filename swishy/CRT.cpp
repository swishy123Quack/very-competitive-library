typedef __int128_t i128;
i128 exeuclid(i128 a, i128 b, i128& x, i128& y){
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    i128 x1, y1;
    i128 d = exeuclid(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

struct CBT{
    i128 A = 0, M = 0;
    void add(i128 a, i128 m){
        a = ((a % m) + m) % m;
        i128 _M = M;
        if (M == 0){
            A = a, M = m;
            return;
        }
        if (A == -1) return;
        i128 p, q;
        i128 g = exeuclid(M, m, p, q);
        if ((a - A) % g != 0){
            A = -1, M = -1;
            return;
        }
        i128 mul = (a - A) / g;
        M = m * M / g;
        A = (((_M * p * mul + A) % M) + M) % M;
    }
};