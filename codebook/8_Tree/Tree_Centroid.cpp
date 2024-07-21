struct CenDecom {
    int n;
    vector<vector<int>> adj;
    vector<bool> vis;
    vector<int> siz;
    CenDecom() {}
    CenDecom(int n_) { init(n_); }
    void init(int n_) {
        n = n_;
        adj.assign(n, {});
        vis.assign(n, false);
        siz.assign(n, 1);
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void get_siz(int dep, int x, int p = -1) {
        siz[x] = 1;
        for (int y : adj[x]) {
            if (y == p || vis[y]) continue;
            get_siz(dep + 1, y, x);
            siz[x] += siz[y];
        }
    }
    int get_cen(int x, int sz, int p = -1) {
        for (int y : adj[x]) {
            if (y == p || vis[y]) continue;
            if (siz[y] * 2 > sz) {
                return get_cen(y, sz, x);
            }
        }
        return x;
    }
    void work(int x = 0) {
        get_siz(0, x);
        int cen = get_cen(x, siz[x]);
        vis[cen] = true;
        // do something
        for (int y : adj[cen]) {
            if (vis[y]) continue;
            work(y);
        }
    }
};