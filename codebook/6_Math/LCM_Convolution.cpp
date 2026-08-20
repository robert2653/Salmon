vector<Z> zeta(vector<Z> a) { // ak = sum_{d|k} a[d]
    int n = a.size() - 1;
    for (int p : primes)
        for (int i = 1; i <= n / p; i++) a[i * p] += a[i];
    return a;
}
vector<Z> fmt(vector<Z> a) { // ck = sum_{d|k} mu[d] * a[k/d]
    int n = a.size() - 1;
    for (int p : primes)
        for (int i = n / p; i >= 1; i--) a[i * p] -= a[i];
    return a;
}
vector<Z> conv(vector<Z> a, vector<Z> b) { // ck = sum_{lcm(i,j)=k} a[i] * b[j]
    int n = a.size() - 1;
    a = zeta(a), b = zeta(b);
    vector<Z> c(n + 1);
    for (int i = 1; i <= n; i++) c[i] = a[i] * b[i];
    return fmt(c);
}