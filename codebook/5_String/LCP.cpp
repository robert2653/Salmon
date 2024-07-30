void solve() {
    string s; cin >> s;
    SuffixArray sa(s);
    RMQ<int> rmq(sa.lc);
    auto lcp = [&](int i, int j) {
        i = sa.rk[i];
        j = sa.rk[j];
        if (i > j) {
            swap(i, j);
        }
        assert(i != j);
        return rmq(i, j);
    };
    int l, r; cin >> l >> r;
    cout << lcp(l, r) << "\n";
}