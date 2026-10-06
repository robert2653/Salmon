void hamiltonianPath() {
	int n, m; cin >> n >> m;
	vector<vector<int>> adj(n);
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v;
		adj[--v].push_back(--u);
	}
	// 以...為終點，走過...
	vector dp(n, vector<int>(1 << n));
	dp[0][1] = 1;
	for (int mask = 1; mask < 1 << n; mask++) {
		if ((mask & 1) == 0) continue;
		for (int i = 0; i < n; i++) {
			if ((mask >> i & 1) == 0) continue;
			if (i == n - 1 && mask != (1 << n) - 1) continue;
			int pre = mask ^ (1 << i);
			for (int j : adj[i]) {
				if ((pre >> j & 1) == 0) continue;
				dp[i][mask] = (dp[i][mask] + dp[j][pre]) % Mod;
			}
		}
	}
	cout << dp[n - 1][(1 << n) - 1] << "\n";
}
void minClique() { // 移掉一些邊, 讓整張圖由最少團組成
	int n, m;
	cin >> n >> m;
	vector<int> g(n);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--, v--;
		g[u] |= 1 << v, g[v] |= 1 << u;
	}
	vector<int> w(1 << n, 1E9), dp(1 << n, 1E9);
	w[0] = 1, dp[0] = 0;
	for (int mask = 0; mask < 1 << n; mask++) // 先正常 dp
		for (int i = 0; i < n; i++) {
			int pre = mask ^ (1 << i);
			if (w[pre] == 1 && (g[i] & pre) == pre)
				w[mask] = 1; // i 有連到所有 pre
		}
	for (int mask = 0; mask < 1 << n; mask++) // 然後枚舉子集 dp
		for (int sub = mask; sub; --sub &= mask)
			dp[mask] = min(dp[mask], dp[mask ^ sub] + w[sub]);
	cout << dp[(1 << n) - 1] << "\n";
}