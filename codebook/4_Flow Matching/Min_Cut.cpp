void policeChase(int n, Dinic<int> &d) {
	int ans = d.work(0, n - 1);
	vector<int> vis(n);
	[&](this auto &&self, int u) -> void {
		if (vis[u]) return;
		vis[u] = 1;
		for (int id : d.g[u]) {
			auto [to, f, cap] = d.e[id];
			if (cap - f > 0) self(to);
		}
	} (0);
	for (int i = 0; i < n; i++) {
		if (!vis[i]) continue;
		for (int id : d.g[i]) {
			if (id & 1) continue;
			auto e = d.e[id];
			if (!vis[e.to]) cout << i + 1 << " " << e.to + 1 << "\n";
		}
	}
}