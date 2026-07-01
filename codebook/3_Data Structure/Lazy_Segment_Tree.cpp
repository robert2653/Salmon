template<class Info, class Tag> struct LazySegmentTree {
    int n;
    vector<Info> info;
    vector<Tag> tag;
    LazySegmentTree(int n) : n(n), info(4 << __lg(n)), tag(4 << __lg(n)) {}
    LazySegmentTree(const vector<Info> &v) : n(v.size()), info(4 << __lg(n)), tag(4 << __lg(n)) {
        auto build = [&](auto &&self, int l, int r, int p) {
            if (r - l == 1) {
                info[p] = v[l];
                return;
            }
            int m = (l + r) / 2;
            self(self, l, m, 2 * p);
            self(self, m, r, 2 * p + 1);
            pull(p);
        };
        build(build, 0, n, 1);
    }
    void pull(int p) { info[p] = info[2 * p] + info[2 * p + 1]; }
    void apply(const Tag &t, int l, int r, int p) {
        info[p].apply(t, l, r);
        tag[p].apply(t);
    }
    void push(int l, int r, int p) {
        int m = (l + r) / 2;
        apply(tag[p], l, m, 2 * p);
        apply(tag[p], m, r, 2 * p + 1); // tag 可位移 (m - l)
        tag[p] = Tag();
    }
    void modify(int x, const Info &i) { modify(x, i, 0, n, 1); }
    void modify(int x, const Info &i, int l, int r, int p) {
        if (r - l == 1) {
            info[p] = i;
            return;
        }
        int m = (l + r) / 2;
        push(l, r, p);
        if (x < m) modify(x, i, l, m, 2 * p);
        else modify(x, i, m, r, 2 * p + 1);
        pull(p);
    }
    Info query(int ql, int qr) { return query(ql, qr, 0, n, 1); } 
    Info query(int ql, int qr, int l, int r, int p) {
        if (qr <= l || ql >= r) return Info();
        if (ql <= l && r <= qr) return info[p];
        int m = (l + r) / 2;
        push(l, r, p);
        return query(ql, qr, l, m, 2 * p) + query(ql, qr, m, r, 2 * p + 1);
    }
    void rangeApply(int ql, int qr, const Tag &t) { rangeApply(ql, qr, t, 0, n, 1); }
    void rangeApply(int ql, int qr, const Tag &t, int l, int r, int p) {
        if (qr <= l || ql >= r) return;
        if (ql <= l && r <= qr) {
            apply(t, l, r, p); // tag 可位移 (l - ql)
            return;
        }
        int m = (l + r) / 2;
        push(l, r, p);
        rangeApply(ql, qr, t, l, m, 2 * p);
        rangeApply(ql, qr, t, m, r, 2 * p + 1);
        pull(p);
    }
    template<class F> int findFirst(int ql, int qr, F &&f) {
        return findFirst(ql, qr, f, 0, n, 1);
    } // 若要找 last，先右子樹遞迴即可
    template<class F> int findFirst(int ql, int qr, F &&f, int l, int r, int p) {
        if (qr <= l || ql >= r) return -1;
        if (ql <= l && r <= qr && !f(info[p])) return -1;
        if (r - l == 1) return l;
        int m = (l + r) / 2;
        push(l, r, p);
        int res = findFirst(ql, qr, f, l, m, 2 * p);
        if (res == -1) res = findFirst(ql, qr, f, m, r, 2 * p + 1);
        return res;
    }
};
struct Tag { // 有些 Tag 不用 push 例如 sweepLine
    ll setVal = 0;
    ll add = 0;
    void apply(const Tag &t) & {
        if (t.setVal) {
            setVal = t.setVal;
            add = t.add;
        } else {
            add += t.add;
        }
    }
};
struct Info {
    ll sum = 0;
    void apply(const Tag &t, int l, int r) & {
        if (t.setVal) {
            sum = (r - l) * t.setVal;
        }
        sum += (r - l) * t.add;
    } /*
    Info &operator=(const Info &i) & {
        // do something... 部分 assignment 使用
        return *this;
    } */
};
Info operator+(const Info &a, const Info &b) {
    Info c;
    c.sum = a.sum + b.sum;
    return c;
}