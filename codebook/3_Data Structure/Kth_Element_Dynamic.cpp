template<class T> struct DynamicKth {
    vector<SegmentTreeDynamic<int>> rt; // Fenwick tree
    int dct(T x) { return lower_bound(s.begin(), s.end(), x) - s.begin(); }
    vector<T> a, s; // array, sorted
    DynamicKth(const vector<T> &a, const vector<T> &s) : a(a), s(s) {
        assert(is_sorted(s.begin(), s.end()));
        rt.assign(a.size(), SegmentTreeDynamic<int>(s.size()));
        for (int i = 0; i < a.size(); i++) add2(dct(a[i]), 1, i);
    }
    void add2(int x, int v, int p) {
        for (int i = p + 1; i <= a.size(); i += i & -i) {
            rt[i - 1].add(x, v);
        }
    }
    void modify(int p, int y) {
        add2(dct(a[p]), -1, p);
        a[p] = y;
        add2(dct(a[p]), 1, p);
    }
    int work(vector<pair<int, int>> &a, vector<pair<int, int>> &b, int l, int r, int k) {
        if (r - l == 1) return l;
        int m = (l + r) / 2, res = 0;
        for (auto [id, p] : a) res -= rt[id].nd[rt[id].nd[p].lc].info;
        for (auto [id, p] : b) res += rt[id].nd[rt[id].nd[p].lc].info;
        if (res >= k) {
            for (auto &[id, p] : a) p = rt[id].nd[p].lc;
            for (auto &[id, p] : b) p = rt[id].nd[p].lc;
            return work(a, b, l, m, k);
        } else {
            for (auto &[id, p] : a) p = rt[id].nd[p].rc;
            for (auto &[id, p] : b) p = rt[id].nd[p].rc;
            return work(a, b, m, r, k - res); 
        }
    }
    int work(int l, int r, int k) { // [l, r), k > 0
        vector<pair<int, int>> a, b;
        for (int i = l; i > 0; i -= i & -i) a.emplace_back(i - 1, rt[i - 1].rt);
        for (int i = r; i > 0; i -= i & -i) b.emplace_back(i - 1, rt[i - 1].rt);
        return s[work(a, b, 0, s.size(), k)];
    }
};