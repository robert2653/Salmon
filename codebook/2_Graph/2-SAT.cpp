struct TwoSat {
    int n; vector<vector<int>> g;
    vector<bool> ans;
    TwoSat(int n) : n(n), g(2 * n), ans(n) {}
    void addClause(int u, bool a, int v, bool b) {
        g[2 * u + !a].push_back(2 * v + b);
        g[2 * v + !b].push_back(2 * u + a);
    }
    void ifThen(int u, bool a, int v, bool b) {
        // 必取 A: not A -> A
        g[2 * u + a].push_back(2 * v + b);
    }
    bool satisfiable() {
        vector<int> id(2 * n, -1), dfn(2 * n, -1), low(2 * n, -1);
        vector<int> stk;
        int now = 0, cnt = 0;
        auto dfs = [&](auto &&self, int u) -> void {
            stk.push_back(u);
            dfn[u] = low[u] = now++;
            for (auto v : g[u]) {
                if (dfn[v] == -1) {
                    self(self, v);
                    low[u] = min(low[u], low[v]);
                } else if (id[v] == -1) { // in stk
                    low[u] = min(low[u], dfn[v]);
                }
            }
            if (dfn[u] == low[u]) {
                int v;
                do {
                    v = stk.back();
                    stk.pop_back();
                    id[v] = cnt;
                } while (v != u);
                ++cnt;
            }
        };
        for (int i = 0; i < 2 * n; ++i) if (dfn[i] == -1) dfs(dfs, i);
        for (int i = 0; i < n; ++i) {
            if (id[2 * i] == id[2 * i + 1]) return false;
            ans[i] = id[2 * i] > id[2 * i + 1];
        }
        return true;
    }
    vector<bool> answer() { return ans; }
};