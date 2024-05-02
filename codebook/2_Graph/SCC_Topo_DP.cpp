#include <bits/stdc++.h>
using namespace std;
#define int long long
// 找到所有 SCC 然後結合原圖重建一個 DAG，然後拓樸 DP
void dfs(int u, vector<int> &vis, vector<int> &kosaraju, vector<vector<int>> &adj) {
    if (!vis[u]) {
        vis[u] = 1;
        for (auto v : adj[u]) {
            dfs(v, vis, kosaraju, adj);
        }
        kosaraju.push_back(u);  // finish time 小到大排列
    }
}
void rev_dfs(int u, vector<int> &vis, vector<int> &order, vector<vector<int>> &rev_adj, int &scc_num) {
    if (!vis[u]) {
        vis[u] = 1;
        order[u] = scc_num;
        for (auto v : rev_adj[u]) {
            rev_dfs(v, vis, order, rev_adj, scc_num);
        }
    }
}
signed main() {
    int n, m, scc_num = 0;
    cin >> n >> m;
    vector<int> coin(n + 1), order(n + 1), vis(n + 1, 0);
    vector<vector<int>> adj(n + 1), rev_adj(n + 1);
    vector<int> kosaraju;
    for (int i = 1; i <= n; i++) {
        cin >> coin[i];
    }
    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        rev_adj[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs(i, vis, kosaraju, adj);
        }
    }
    reverse(kosaraju.begin(), kosaraju.end());  // 轉過來，從 finish time 大的開始做 dfs
    vis.assign(n + 1, 0);
    for (auto &u : kosaraju) {
        if (!vis[u]) {
            scc_num++;
            rev_dfs(u, vis, order, rev_adj, scc_num);
        }
    }
    // 重新建 DAG，根據原圖，如果不再同個 SCC，對 order 加邊
    vector<vector<int>> DAG(scc_num + 1, vector<int>());
    vector<int> in_degree(scc_num + 1, 0);
    vector<int> sum_coin(scc_num + 1, 0), dp_coin(scc_num + 1, 0);
    set<pair<int, int>> st;
    int ans = -1e9;
    for (int i = 1; i <= n; i++) {
        sum_coin[order[i]] += coin[i];
        for (auto j : adj[i]) {
            // 如果不是在同一個 SCC 且 order 邊還沒加過
            if (order[i] != order[j] && st.find({order[i], order[j]}) == st.end()) {
                DAG[order[i]].push_back(order[j]);
                in_degree[order[j]]++;
                st.insert({order[i], order[j]});
            }
        }
    }
    // 對 DAG 拓蹼 DP
    queue<int> q;
    for (int i = 1; i <= scc_num; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int now = q.front(); q.pop();
        dp_coin[now] += sum_coin[now];
        ans = max(ans, dp_coin[now]);
        for (auto v : DAG[now]) {
            in_degree[v]--;
            dp_coin[v] = max(dp_coin[v], dp_coin[now]);
            if (in_degree[v] == 0) q.push(v);
        }
    }
    cout << ans;
}