#include <bits/stdc++.h> // LCA from 1
using namespace std;
int main() {
    int n, q; cin >> n >> q;
    vector<vector<int>> tree(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    vector<vector<int>> par(n + 1, vector<int>(18));
    vector<int> depth(n + 1);
    auto dfs = [&](auto self, int u, int pre) -> void {
        for (auto v : tree[u]) {
            if (v == pre) continue;
            par[v][0] = u;  // 2 ^ 0
            depth[v] = depth[u] + 1;
            self(self, v, u);
        }
    };
    dfs(dfs, 1, 0);
    for (int i = 1; i < 18; i++) {
        for (int j = 1; j <= n; j++) {
            par[j][i] = par[par[j][i - 1]][i - 1];
        }
    }
    auto lca = [&](int a, int b) -> int {
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
    };
}