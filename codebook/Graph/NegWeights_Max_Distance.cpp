#include <bits/stdc++.h>
#define int long long
using namespace std;
// CSES High Score
const int maxn = 2505;

void dfs(int u, vector<int> &vis, vector<vector<int>> &adj) {
	if (vis[u]) return;
	vis[u] = 1;
	for (int v : adj[u]) {
		dfs(v, vis, adj);
	}
}
void bellman_ford(int n, int s, vector<int> &vis, vector<int> &dis, vector<array<int, 3>> edge, vector<vector<int>> &adj) {
	fill(dis.begin(), dis.end(), -1e18);
	dis[s] = 0;
	for (int i = 1; i <= n; i++) {
		for (auto [u, v, w] : edge) {
			if (dis[u] != -1e18 && dis[v] < dis[u] + w) {
				dis[v] = dis[u] + w;
				if (i == n) {
					dfs(v, vis, adj);
				}
			}
		}
	}
}
signed main() {
    int n, m; cin >> n >> m;
    vector<array<int, 3>> edge;
    vector<vector<int>> adj(n + 1);
    vector<int> dis(n + 1), vis(n + 1);
	while (m--) {
		int u, v, w;
		cin >> u >> v >> w;
		edge.push_back({u, v, w});
		adj[u].push_back(v);
	}
	bellman_ford(n, 1, vis, dis, edge, adj);
	if (vis[n]) cout << -1;
	else cout << dis[n];
}