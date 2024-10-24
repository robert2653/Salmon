void dfsBfs() {
    int n;
    vector<vector<int>> adj(n);
    // dfs_graph
    vector<bool> vis(n);
    auto dfs = [&](auto self, int u) -> void {
        if (vis[u]) return;
        vis[u] = true;
        for (auto v: adj[u]) {
            self(self, v);
        }
    };
    dfs(dfs, 0);
    // bfs
    vector<int> dep(n, -1);
    auto bfs = [&](auto self, int s) -> void {
        queue<int> que;
        dep[s] = 0, que.push(s);
        while (!que.empty()) {
            int u = que.front(); que.pop();
            for (auto v : adj[u]) {
                if (dep[v] == -1) {
                    dep[v] = dep[u] + 1;
                    que.push(v);
                }
            }
        }
    };
    bfs(bfs, 0);
}