vector<vector<int>> par;
vector<int> dep;
void build(int n, vector<vector<int>> &tree, int u = 0) {
    par.assign(n, vector<int>(B + 1, -1));
    dep.assign(n, 0);
    auto dfs = [&](auto self, int x, int p) -> void {
        for (auto y : tree[x]) {
            if (y == p) continue;
            par[y][0] = x;  // 2 ^ 0
            dep[y] = dep[x] + 1;
            self(self, y, x);
        }
    };
    par[u][0] = u; dfs(dfs, 0, -1);
    for (int i = 1; i <= B; i++) {
        for (int j = 0; j < n; j++) {
            par[j][i] = par[par[j][i - 1]][i - 1];
        }
    }
}
int lca(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    int pull = dep[a] - dep[b];
    for (int i = 0; i <= B; i++) {
        if (pull & (1 << i)) {
            a = par[a][i];
        }
    }
    if (a == b) return a;
    for (int i = B; i >= 0; i--) {
        if (par[a][i] != par[b][i]) {
            a = par[a][i], b = par[b][i];
        }
    }
    return par[a][0];
}
int jump(int x, int k) {
    for (int i = B; i >= 0; i--) {
        if (k >> i & 1) {
            x = par[x][i];
        }
    }
    return x;
}