int findPrimitiveRoot(ll m) {
    Mlong<0>::setMod(m); // Mlong if needed
    ll phi = m; // m - 1 if m prime
    res.clear();
    pollardRho(m);
    for (auto [p, _] : res) phi = phi / p * (p - 1);
    vector<ll> pr; // prime factors of phi
    res.clear();
    pollardRho(phi);
    for (auto &[p, _] : res) pr.push_back(p);
    for (int i = 1; i <= m; i++) {
        bool ok = true;
        for (int j = 0; j < int(pr.size()) && ok; j++)
            ok &= power(Mlong<0>(i), phi / pr[j]).x != 1;
        if (ok) return i;
    }
    return -1; // m != 1, 2, 4, p^k, 2(p^k)
}