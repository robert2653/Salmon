auto add = [&](vector<int> &bas, int x) {
    for (auto i : bas) x = min(x, x ^ i);
    if (x) bas.push_back(x);
};
sort(bas.begin(), bas.end()); // 最簡化列梯
for (auto i = bas.begin(); i != bas.end(); i++) {
    for (auto j = next(i); j != bas.end(); j++) {
        *j = min(*j, *j ^ *i);
    }
}
// [l, r] 的區間 xor max (1-indexed)
vector<array<int, B>> bas(n + 1), lst(n + 1);
for (int i = 1; i <= n; i++) {
    int x = a[i - 1], p = i;
    bas[i] = bas[i - 1], lst[i] = lst[i - 1];
    for (int j = B - 1; j >= 0; j--)
        if (x >> j & 1) {
            if (!bas[i][j]) {
                bas[i][j] = x, lst[i][j] = p;
                break;
            }
            if (lst[i][j] < p)
                swap(lst[i][j], p), swap(x, bas[i][j]);
            x ^= bas[i][j];
        }
}
auto qry = [&](int l, int r) -> int {
    int mx = 0;
    for (int i = B - 1; i >= 0; i--)
        if (lst[r][i] >= l)
            mx = max(mx, mx ^ bas[r][i]);
    return mx;
};