// 當存在關鍵點且除了關鍵點的根關鍵點的 LCA 都沒用處
// 可以建立虛樹達成快速樹 DP
// 例如這題是有權樹，跟 vertex 1 隔開的最小成本
int top = -1; vector<int>stk(maxn);
void insert(int u, vector<vector<int>> &vt) {
    if (top == -1) return stk[++top] = u, void();
    int l = lca(stk[top], u);
    if (l == stk[top]) return stk[++top] = u, void();
    while (dfn[l] < dfn[stk[top - 1]])
        vt[stk[top - 1]].push_back(stk[top]), top--;
    if (stk[top - 1] != l) {
        vt[l].push_back(stk[top]);
        stk[top] = l;
    } else vt[l].push_back(stk[top--]);
    stk[++top] = u;
}
void reset(int u, vector<vector<int>> &vt) {
    for (int i : vt[u]) reset(i, vt);
    vt[u].clear();
}
void solve(int n, int q) {
    vector g(n + 1, vector<pair<int, int>>());
    vector vt(n + 1, vector<int>()); // dfs 完清除，否則會退化
    vector<ll> dp(n + 1), iskey(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w; cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    build_lca(n, g);
    build(n, g);
    for (int i = 0; i < q; i++) {
        int m; top = -1; cin >> m;
        vector<int> key(m);
        for (int j = 0; j < m; j++) {
            cin >> key[j];
            iskey[key[j]] = 1;
        }
        key.push_back(1);   // 看題目，需要才放
        sort(all(key), [&](int a, int b) {
            return dfn[a] < dfn[b];
        });
        for (int x : key) insert(x, vt);
        while (top > 0) vt[stk[top - 1]].push_back(stk[top]), --top;
        // DP
        auto dfs = [&](auto self, int u) -> void {
            for (auto v : vt[u]) {
                self(self, v);
                if (iskey[v]) {
                    dp[u] += min_dis[v];
                    // 砍掉 1 到 v 之間最短的路
                }
                else {
                    dp[u] += min(dp[v], min_dis[v]);
                }
                iskey[v] = dp[v] = 0;
            }
            vt[u].clear();
        };
        dfs(dfs, key[0]); // key[0] 一定是 root
        cout << dp[key[0]] << "\n";
        iskey[key[0]] = dp[key[0]] = 0;
    }
}