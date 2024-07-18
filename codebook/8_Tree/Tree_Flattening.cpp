// 父節點加值 = 所有子節點區間加值，求單點，使用 bit，做前綴差分
// CSES 1138_Path Queries
int main(){
    int n, q; cin >> n >> q;
    vector<int> node_value(n + 1), euler_ordered_value(n);
    for (int i = 1; i <= n; i++) {
        cin >> node_value[i];
    }
    vector<vector<int>> tree(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    vector<pair<int, int>> tree_mapping(n + 1);
    int cnt = 0;
    auto dfs = [&](auto self, int u, int par) -> void {
        euler_ordered_value[++cnt] = node_value[u];
        tree_mapping[u].first = cnt;
        for (auto v : tree[u]) {
            if (v == par) continue;
            self(self, v, u);
        }
        tree_mapping[u].second = cnt;
    };
    dfs(dfs, 1, 0);
    BIT bit(n);
    for (int i = 1; i <= n; i++) {
        bit.modify(tree_mapping[i].first, node_value[i]);
        if (tree_mapping[i].first < n) { // root 就不用扣了
            bit.modify(tree_mapping[i].second + 1, -node_value[i]);
        }
    }
    for (int i = 0; i < q; i++) {
        int op; cin >> op;
        if (op == 1) {
            int s, x; cin >> s >> x;
            int add = x - euler_ordered_value[tree_mapping[s].first];
            euler_ordered_value[tree_mapping[s].first] = x;
            bit.modify(tree_mapping[s].first, add);
            if (tree_mapping[s].first < n) { // root 就不用扣了
                bit.modify(tree_mapping[s].second + 1, -add);
            }
        }
        else {
            int node; cin >> node;
            cout << bit.query(tree_mapping[node].first) << "\n";
        }
    }
}