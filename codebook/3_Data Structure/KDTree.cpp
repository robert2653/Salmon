struct Info {
    static constexpr int DIM = 2;
    array<int, DIM> x, L, R;
    int v = 0, sum = 0;
    void pull(const Info &l, const Info &r) {
        sum = v + l.sum + r.sum;
    }
};
struct KDTree {
    static constexpr int DIM = Info::DIM;
    vector<Info> info;
    vector<int> rt, l, r, p;
    KDTree(int n) : n(n), lg(__lg(n)), info(1), rt(lg + 1), l(n + 1), r(n + 1) {}
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
    int rebuild(int l, int r, int dep = 0) {
        if (r == l) return 0;
        int m = (l + r) / 2;
        nth_element(p.begin() + l, p.begin() + m, p.begin() + r,
            [&](int x, int y) { return info[x].x[dep] < info[y].x[dep]; });
        int x = p[m];
        this->l[x] = rebuild(l, m, (dep + 1) % DIM);
        this->r[x] = rebuild(m + 1, r, (dep + 1) % DIM);
        pull(x);
        return x;
    }
    void append(int &x) {
        if (!x) return;
        p.push_back(x);
        append(l[x]);
        append(r[x]);
        x = 0;
    }
    void addNode(const Info &i) {
        p.assign(1, info.size());
        info.push_back(i);
        for (int j = 0;; j++) {
            if (!rt[j]) {
                rt[j] = rebuild(0, p.size());
                break;
            } else {
                append(rt[j]);
            }
        }
    }
    Info query(int p, const array<int, DIM> &l, const array<int, DIM> &r) {
        if (!p) return Info();
        bool inside = true;
        for (int k = 0; k < DIM; k++) {
            inside &= (l[k] <= info[p].L[k] && info[p].R[k] <= r[k]);
        }
        if (inside) return info[p];
        for (int k = 0; k < DIM; k++) {
            if (info[p].R[k] < l[k] || r[k] < info[p].L[k]) {
                return Info();
            }
        }
        Info ans;
        inside = true;
        for (int k = 0; k < DIM; k++) {
            inside &= l[k] <= info[p].x[k] && info[p].x[k] <= r[k];
        }
        if (inside) ans = info[p];
        ans.pull(query(this->l[p], l, r), query(this->r[p], l, r));
        return ans;
    }
    Info query(const array<int, DIM> &l, const array<int, DIM> &r) {
        Info res;
        for (int i = 0; i <= lg; i++) {
            res.pull(res, query(rt[i], l, r));
        }
        return res;
    }
};