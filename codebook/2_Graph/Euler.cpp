vector<int> ans;
[&](this auto &&self, int u) -> void {
	while (g[u].size()) {
		int v = *g[u].begin();
		g[u].erase(v);
		self(v);
	}
	ans.push_back(u);
} (0); reverse(ans.begin(), ans.end());