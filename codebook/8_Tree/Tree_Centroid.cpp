int get_centroid(vector<vector<int>> &adj, vector<int> &vis, vector<int> &siz, int u, int pre) {
    auto get_sz = [&](auto &&self, int u, int pre) -> void {
        siz[u] = 1;
        for (int v : adj[u]) {
            if (v == pre) continue;
            if (vis[v]) continue;
            self(self, v, u);
            siz[u] += siz[v];
        }
    };
    auto get_cen = [&](auto &&self, int tot_sz, int u, int pre) -> int {
        for (auto v : adj[u]) {
            if (v == pre) continue;
            if (vis[v]) continue;
            if (siz[v] * 2 > tot_sz){
                return self(self, tot_sz, v, u);
            }
        }
        return u;
    };
    get_sz(get_sz, u, pre);
    return get_cen(get_cen, siz[u], u, pre);
}