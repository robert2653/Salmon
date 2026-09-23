// 排程有權重問題(strict)，價值最多且時間最少
void projects(int n, vector<array<int, 4>> a) {
	// a[i] = {t, s, w, idx}
	sort(a.begin(), a.end());
	vector<ll> ts(n + 1); // ensure ts[0] is minimum
	for (int i = 1; i <= n; i++) ts[i] = a[i][0];
	vector<array<ll, 3>> dp(n + 1); // {-w, time, 上個是誰}
	for (int i = 1; i <= n; i++) {
		int id = --lower_bound(all(ts), a[i][1]) - ts.begin();
		dp[i] = {dp[i - 1][0], dp[i - 1][1], -1};
		ll nw = dp[id][0] - a[i][2];
		ll nt = dp[id][1] + a[i][0] - a[i][1];
		chmin(dp[i], {nw, nt, id});
	}
	vector<int> used;
	for (int i = n; i != 0;) {
		if (dp[i][2] != -1) {
			used.push_back(a[i][3]);
			i = dp[i][2];
		} else i--;
	} reverse(used.begin(), used.end());
}