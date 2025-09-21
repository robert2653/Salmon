// recursive solution
void minEuclideanDistance() {
    int n; cin >> n;
    const ll inf = 8E18;
    vector<P> a(n);
    for (int i = 0; i < n; i++) {
        ll x, y; cin >> x >> y;
        a[i] = P(x, y);
    }
    struct sortY { bool operator()(const P &a, const P &b) const { return a.y < b.y; } };
    struct sortXY {
        bool operator()(const P &a, const P &b) const {
            return a.x == b.x ? a.y < b.y : a.x < b.x;
        }
    };
    sort(a.begin(), a.end(), sortXY());
    vector<P> t(n);
    auto divide = [&](auto &&self, int l, int r) -> ll {
        if (l == r) return inf;
        int m = (l + r) / 2;	
        ll ans = min(self(self, l, m), self(self, m + 1, r));
        ll midval = a[m].x;
        ll p = 0;
        for (int i = l; i <= r; i++)
            if ((midval - a[i].x) * (midval - a[i].x) <= ans)
                t[p++] = a[i];
        sort(t.begin(), t.begin() + p, sortY());
        for (int i = 0; i < p; i++) {
            for (int j = i + 1; j < p; j++) {
                ans = min(ans, square(t[i] - t[j]));
                if ((t[i].y - t[j].y) * (t[i].y - t[j].y) > ans) break;
            } 
        }
        return ans;
    };
    cout << divide(divide, 0, n - 1) << "\n";
}
// K-D tree solution
template<class Info>
struct KDTree { // 1-indexed
    static constexpr int DIM = Info::DIM;
    int n, rt;
    vector<Info> info;
    vector<int> l, r;
    KDTree(const vector<Info> &info) : n(info.size()), info(info), l(n + 1), r(n + 1) {
        rt = build(1, n);
    }
    void pull(int p) {
        info[p].L = info[p].R = info[p].x;
        info[p].pull(info[l[p]], info[r[p]]);
        for (int ch : {l[p], r[p]}) {
            if (!ch) continue;
            for (int k = 0; k < DIM; k++) {
                info[p].L[k] = min(info[p].L[k], info[ch].L[k]);
                info[p].R[k] = max(info[p].R[k], info[ch].R[k]);
            }
        }
    }
    int build(int l, int r) {
        if (r == l) return 0;
        int m = (l + r) / 2;
        array<double, DIM> av = {}, va = {};
        for (int i = l; i < r; i++)
            for (int d = 0; d < DIM; d++)
                av[d] += info[i].x[d];
        for (int d = 0; d < DIM; d++)
            av[d] /= (double)(r - l);
        for (int i = l; i < r; i++)
            for (int d = 0; d < DIM; d++)
                va[d] += (info[i].x[d] - av[d]) * (info[i].x[d] - av[d]);
        int dep = max_element(va.begin(), va.end()) - va.begin();
        nth_element(info.begin() + l, info.begin() + m, info.begin() + r,
            [&](const Info &x, const Info &y) { return x.x[dep] < y.x[dep]; });
        this->l[m] = build(l, m);
        this->r[m] = build(m + 1, r);
        pull(m); return m;
    }
    ll ans = 9E18;
    ll dist(int a, int b) {
        return (info[a].x[0] - info[b].x[0]) * (info[a].x[0] - info[b].x[0]) + 
        (info[a].x[1] - info[b].x[1]) * (info[a].x[1] - info[b].x[1]);
    }
    void query(int p, int x) {
        if (!p) return;
        if (p != x) ans = min(ans, dist(x, p));
        ll distl = info[x].f(info[l[p]]);
        ll distr = info[x].f(info[r[p]]);
        if (distl < ans && distr < ans) {
            if (distl < distr) {
                query(l[p], x);
                if (distr < ans) query(r[p], x);
            } else {
                query(r[p], x);
                if (distl < ans) query(l[p], x);
            }
        } else {
            if (distl < ans) query(l[p], x);
            if (distr < ans) query(r[p], x);
        }
    }
};
struct Info {
    static constexpr int DIM = 2;
    array<ll, DIM> x, L, R;
    ll distl, distr;
    ll f(const Info &i) {
        ll ret = 0;
        if (i.L[0] > x[0]) ret += (i.L[0] - x[0]) * (i.L[0] - x[0]);
        if (i.R[0] < x[0]) ret += (x[0] - i.R[0]) * (x[0] - i.R[0]);
        if (i.L[1] > x[1]) ret += (i.L[1] - x[1]) * (i.L[1] - x[1]);
        if (i.R[1] < x[1]) ret += (x[1] - i.R[1]) * (x[1] - i.R[1]);
        return ret;
    }
    void pull(const Info &l, const Info &r) {
        distl = f(l), distr = f(r);
    }
};