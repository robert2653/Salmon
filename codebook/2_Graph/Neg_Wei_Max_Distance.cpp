// CSES High Score
void dfs(int u, vector<int> &vis, vector<vector<int>> &adj) {
	if (vis[u]) return;
	vis[u] = 1;
	for (int v : adj[u]) {
		dfs(v, vis, adj);
	}
}
void negWeiMaxDistance() {
    int n, m; cin >> n >> m;
    vector<array<int, 3>> edges;
    vector<vector<int>> adj(n);
    vector<int> dis(n), vis(n);
	while (m--) {
		int u, v, w;
		cin >> u >> v >> w;
		edges.emplace_back(u, v, w);
		adj[u].push_back(v);
	}
	fill(dis.begin(), dis.end(), -1e18);
	dis[0] = 0;
	for (int i = 0; i < n; i++) {
		for (auto [u, v, w] : edges) {
			if (dis[u] != -1e18 && dis[v] < dis[u] + w) {
				dis[v] = dis[u] + w;
				if (i == n) {
					dfs(v, vis, adj);
				}
			}
		}
	}
	if (vis[n - 1]) cout << -1;
	else cout << dis[n - 1];
}