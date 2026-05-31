template<class Info, class Tag = bool()>
struct SegmentTree { // [l, r), uncomment /**/ to lazy
    int n;
    vector<Info> info;
    /* vector<Tag> tag; */
    template<class T> SegmentTree(const vector<T> &v) {
        n = v.size();
        info.resize(4 * n);
        /* tag.resize(4 * n); */
        function<void(int, int, int)> build = [&](int l, int r, int p) {
            if (r - l == 1) {
                info[p] = v[l];
                return;
            }
            int m = (l + r) / 2;
            build(l, m, 2 * p);
            build(m, r, 2 * p + 1);
            pull(p);
        };
        build(0, n, 1);
    }
    void pull(int p) { info[p] = info[2 * p] + info[2 * p + 1]; } /*
    void apply(const Tag &t, int l, int r, int p) {
        info[p].apply(t, l, r);
        tag[p].apply(t);
    }
    void push(int l, int r, int p) {
        int m = (l + r) / 2;
        if (r - l >= 1) {
            apply(tag[p], l, m, 2 * p);
            apply(tag[p], m, r, 2 * p + 1);
        }
        tag[p] = Tag();
    } */
    void modify(int x, const Info &i) { modify(x, i, 0, n, 1); }
    void modify(int x, const Info &i, int l, int r, int p) {
        if (r - l == 1) {
            info[p] = i;
            return;
        }
        int m = (l + r) / 2;
        /* push(l, r, p); */
        if (x < m) modify(x, i, l, m, 2 * p);
        else       modify(x, i, m, r, 2 * p + 1);
        pull(p);
    }
    Info query(int ql, int qr) { return query(ql, qr, 0, n, 1); } 
    Info query(int ql, int qr, int l, int r, int p) {
        if (qr <= l || ql >= r) return Info();
        if (ql <= l && r <= qr) return info[p];
        int m = (l + r) / 2;
        /* push(l, r, p); */
        return query(ql, qr, l, m, 2 * p) + query(ql, qr, m, r, 2 * p + 1);
    } /*
    void rangeApply(int ql, int qr, const Tag &t) { rangeApply(ql, qr, t, 0, n, 1); }
    void rangeApply(int ql, int qr, const Tag &t, int l, int r, int p) {
        if (qr <= l || ql >= r) return;
        if (ql <= l && r <= qr) {
            apply(t, l, r, p);
            return;
        }
        int m = (l + r) / 2;
        push(l, r, p);
        rangeApply(ql, qr, t, l, m, 2 * p);
        rangeApply(ql, qr, t, m, r, 2 * p + 1);
        pull(p);
    } */
    template<class F> int findFirst(int ql, int qr, F &&pred) {
        return findFirst(ql, qr, pred, 0, n, 1);
    } // 若要找 last，先右子樹遞迴即可
    template<class F> int findFirst(int ql, int qr, F &&pred, int l, int r, int p) {
        if (l >= qr || r <= ql) return -1;
        if (l >= ql && r <= qr && !pred(info[p])) return -1;
        if (r - l == 1) return l;
        int m = (l + r) / 2;
        /* push(l, r, p); */
        int res = findFirst(ql, qr, pred, l, m, 2 * p);
        if (res == -1) res = findFirst(ql, qr, pred, m, r, 2 * p + 1);
        return res;
    }
};
// 有些 Tag 不用 push 例如 sweepLine
/* struct Tag {
    int setVal = 0;
    int add = 0;
    void apply(const Tag &t) & {
        if (t.setVal) {
            setVal = t.setVal;
            add = t.add;
        } else {
            add += t.add;
        }
    }
}; */
struct Info {
    ll sum = 0; /*
    void apply(const Tag &t, int l, int r) & {
        if (t.setVal) {
            sum = (r - l) * t.setVal;
        }
        sum += (r - l) * t.add;
    } *//*
    Info &operator=(const Info &i) & {
        // do something... 部分 assignment 使用
        return *this;
    } */
    Info &operator=(const ll x) & {
        sum = x;
        return *this;
    }
};
Info operator+(const Info &a, const Info &b) {
    Info c;
    c.sum = a.sum + b.sum;
    return c;
}