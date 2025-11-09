// a^x = b (mod m)
// x = A * sq - B (0 <= A, B <= sq)
vector<int> BSGS(int a, int b, int m) { // gcd(a, m) = 1
    Z::setMod(m);
    unordered_map<int, int> mp;
    ll sq = 1; while (sq * sq < m) sq++;
    Z rhs = b; vector<int> res;
    for (int B = 0; B <= sq; B++) {
        mp[rhs.x] = B;
        rhs *= a;
    }
    Z a_pow_sq = power(Z(a), sq), lhs = a_pow_sq;
    for (int A = 1; A <= sq; A++, lhs *= a_pow_sq)
        if (mp.find(lhs.x) != mp.end()) {
            int B = mp[lhs.x];
            res.push_back(A * sq - B);
        }
    return res;
}
int exBSGS(int a, int b, int m) {
    if (b == 1 || m == 1) return 0;
    if (!a) return b ? -1 : 1;
    int k = 0;
    ll tmp = 1;
    while (__gcd(a, m) != 1) {
        int d = __gcd(a, m);
        if (b % d != 0) return -1;
        b /= d, m /= d, k++;
        tmp = tmp * (a / d) % m;
        if (tmp == b) return k;
    }
    Z::setMod(m);
    Z b_ = Z(b) * Z(tmp).inv();
    auto xs = BSGS(a, b_.x, m);
    return xs.empty() ? -1 : *min_element(xs.begin(), xs.end()) + k;
}