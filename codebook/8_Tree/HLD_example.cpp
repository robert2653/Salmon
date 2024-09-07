// CSES Path_Queries_II
struct Info {
    int max = 0;
};
Info operator+(const Info &a, const Info &b) {
    return { max(a.max, b.max) };
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;
    HLD hld(n);
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<pair<int, int>> in(n - 1);
    for (int i = 0; i < n - 1; i++) {
        cin >> in[i].first >> in[i].second;
    }
    for (int i = 0; i < n - 1; i++) {
        auto [u, v] = in[i];
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
            seg.modify(hld.in[u], {x});
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
    cout << "\n";
    return 0;
}