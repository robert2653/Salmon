void minCut(int n, int m, Dinic<int> d) {
    int ans = d.work(0, n - 1);
    cout << ans << "\n";
    vector<int> vis(n);
    auto dfs = [&](auto self, int u) -> void {
        if (!vis[u]) {
            vis[u] = 1;
            for (int id : d.g[u]) {
                auto [to, f, cap] = d.e[id];
                if (cap - f > 0) {
                    self(self, to);
                }
            }
        }
    };
    dfs(dfs, 0);
    for (int i = 0; i < n; i++) {
        if (!vis[i]) continue;
        for (int id : d.g[i]) {
            if (id & 1) continue;
            auto e = d.e[id];
            if (!vis[e.to]) {
                cout << i + 1 << " " << e.to + 1 << "\n";
            }
        }
    }
}