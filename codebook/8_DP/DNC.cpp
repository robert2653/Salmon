// 應用: 切 k 段問題, 且滿足四邊形不等式
// w(a,c) + w(b,d) <= w(a,d) + w(b,c)
// dp[k][j] = min(dp[k - 1][i] + cost[i][j])
// O(K N logN)
auto getCost = [&](int l, int r) {}; // (l, r], 1-based
vector<ll> dp(n + 1, inf); dp[0] = 0;
for (int j = 0; j < k; j++) {
	vector<ll> ndp(n + 1, inf);
	[&](this auto &&self, int l, int r, int optl, int optr) {
		if (l > r) return;
		int m = (l + r) / 2, opt = 0;
		ndp[m] = inf;
		for (int i = optl; i <= min(m - 1, optr); i++) {
			ll x = dp[i] + getCost(i, m);
			if (x < ndp[m]) ndp[m] = x, opt = i;
		}
		self(l, m - 1, optl, opt);
		self(m + 1, r, opt, optr);
	} (1, n, j, n - 1);
	dp = ndp;
}