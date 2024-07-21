struct VBCC {
    int n, cur;
    vector<vector<int>> adj;
    vector<int> dfn, low, parent;
    vector<bool> is_cut;
    VBCC(int n_ = 0) { init(n_); }
    void init(int n_) {
        n = n_;
        adj.assign(n, {});
        dfn.assign(n, -1);
        low.resize(n);
        parent.assign(n, -1);
        is_cut.assign(n, false);
        cur = 0;
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void dfs(int x) {
        int children = 0;
        dfn[x] = low[x] = cur++;
        for (int v : adj[x]) {
            if (dfn[v] == -1) {
                children++;
                parent[v] = x;
                dfs(v);
                low[x] = min(low[x], low[v]);
                
                if (parent[x] != -1 && low[v] >= dfn[x]) {
                    is_cut[x] = true;
                }
            } else if (v != parent[x]) {
                low[x] = min(low[x], dfn[v]);
            }
        }
        if (parent[x] == -1 && children > 1) {
            is_cut[x] = true;
        }
    }
    void work() {
        for (int i = 0; i < n; i++) {
            if (dfn[i] == -1) {
                dfs(i);
            }
        }
    }
};