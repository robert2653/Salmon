// 父節點加值 = 所有子節點區間加值，求單點，使用 bit，做前綴差分
// CSES 1138_Path Queries
void treeFlattening() {
    int n, q; cin >> n >> q;
    vector<int> val(n + 1), dfnToVal(n);
    for (int i = 1; i <= n; i++) {
        cin >> val[i];
    }
    vector<vector<int>> tree(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    vector<pair<int, int>> mp(n + 1); // dfn 區間
    int cnt = 0;
    auto dfs = [&](auto self, int u, int par) -> void {
        dfnToVal[++cnt] = val[u];
        mp[u].first = cnt;
        for (auto v : tree[u]) {
            if (v == par) continue;
            self(self, v, u);
        }
        mp[u].second = cnt;
    };
    dfs(dfs, 1, 0);
    BIT bit(n);
    for (int i = 1; i <= n; i++) {
        bit.modify(mp[i].first, val[i]);
        if (mp[i].first < n) { // root 就不用扣了
            bit.modify(mp[i].second + 1, -val[i]);
        }
    }
    for (int i = 0; i < q; i++) {
        int op; cin >> op;
        if (op == 1) {
            int s, x; cin >> s >> x;
            int add = x - dfnToVal[mp[s].first];
            dfnToVal[mp[s].first] = x;
            bit.modify(mp[s].first, add);
            if (mp[s].first < n) { // root 就不用扣了
                bit.modify(mp[s].second + 1, -add);
            }
        } else {
            int node; cin >> node;
            cout << bit.query(mp[node].first) << "\n";
        }
    }
}