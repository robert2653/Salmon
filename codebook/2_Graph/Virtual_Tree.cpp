// 多次詢問給某些關鍵點, 虛樹可達成快速樹 DP (前處理每個點)
// 例如這題是有權樹，給一些關鍵點, 求跟 vertex 1 隔開的最小成本
// 前處理 root 到所有點的最小邊權
void solve(int n, vector<vector<pair<int, int>>> &g, int q) {
    build(n, g); // build LCA
    vector<int> dis(n, 1E9); // root 到各點的最小邊權
    [&](this auto &&self, int x, int p) -> void {
        for (auto [y, w] : g[x]) {
            if (y == p) continue;
            dis[y] = min(w, dis[x]);
            self(y, x);
        }
    } (0, -1);
    vector<vector<int>> vt(n);
    vector<int> isKey(n);
    vector<ll> dp(n);
    while (q--) {
        int m; cin >> m;
        vector<int> key(m);
        for (int i = 0; i < m; i++) {
            cin >> key[i];
            isKey[--key[i]] = 1;
        }
        key.push_back(0); // 固定 0 為 root, 看題目需求
        sort(key.begin(), key.end(), [&](int a, int b) {
            return dfn[a] < dfn[b];
        }); // 要 sort 再 insert
        vector<int> stk; // 維護一條虛樹鏈
        for (int k : key) {
            if (stk.empty()) {
                stk.push_back(k);
                continue;
            }
            int l = lca(stk.back(), k);
            if (l == stk.back()) { // 直接一條鏈
                stk.push_back(k);
                continue;
            } // 次頂是 lca 的子孫，直接跟最頂連邊
            while (stk.size() > 1 && dfn[stk[stk.size() - 2]] > dfn[l]) {
                vt[stk[stk.size() - 2]].push_back(stk.back());
                stk.pop_back();
            } // 保證 back 是 lca 的子孫，且次頂不是 lca 的子孫
            vt[l].push_back(stk.back());
            if (stk.size() < 2 || stk[stk.size() - 2] != l) stk.back() = l;
            else stk.pop_back(); // lca 的子孫已經用不到了，直接換成 lca
            stk.push_back(k);
        }
        while (stk.size() > 1) {
            vt[stk[stk.size() - 2]].push_back(stk.back());
            stk.pop_back();
        }
        int rt = stk[0]; stk.clear();
        [&](this auto &&self, int x) -> void {
            for (auto y : vt[x]) {
                self(y);
                if (isKey[y]) { // 直接砍了
                    dp[x] += dis[y];
                } else { // 不砍 or 砍
                    dp[x] += min<ll>(dp[y], dis[y]);
                } // 記得 reset
                isKey[y] = dp[y] = 0;
            }
            vt[x].clear(); // 記得 reset
        } (rt);
        cout << dp[rt] << "\n";
        isKey[rt] = 0;
        dp[rt] = 0; // 最後 reset root
    }
}