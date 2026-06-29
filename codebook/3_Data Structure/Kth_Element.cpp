template<class T> struct StaticKth : PST<int> {
    int dct(T x) { return lower_bound(s.begin(), s.end(), x) - s.begin(); }
    vector<T> a, s; // array, sorted
    StaticKth(const vector<T> &a, const vector<T> &s) : a(a), s(s), PST<int>(vector<int>(s.size())) {
        assert(is_sorted(s.begin(), s.end()));
        for (int i = 0; i < a.size(); i++) {
            createVersion(i);
            add(dct(a[i]), 1, i + 1);
        }
    }
    int work(int a, int b, int l, int r, int k) {
        if (r - l == 1) return l;
        int x = nd[nd[b].lc].info - nd[nd[a].lc].info;
        int m = (l + r) / 2;
        if (x >= k) {
            return work(nd[a].lc, nd[b].lc, l, m, k);
        } else {
            return work(nd[a].rc, nd[b].rc, m, r, k - x);
        }
    }
    int work(int l, int r, int k) { // [l, r), k > 0
        return s[work(rt[l], rt[r], 0, n, k)];
    }
};
// Fenwick(rt-indexed) 包線段樹
template<class T> struct DynamicKth : PST<int> {
    int dct(T x) { return lower_bound(s.begin(), s.end(), x) - s.begin(); }
    vector<T> a, s; // array, sorted
    DynamicKth(const vector<T> &a, const vector<T> &s) : a(a), s(s), PST<int>(vector<int>(s.size())) {
        assert(is_sorted(s.begin(), s.end()));
        rt.resize(a.size());
        for (int i = 0; i < a.size(); i++) add(dct(a[i]), 1, i);
    }
    int modify(int x, int v, int l, int r, int t) {
        t = t ? t : generate();
        if (r - l == 1) {
            nd[t].info += v;
            return t;
        }
        int m = (l + r) / 2;
        if (x < m) nd[t].lc = modify(x, v, l, m, nd[t].lc);
        else nd[t].rc = modify(x, v, m, r, nd[t].rc);
        pull(nd[t]);
        return t;
    }
    void add(int x, int v, int p) {
        for (int i = p + 1; i <= rt.size(); i += i & -i)
            rt[i - 1] = modify(x, v, 0, s.size(), rt[i - 1]);
    }
    void modify(int p, int y) {
        add(dct(a[p]), -1, p);
        a[p] = y;
        add(dct(a[p]), 1, p);
    }
    int work(vector<int> &a, vector<int> &b, int l, int r, int k) {
        if (r - l == 1) return l;
        int m = (l + r) / 2, res = 0;
        for (auto x : a) res -= nd[nd[x].lc].info;
        for (auto x : b) res += nd[nd[x].lc].info;
        if (res >= k) {
            for (auto &x : a) x = nd[x].lc; 
            for (auto &x : b) x = nd[x].lc;
            return work(a, b, l, m, k); 
        } else {
            for (auto &x : a) x = nd[x].rc; 
            for (auto &x : b) x = nd[x].rc;
            return work(a, b, m, r, k - res); 
        }
    }
    int work(int l, int r, int k) { // [l, r), k > 0
        vector<int> a, b;
        for (int i = l; i > 0; i -= i & -i) a.push_back(rt[i - 1]);
        for (int i = r; i > 0; i -= i & -i) b.push_back(rt[i - 1]);
        return s[work(a, b, 0, s.size(), k)];
    }
};