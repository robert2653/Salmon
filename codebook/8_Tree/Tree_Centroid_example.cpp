#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int> cnt; // 當前深度數量
ll ans = 0;
int k; int mx_depth = 0;

struct centroid_decomposition {
    int n;
    vector<vector<int>> adj;
    vector<bool> vis;
    vector<int> siz;
    centroid_decomposition() {}
    centroid_decomposition(int n_) { init(n_); }
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
        mx_depth = max(mx_depth, dep); // add
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

    void get_ans(int x, int p, int dep, bool upd) {
        if (dep > k) return;
        mx_depth = max(dep, mx_depth);
        if (upd) cnt[dep]++;
        else ans += cnt[k - dep];
        for (int y : adj[x]) {
            if (y == p || vis[y]) continue;
            get_ans(y, x, dep + 1, upd);
        }
    }

    void work(int x = 0) {
        mx_depth = 0;
        get_siz(0, x);
        int cen = get_cen(x, siz[x]);
        vis[cen] = true;
        if (mx_depth * 2 < k) return; // 剪枝
        mx_depth = 0;
        // do something
        for (int y : adj[cen]) {
            if (vis[y]) continue;
            get_ans(y, cen, 1, false);
            get_ans(y, cen, 1, true);
        }
        fill(cnt.begin() + 1, cnt.begin() + mx_depth + 1, 0);
        for (int y : adj[cen]) {
            if (vis[y]) continue;
            work(y);
        }
    }
};

void solve() {
    int n; cin >> n;
    centroid_decomposition g;
    cin >> k;
    g.init(n);

    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        g.addEdge(u, v);
    }
    cnt.resize(n);
    cnt[0] = 1;
    g.work(0);

    cout << ans << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}