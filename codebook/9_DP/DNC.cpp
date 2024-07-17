constexpr int N = 3e3 + 5;
constexpr ll inf = 4e18;
// dp[k][j] = min(dp[k - 1][i - 1] + cost[i][j]);
ll cost[N][N], dp[N][N]; // 1-based
ll get_cost(int l, int r) {}
void DNC(int k, int l, int r, int optl, int optr) {
    if (l > r) return;
    int m = (l + r) >> 1, opt = -1;
    dp[k][m] = inf;
    for (int i = max(k, optl); i <= min(m, optr); i++) {
        ll cur = dp[k - 1][i - 1] + get_cost(i, m);
        if (cur < dp[k][m]) {
            dp[k][m] = cur, opt = i;
        }
    }
    DNC(k, l, m - 1, optl, opt);
    DNC(k, m + 1, r, opt, optr);
}
int main() {
    // first build cost...
    for (int i = 1; i <= n; i++) {
        dp[1][i] = get_cost(1, i);
    }
    for (int i = 2; i <= k; i++) {
        DNC(i, 1, n, 1, n);
    }
    cout << dp[k][n] << "\n";
}