// CSES Police Chase
int g[505][505]; // 以 O(1) 紀錄存在邊
void solve(){
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        add_edge(u, v, 1);
    }
    dinic();
    fill(all(vis), 0);
    unordered_set<int> reach;
    auto find = [&](auto self, int u) -> void {
        if (!vis[u]) {
            vis[u] = 1;
            reach.insert(u);
            for (auto [v, w, _] : adj[u]){
                if(w > 0){
                    self(self, v);
                }
            }
        }
    };
    find(find, 1);
    cout << ans << "\n";
    for (auto u : reach) {
        for (auto [v, w, _] : adj[u]) {
            if (g[u][v] && !w && reach.find(v) == reach.end()) {
                cout << u << " " << v << "\n";
                // ans = sum(u_to_v)
            }
        }
    }
}