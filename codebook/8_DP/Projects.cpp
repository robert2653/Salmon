void projects() { // 排程有權重問題，輸出價值最多且時間最少
	int n; cin >> n;
	vector<array<int, 4>> a(n + 1);
	for (int i = 1; i <= n; i++) {
		int u, v, w; cin >> u >> v >> w;
		a[i] = {v, u, w, i};
	}
	sort(a.begin(), a.end());
	vector<ll> vs(n + 1);
	for (int i = 1; i <= n; i++) vs[i] = a[i][0];
	vector<array<ll, 3>> dp(n + 1); // {w, time, 上個是誰}
	for (int i = 1; i <= n; i++) {
		int id = --lower_bound(all(vs), a[i][1]) - vs.begin();
		dp[i] = {dp[i - 1][0], dp[i - 1][1], -1};
		ll nw = dp[id][0] + a[i][2];
		ll nt = dp[id][1] + a[i][0] - a[i][1];
		if (dp[i][0] < nw || dp[i][0] == nw && dp[i][1] > nt) {
			dp[i] = {nw, nt, id};
		}
	}
	vector<int> ans;
	for (int i = n; i != 0;) {
		if (dp[i][2] != -1) {
			ans.push_back(a[i][3]);
			i = dp[i][2];
		} else i--;
	} reverse(ans.begin(), ans.end());
}