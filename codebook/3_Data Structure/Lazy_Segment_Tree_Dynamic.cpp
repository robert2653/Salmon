template<class Info, class Tag> struct LazySegmentTreeDynamic {
    struct Node {
        Info info = Info();
        Tag tag = Tag();
        bool isLazy = false;
        int lc = 0, rc = 0;
    };
    int n, rt;
    vector<Node> nd;
    LazySegmentTreeDynamic(int n) : n(n), rt(0), nd(1) {}
    int generate() {
        nd.emplace_back();
        return nd.size() - 1;
    }
    void pull(int p) { nd[p].info = nd[nd[p].lc].info + nd[nd[p].rc].info; }
    void modify(int x, const Info &i) { rt = modify(x, i, 0, n, rt); }
    int modify(int x, const Info &i, int l, int r, int p) {
        if (p == 0) p = generate();
        if (r - l == 1) {
            nd[p].info = i;
            return p;
        }
        push(l, r, p);
        int m = (l + r) / 2;
        if (x < m) {
            int y = modify(x, i, l, m, nd[p].lc);
            nd[p].lc = y;
        } else {
            int y = modify(x, i, m, r, nd[p].rc);
            nd[p].rc = y;
        }
        pull(p);
        return p;
    }
    Info query(int ql, int qr) { return query(ql, qr, 0, n, rt); }
    Info query(int ql, int qr, int l, int r, int p) {
        if (l >= qr || r <= ql || p == 0) return Info();
        if (ql <= l && r <= qr) return nd[p].info;
        push(l, r, p);
        int m = (l + r) / 2;
        return query(ql, qr, l, m, nd[p].lc) + query(ql, qr, m, r, nd[p].rc);
    }
    void apply(const Tag &t, int l, int r, int p) {
        nd[p].info.apply(t, l, r);
        nd[p].tag.apply(t);
        nd[p].isLazy = true;
    }
    void push(int l, int r, int p) {
        if (!nd[p].isLazy) return;
        int m = (l + r) / 2;
        if (nd[p].lc == 0) nd[p].lc = generate();
        if (nd[p].rc == 0) nd[p].rc = generate();
        apply(nd[p].tag, l, m, nd[p].lc);
        apply(nd[p].tag.offset(m - l), m, r, nd[p].rc);
        nd[p].tag = Tag();
        nd[p].isLazy = false;
    }
    void rangeApply(int ql, int qr, const Tag &t) { rt = rangeApply(ql, qr, t, 0, n, rt); }
    int rangeApply(int ql, int qr, const Tag &t, int l, int r, int p) {
        if (l >= qr || r <= ql) return p;
        if (p == 0) p = generate();
        if (ql <= l && r <= qr) {
            apply(t.offset(l - ql), l, r, p);
            return p;
        }
        push(l, r, p);
        int m = (l + r) / 2;
        nd[p].lc = rangeApply(ql, qr, t, l, m, nd[p].lc);
        nd[p].rc = rangeApply(ql, qr, t, m, r, nd[p].rc);
        pull(p);
        return p;
    }
    template<class T> int findFirst(int ql, int qr, T &&f) { return findFirst(ql, qr, f, 0, n, rt); }
    template<class T> int findFirst(int ql, int qr, T &&f, int l, int r, int p) {
        if (l >= qr || r <= ql || p == 0 || !f(nd[p].info)) return -1;
        if (r - l == 1) return l;
        int m = (l + r) / 2;
        push(l, r, p);
        int res = findFirst(ql, qr, f, l, m, nd[p].lc);
        if (res != -1) return res;
        return findFirst(ql, qr, f, m, r, nd[p].rc);
    }
};
struct Tag { // 有些 Tag 不用 push 例如 sweepLine
    void apply(const Tag &t) & {}
    Tag offset(int d) const { return *this; }
};
struct Info {
    void apply(const Tag &t, int l, int r) & {} /*
    Info &operator=(const Info &i) & {
        // do something... 部分 assignment 使用
        return *this;
    } */
};
Info operator+(const Info &a, const Info &b) {
    Info c;
    return c;
}