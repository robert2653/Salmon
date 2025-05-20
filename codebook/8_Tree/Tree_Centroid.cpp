struct CentriodDecomposition {
    int n;
    vector<vector<int>> adj;
    vector<bool> vis;
    vector<int> siz;
    CentriodDecomposition(int n) : n(n) {
        adj.assign(n, {});
        vis.assign(n, false);
        siz.assign(n, 1);
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void getSiz(int x, int p = -1) {
        siz[x] = 1;
        for (int y : adj[x]) {
            if (y == p || vis[y]) continue;
            getSiz(y, x);
            siz[x] += siz[y];
        }
    }
    int getCen(int x, int sz, int p = -1) {
        for (int y : adj[x]) {
            if (y == p || vis[y]) continue;
            if (siz[y] * 2 > sz)
                return getCen(y, sz, x);
        }
        return x;
    }
    void getAns(int x, int p) {
        // do something
        for (int y : adj[x]) {
            if (y == p || vis[y]) continue;
            getAns(y, x);
        }
    }
    void work(int x = 0) {
        getSiz(0, x);
        int cen = getCen(x, siz[x]);
        vis[cen] = true;
        for (int y : adj[cen]) {
            if (vis[y]) continue;
            getAns(y, cen);
        }
        for (int y : adj[cen]) {
            if (vis[y]) continue;
            work(y);
        }
    }
};