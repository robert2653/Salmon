template<class T> struct StaticKth : PST<int> {
    int dct(T x) { return lower_bound(s.begin(), s.end(), x) - s.begin(); }
    vector<T> a, s; // array, sorted
    StaticKth(const vector<T> &a, const vector<T> &s) : a(a), s(s), PST<int>(vector<int>(s.size())) {
        assert(is_sorted(s.begin(), s.end()));
        for (int i = 0; i < a.size(); i++) {
            createVersion(i);
            add(i + 1, dct(a[i]), 1);
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
template<class T>
struct DynamicKth : PST<int> {
    int dct(T x) { return lower_bound(s.begin(), s.end(), x) - s.begin(); }
    vector<T> a, s; // array, sorted
    DynamicKth(const vector<T> &a, const vector<T> &s) : a(a), s(s), PST<int>(vector<int>(s.size())) {
        assert(is_sorted(s.begin(), s.end()));
        rt.resize(a.size());
        for (int i = 0; i < a.size(); i++) add(i, dct(a[i]), 1);
    }
    int modify(int t, int l, int r, int x, int v) {
        t = t ? t : generate();
        if (r - l == 1) {
            nd[t].info += v;
            return t;
        }
        int m = (l + r) / 2;
        if (x < m) nd[t].lc = modify(nd[t].lc, l, m, x, v);
        else nd[t].rc = modify(nd[t].rc, m, r, x, v);
        pull(nd[t]);
        return t;
    }
    void add(int p, int x, int val) {
        for (int i = p + 1; i <= rt.size(); i += i & -i)
            rt[i - 1] = modify(rt[i - 1], 0, s.size(), x, val);
    }
    void modify(int p, int y) {
        add(p, dct(a[p]), -1);
        a[p] = y;
        add(p, dct(a[p]), 1);
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