int main() {
    int n;
    vector<vector<int>> adj(n + 1, vector<int>());
    // dfs_graph
    vector<bool> vis(n + 1, 0);
    auto dfs = [&](auto self, int u) -> void {
        if (vis[u]) return;
        vis[u] = true;
        for (auto v: adj[u]) {
            self(self, v);
        }
    };
    dfs(dfs, 1);
    // bfs
    vector<int> depth(n + 1, 1e9);
    queue<int> q;
    auto bfs = [&](auto self, int u) -> void {
        vis[u] = true;
        depth[u] = 0;
        q.push(u);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto v : adj[u]) {
                if (vis[v]) continue;
                vis[v] = true;
                depth[v] = depth[u] + 1;
                q.push(v);
            }
        }
    };
    bfs(bfs, 1);
}