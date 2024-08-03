template<class Info>
struct PST {
    struct Node {
        Info info = Info();
        int lc = 0, rc = 0;
    };
    vector<Node> nd;
    int n = 0; vector<int> rt;
    PST() : n(0) {}
    PST(int n_, Info v_ = Info()) { init(n_, v_); }
    template<class T>
    PST(vector<T> init_) { init(init_); }
    void init(int n_, Info v_ = Info()) {
        init(vector<Info>(n_, v_));
    }
    template<class T>
    void init(vector<T> init_) {
        n = init_.size();
        nd.clear(); rt.clear();
        nd.emplace_back(); // 讓 root 指向 1-based
        rt.push_back(build(0, n, init_));
    }
    int build(int l, int r, const vector<Info> &init_) {
        int id = nd.size();
        nd.emplace_back();
        if (r - l == 1) {
            nd[id].info = init_[l];
            return id;
        }
        int m = (l + r) >> 1;
        nd[id].lc = build(l, m, init_);
        nd[id].rc = build(m, r, init_);
        pull(nd[id]);
        return id;
    }
    void pull(Node &t) {
        t.info = nd[t.lc].info + nd[t.rc].info;
    }
    int copy(int t) {
        nd.push_back(nd[t]);
        return nd.size() - 1;
    }
    int modify(int t, int p, const Info &v, int l, int r) {
        int nt = copy(t);
        if (r - l == 1) {
            nd[nt].info = v;
            return nt;
        }
        int m = (l + r) >> 1;
        if (p < m) {
            nd[nt].lc = modify(nd[t].lc, p, v, l, m);
        } else {
            nd[nt].rc = modify(nd[t].rc, p, v, m, r);
        }
        pull(nd[nt]);
        return nt;
    }
    void modify(int ver, int pos, const Info& val) {
        rt[ver] = modify(rt[ver], pos, val, 0, n);
    }
    Info query(int t, int ql, int qr, int l, int r) {
        if (l >= qr || r <= ql) return Info();
        if (ql <= l && r <= qr) return nd[t].info;
        int m = (l + r) >> 1;
        return query(nd[t].lc, ql, qr, l, m) + query(nd[t].rc, ql, qr, m, r);
    }
    Info query(int ver, int ql, int qr) {
        return query(rt[ver], ql, qr, 0, n);
    }
    void createVersion(int ori_ver) {
        rt.push_back(copy(rt[ori_ver]));
    }
    void reserve(int n, int q) {
        nd.reserve(n + q * (2 * __lg(n) + 1));
        rt.reserve(q + 1);
    }
};
struct Info {
    int sum = 0;
};
Info operator+(const Info &a, const Info &b) {
    return { a.sum + b.sum };
}