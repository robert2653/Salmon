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
        for (auto i : adj[u]) {
            if (i.w > 0 && lev[i.v] == -1) {
                q.push(i.v);
                lev[i.v] = lev[u] + 1;
            }
        }
    }
    return (lev[n] == -1 ? false : true);
}
int dfs(int u, int flow){
    if (u == n) return flow;
    for (auto &i : adj[u]) {
        if (lev[i.v] == lev[u] + 1 && !vis[i.v] && i.w > 0) {
            vis[i.v] = true;
            int ret = dfs(i.v, min(flow, i.w));
            if (ret > 0) {
                i.w -= ret;
                adj[i.v][i.rev_id].w += ret;
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
// edge set valid var, if we need to argument pos road, the reverse edge set true valid；
// if we need argument the argumented edge，both set false. Last, from v dfs ans times
bool get_road(int now, vector<int> &ans, vector<bool> &vis) {
    if(now == 1) return true;
    for(auto &v : adj[now]){
        if(v.arg_valid && !vis[v.to]) {
            ans.push_back(v.to);
            vis[v.to] = true;
            bool flag = get_road(v.to, ans, vis);
            if(flag){
                v.arg_valid = false;
                return true;
            }
            ans.pop_back();
        }
    }
    return false;
}