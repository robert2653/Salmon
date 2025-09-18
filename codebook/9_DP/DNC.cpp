// 應用: 切 k 段問題, 且滿足四邊形不等式
// w(a,c) + w(b,d) ≤(≥) w(a,d) + w(b,c)
// dp[k][j] = min(dp[k - 1][i] + cost[i][j])
// cost: (i, j]
constexpr int N = 3E3 + 5;
constexpr ll inf = 4E18;
ll dp[N][N]; // 1-based
ll getCost(int l, int r) {}
void rec(int k, int l, int r, int optl, int optr) {
    if (l > r) return;
    int m = (l + r) >> 1, opt = -1;
    dp[k][m] = inf;
    for (int i = max(k, optl); i <= min(m, optr); i++) {
        // 注意 i 的範圍、 get_cost 與 dp 的邊界
        ll cur = dp[k - 1][i] + getCost(i, m);
        if (cur < dp[k][m]) dp[k][m] = cur, opt = i;
    }
    rec(k, l, m - 1, optl, opt);
    rec(k, m + 1, r, opt, optr);
}
void DNC() {
    // first build cost...
    for (int i = 1; i <= n; i++) dp[1][i] = getCost(1, i);
    for (int i = 2; i <= k; i++) rec(i, 1, n, 1, n);
    cout << dp[k][n] << "\n";
}