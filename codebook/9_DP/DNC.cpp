// 應用: 切 k 段問題, 且滿足四邊形不等式
// w(a,c) + w(b,d) ≤ w(a,d) + w(b,c)
// dp[k][j] = min(dp[k - 1][i] + cost[i][j])
// O(K N logN)
ll dp[K + 1][N + 1];
ll getCost(int l, int r) {} // (l, r], 1-based
void rec(int k, int l, int r, int optl, int optr) {
    if (l > r) return;
    int m = (l + r) / 2, opt = 0;
    dp[k][m] = inf;
    for (int i = max(k - 1, optl); i <= min(m - 1, optr); i++) {
        ll x = dp[k - 1][i] + getCost(i, m);
        if (x < dp[k][m]) dp[k][m] = x, opt = i;
    }
    rec(k, l, m - 1, optl, opt);
    rec(k, m + 1, r, opt, optr);
}
void DNC() { // first build cost...
    for (int i = 1; i <= n; i++) dp[1][i] = getCost(0, i);
    for (int i = 2; i <= k; i++) rec(i, 1, n, 1, n);
    cout << dp[k][n] << "\n";
}