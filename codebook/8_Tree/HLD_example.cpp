#include <bits/stdc++.h>
using namespace std;

// CSES Path Queries II

struct HLD {
    int n;
    vector<int> siz, top, dep, parent, in, out, seq;
    vector<vector<int>> adj;
    int cur;
    
    HLD() {}
    HLD(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        siz.resize(n);
        top.resize(n);
        dep.resize(n);
        parent.resize(n);
        in.resize(n);
        out.resize(n);
        seq.resize(n);
        cur = 0;
        adj.assign(n, {});
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void work(int root = 0) {
        top[root] = root;
        dep[root] = 0;
        parent[root] = -1;
        dfs1(root);
        dfs2(root);
    }
    void dfs1(int u) {
        if (parent[u] != -1) {
            adj[u].erase(find(adj[u].begin(), adj[u].end(), parent[u]));
        }
        
        siz[u] = 1;
        for (auto &v : adj[u]) {
            parent[v] = u;
            dep[v] = dep[u] + 1;
            dfs1(v);
            siz[u] += siz[v];
            if (siz[v] > siz[adj[u][0]]) {
                swap(v, adj[u][0]);
            } // 讓 adj[u][0] 是重子節點
        }
    }
    void dfs2(int u) {
        in[u] = cur++;
        seq[in[u]] = u; // dfn 對應的編號
        for (auto v : adj[u]) {
            top[v] = v == adj[u][0] ? top[u] : v;
            dfs2(v);
        }
        out[u] = cur;
    }
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) {
                u = parent[top[u]];
            } else {
                v = parent[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    }
    
    int dist(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
    int jump(int u, int k) {
        if (dep[u] < k) {
            return -1;
        }
        int d = dep[u] - k;
        while (dep[top[u]] > d) {
            u = parent[top[u]];
        }
        return seq[in[u] - dep[u] + d];
    }
    bool isAncester(int u, int v) {
        // 判斷 u 是否是 v 的祖先
        return in[u] <= in[v] && in[v] < out[u];
    }
    int rootedParent(int u, int v) {
        // 根據新根節點 u 計算 v 的父節點
        swap(u, v);
        if (u == v) {
            return u;
        }
        if (!isAncester(u, v)) {
            return parent[u];
        }
        auto it = upper_bound(adj[u].begin(), adj[u].end(), v, [&](int x, int y) {
            return in[x] < in[y];
        }) - 1;
        return *it;
    }
    int rootedSize(int u, int v) {
        // 根據新根節點 u 計算子樹 v 的大小
        if (u == v) {
            return n;
        }
        if (!isAncester(v, u)) {
            return siz[v];
        }
        return n - siz[rootedParent(u, v)];
    }
    int rootedLca(int a, int b, int c) {
        // 根據新的根節點計算三個節點 a、b 和 c 的最近公共祖先
        return lca(a, b) ^ lca(b, c) ^ lca(c, a);
    }
};

template <class Info>
struct Seg {    // 左開右閉寫法
    int n;
    vector<Info> info;
    Seg(int n_, Info v_ = Info()) {
        init(n_, v_);
    }
    template <class T>
    Seg(vector<T> init_) {
        init(init_);
    }
    void init(int n_, Info v_ = Info()) {
        init(vector(n_, v_));
    }
    template <class T>
    void init(vector<T> init_) {
        n = init_.size();
        info.assign(4 << __lg(n), Info());
        function <void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init_[l];
                return;
            }
            int m = (l + r) / 2;
            build(p * 2, l, m);
            build(p * 2 + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }
    void pull(int p) { info[p] = info[p * 2] + info[p * 2 + 1]; }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info &i) {
        modify(1, 0, n, p, i);
    }
    Info query(int p, int l, int r, int ql, int qr) {
        if (qr <= l || ql >= r) return Info();
        if (ql <= l && r <= qr) return info[p];
        int m = (l + r) / 2;
	    return query(p * 2, l, m, ql, qr) + query(p * 2 + 1, m, r, ql, qr);
    }
    Info query(int ql, int qr) { return query(1, 0, n, ql, qr); }
    template<class F>   // 尋找區間內，第一個符合條件的
    int findFirst(int p, int l, int r, int x, int y, F &&pred) {
        if (l >= y || r <= x) {
            return -1;
        }
        if (l >= x && r <= y && !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int res = findFirst(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = findFirst(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }
    template<class F>   // 若要找 last，先右子樹遞迴即可
    int findFirst(int l, int r, F &&pred) {
        return findFirst(1, 0, n, l, r, pred);
    }
};
// ---define structure and info plus---
struct Info {
    int max;
    Info() { max = 0; }
    Info(int _max) { max = _max; }
};
Info operator + (const Info &a, const Info &b) {
    return { max(a.max, b.max) };
}

void solve(){
    int n, q; cin >> n >> q;
    HLD hld(n);
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        hld.addEdge(u, v);
    }
    hld.work();
    vector<Info> init_(n);
    for (int i = 0; i < n; i++) {
        init_[hld.in[i]].max = a[i];
    }
    Seg<Info> seg(init_);
    for (int i = 1; i <= q; i++) {
        int op; cin >> op;
        if (op == 1) {
            int u, x; cin >> u >> x;
            u--;
            seg.modify(hld.in[u], Info(x));
        }
        else {
            int a, b; cin >> a >> b;
            a--; b--;
            int res = 0;
            while (hld.top[a] != hld.top[b]) { // a, b 不在同一條鍊上
                if (hld.dep[hld.top[a]] > hld.dep[hld.top[b]]) {
                    swap(a, b); // 選擇較深的 b 跳鍊
                }
                res = max(res, seg.query(hld.in[hld.top[b]], hld.in[b] + 1).max);
                b = hld.parent[hld.top[b]];
            }
            if (hld.dep[a] > hld.dep[b]) {
                swap(a, b); // 確保 a 比 b 淺, in[a] < in[b]
            }
            res = max(res, seg.query(hld.in[a], hld.in[b] + 1).max);
            cout << res << " ";
        }
    }
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