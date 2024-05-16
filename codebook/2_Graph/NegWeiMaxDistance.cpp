// CSES High Score
void dfs(int u, vector<int> &vis, vector<vector<int>> &adj) {
	if (vis[u]) return;
	vis[u] = 1;
	for (int v : adj[u]) {
		dfs(v, vis, adj);
	}
}
signed main() {
    int n, m; cin >> n >> m;
    vector<array<int, 3>> edges;
    vector<vector<int>> adj(n + 1);
    vector<int> dis(n + 1), vis(n + 1);
	while (m--) {
		int u, v, w;
		cin >> u >> v >> w;
		edges.push_back({u, v, w});
		adj[u].push_back(v);
	}
	fill(dis.begin(), dis.end(), -1e18);
	dis[1] = 0;
	for (int i = 1; i <= n; i++) {
		for (auto [u, v, w] : edges) {
			if (dis[u] != -1e18 && dis[v] < dis[u] + w) {
				dis[v] = dis[u] + w;
				if (i == n) {
					dfs(v, vis, adj);
				}
			}
		}
	}
	if (vis[n]) cout << -1;
	else cout << dis[n];
}