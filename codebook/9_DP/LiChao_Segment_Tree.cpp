// 應用: dp(i) = h(i) + min/max(A(j)X(i) + B(j)), for j ≤ r(i)
//        y    =  c   +          m  x   +   b
constexpr ll inf = 4E18;
struct Line {
    ll m, b;
    Line(ll m = 0, ll b = inf) : m(m), b(b) {}
    ll eval(ll x) { return m * x + b; }
};
struct LiChaoSeg { // 取 max 再變換就好
    int n;
    vector<Line> info;
    LiChaoSeg(int n_ = 0) { init(n_); }
    void init(int n_) {
        n = n_;
        info.assign(4 << __lg(n), Line());
    }
    void update(Line line, int p, int l, int r) {
        int m = (l + r) / 2;
        bool left = line.eval(l) < info[p].eval(l);
        bool mid = line.eval(m) < info[p].eval(m);
        if (mid) swap(info[p], line); // 如果新線段比較好
        if (r - l == 1) return;
        else if (left != mid) update(line, 2 * p, l, m);
        // 代表左半有交點
        else update(line, 2 * p + 1, m, r); 
        // 代表如果有交點一定在右半
    }
    void rangeUpdate(Line line, int p, int l, int r, int ql, int qr) {
        if (l >= qr || r <= ql) return;
        if (l >= ql && r <= qr) {
            update(line, p, l, r);
            return;
        }
        int m = (l + r) / 2;
        rangeUpdate(line, 2 * p, l, m, ql, qr);
        rangeUpdate(line, 2 * p + 1, m, r, ql, qr);
    }
    void addLine(Line line) {
        update(line, 1, 0, n);
    }
    void rangeAddLine(Line line, int ql, int qr) {
        rangeUpdate(line, 1, 0, n, ql, qr);
    }
    ll query(int x, int p, int l, int r) {
        if (r - l == 1) return info[p].eval(x);
        int m = (l + r) / 2;
        if (x < m) {
            return min(info[p].eval(x), query(x, 2 * p, l, m));
        } else {
            return min(info[p].eval(x), query(x, 2 * p + 1, m, r));
        }
    }
    ll query(int x) { return query(x, 1, 0, n); }
};