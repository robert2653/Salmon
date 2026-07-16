vector<int> LIS(const vector<int> &a) { // strictly
	int n = a.size(), L = 1;
	vector<int> dp(n); dp[0] = 1;
	vector<int> v {a[0]};
	for (int i = 1; i < n; i++) {
		if (a[i] > v.back()) { // >=
			v.push_back(a[i]);
			dp[i] = ++L;
		} else { // upper
			auto it = lower_bound(v.begin(), v.end(), a[i]);
			*it = a[i];
			dp[i] = it - v.begin() + 1;
		}
	}
	vector<int> ans;
	for (int i = n - 1; i >= 0; i--)
		if (dp[i] == L) ans.push_back(a[i]), L--;
	reverse(ans.begin(), ans.end());
	return dp;
}