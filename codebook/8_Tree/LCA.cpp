vector<vector<int>> par(maxn, vector<int>(18));
vector<int> depth(maxn + 1);
vector<int> dfn(maxn);
void build(int n, vector<vector<pair<int, int>>> &tree) {
    auto dfs = [&](auto self, int u, int pre) -> void {
        for (auto [v, w] : tree[u]) {
            if (v == pre) continue;
            par[v][0] = u;  // 2 ^ 0
            depth[v] = depth[u] + 1;
            self(self, v, u);
        }
    };
    dfs(dfs, 1, 0);
    for (int i = 1; i <= 18; i++) {
        for (int j = 1; j <= n; j++) {
            par[j][i] = par[par[j][i - 1]][i - 1];
        }
    }
}
int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    int pull = depth[a] - depth[b];
    for (int i = 0; i < 18; i++) {
        if (pull & (1 << i)) {
            a = par[a][i];
        }
    }
    if (a == b) return a;
    for (int i = 17; i >= 0; i--) {
        if (par[a][i] != par[b][i]) {
            a = par[a][i], b = par[b][i];
        }
    }
    return par[a][0];
}