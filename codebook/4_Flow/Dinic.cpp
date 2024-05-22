// template dinic max flow
struct edge {
    int v, w, rev_id;
};
int n, m, ans = 0;
vector<edge> adj[505];
vector<int> lev(505), vis(505);
bool label_level(){ // 標記深度，如果到不了終點 return false
    fill(all(lev), -1); lev[1] = 0;
    queue<int> q;   q.push(1);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto &[v, w, rev_id] : adj[u]) {
            if (w > 0 && lev[v] == -1) {
                q.push(v);
                lev[v] = lev[u] + 1;
            }
        }
    }
    return (lev[n] == -1 ? false : true);
}
int dfs(int u, int flow){
    if (u == n) return flow;
    for (auto &[v, w, rev_id] : adj[u]) {
        if (lev[v] == lev[u] + 1 && !vis[v] && w > 0) {
            vis[v] = true;
            int ret = dfs(v, min(flow, w));
            if (ret > 0) {
                w -= ret;
                adj[v][rev_id].w += ret;
                return ret;
            }
        }
    }
    return 0;   // 到不了終點就會 return 0
}
void add_edge(int u, int v, int w) { // 無向圖的話兩邊都是 w
    adj[u].push_back({v, w, (int)adj[v].size()});
    adj[v].push_back({u, 0, (int)adj[u].size() - 1});
}
void dinic() {
    while (label_level()) {
        while (true) {
            fill(all(vis), 0);
            int tmp = dfs(1, inf);
            if (tmp == 0) break;
            ans += tmp;
        }
    }
    cout << ans;
}

// Distinct Route
// 給你一張有向圖，求從走 1 到 n 的最多方法數，並且邊不重複
// dfs 要改成
int dfs(int u, int flow){
    if (u == n) return flow;
    for (auto &[v, w, rev_id, arg_valid] : adj[u]){
        if (lev[v] == lev[u] + 1 && !vis[v] && w > 0) {
            vis[v] = true;
            int ret = dfs(v, min(flow, w));
            if (ret > 0) {
                w -= ret;
                adj[v][rev_id].w += ret;
                if (arg_valid) {    // 走的是 arg 路，Reset
                    arg_valid = 0;
                    adj[v][rev_id].arg_valid = 0;
                }
                else adj[v][rev_id].arg_valid = 1;    // 走正常路
                return ret;
            }
        }
    }
    return 0;   // 到不了終點就會 return 0
}
bool get_road(int now, vector<int> &ans, vector<bool> &vis) {
    if (now == 1) return true;
    for (auto &[v, w, rev_id, arg_valid] : adj[now]) {
        if (arg_valid && !vis[v]){
            ans.push_back(v);
            vis[v] = true;
            bool flag = get_road(v, ans, vis);
            if (flag) {
                arg_valid = false;
                return true;
            }
            ans.pop_back();
        }
    }
    return false;
}