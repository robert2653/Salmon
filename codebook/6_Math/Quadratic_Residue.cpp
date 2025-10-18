int jacobi(int x, int p) {
    int s = 1;
    for (; p > 1; ) {
        x %= p;
        if (x == 0) return 0;
        const int r = __builtin_ctz(x);
        if ((r & 1) && ((p + 2) & 4)) s = -s;
        x >>= r;
        if (x & p & 2) s = -s;
        swap(x, p);
    }
    return s;
}
template<class Z>
int quadraticResidue(Z x) {
    int p = Z::getMod();
    if (p == 2) return x.x & 1;
    const int jc = jacobi(x.x, p);
    if (jc == 0) return 0;
    if (jc == -1) return -1;
    Z b, d;
    while (true) {
        b = rand(), d = b * b - x;
        if (jacobi(d.x, p) == -1) break;
    }
    Z f0 = b, f1 = 1, g0 = 1, g1 = 0, tmp;
    for (int e = (p + 1) >> 1; e; e >>= 1) {
        if (e & 1) {
            tmp = g0 * f0 + d * (g1 * f1);
            g1 = g0 * f1 + g1 * f0, g0 = tmp;
        }
        tmp = f0 * f0 + d * (f1 * f1);
        f1 = f0 * f1 * 2, f0 = tmp;
    }
    return min(g0.x, p - g0.x);
}