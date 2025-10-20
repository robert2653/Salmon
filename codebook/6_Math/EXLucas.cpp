ll legendre(ll n, int p) { // n! 中質數 p 的冪次
    ll res = 0;
    while (n) { n /= p, res += n; }
    return res;
}
Z C_pe(ll n, ll m, int p, int e) {
    int pe = power(p, e);
    Z::setMod(pe); // inv 要用 exgcd
    vector<Z> fac(pe); fac[0] = 1;
    for (int j = 1; j < pe; j++) {
        if (j % p == 0) fac[j] = fac[j - 1];
        else fac[j] = fac[j - 1] * j;
    }
    Z wilson = p == 2 && e >= 3 ? 1 : -1; // (p^e)! ≡ wilson (mod p^e)
    function<Z(ll)> fastFac = [&](ll n)
    { return n ? power(wilson, n / pe) * fac[n % pe] * fastFac(n / p) : 1; };
    ll vp = legendre(n, p) - legendre(m, p) - legendre(n - m, p);
    if (vp >= e) return 0;
    return power(Z(p), vp) * fastFac(n) / (fastFac(m) * fastFac(n - m));
}
ll exlucas(ll n, ll m, int mod) {
    vector<pair<int, int>> a;
    for (int i = 2; i * i <= mod; i++) {
        if (mod % i) continue;
        int e = 0, p = 1;
        while (mod % i == 0) mod /= i, e++, p *= i;
        a.emplace_back(C_pe(n, m, i, e).x, p);
    }
    if (mod != 1) a.emplace_back(C_pe(n, m, mod, 1).x, mod);
    return CRT(a);
}