struct Hangarian { // 0-based
    int n, m; // 最小路徑覆蓋，二分匹配
    vector<vector<int>> adj;
    vector<int> used, vis;
    vector<pair<int, int>> match;
    Hangarian(int n_ = 0, int m_ = 0) {
        init(n_, m_);
    }
    void init(int n_ = 0, int m_ = 0) {
        n = n_; m = m_;
        adj.assign(n + m, vector<int>());
        used.assign(n + m, -1);
        vis.assign(n + m, 0);
    }
    void addEdge(int u, int v) {
        adj[u].push_back(n + v);
        adj[n + v].push_back(u);
    }
    vector<pair<int, int>> work() {
        match.clear();
        used.assign(n + m, -1);
        vis.assign(n + m, 0);
        auto dfs = [&](auto self, int u) -> bool {
            for (int v : adj[u]) {
                if (vis[v] == 0) {
                    vis[v] = 1;
                    if (used[v] == -1 || self(self, used[v])) {
                        used[v] = u;
                        return true;
                    }
                }
            }
            return false;
        };
        for (int i = 0; i < n; i++) {
            fill(vis.begin(), vis.end(), 0);
            dfs(dfs, i);
        }
        for (int i = n; i < n + m; i++) {
            if (used[i] != -1) {
                match.emplace_back(used[i], i - n);
            }
        }
        return match;
    }
};