auto prim = [&](int n, vector<vector<pair<int, int>>> &adj) -> bool {
	int sz = 0; ll ans = 0;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.emplace(0, 0); // w, vertex
	vector<bool> vis(n);
	while (!pq.empty()) {
		auto [w, u] = pq.top(); pq.pop();
		if (vis[u]) continue;
		vis[u] = true;
		ans += w, sz++;
		for (auto [v, w] : g[u])
			if (!vis[v]) pq.emplace(w, v);
	}
	if (sz == n) return true;
	return false;
};
// Borůvka's algorithm
// 使用 DSU，每一輪中所有 component 嘗試使用最小邊去找到另一個 component 合併
// 時間複雜度: O(E log V \alpha(V)) 實際上會接近 O(E log V)