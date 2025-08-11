// Fenwick(rt-indexed) 包線段樹
template<class T>
struct DynamicKth : PST<int> {
    int dct(T x) {
        return lower_bound(s.begin(), s.end(), x) - s.begin();
    }
    vector<T> v, s; // array, sorted
    DynamicKth(const vector<T> &v_, const vector<T> &s_) 
        : PST<int>(vector<int>(s_.size(), 0)) {
        assert(is_sorted(s_.begin(), s_.end()));
        v = v_, s = s_;
        rt.resize(v.size());
        for (int i = 0; i < v.size(); i++) add(i, dct(v[i]), 1);
    }
    int modify(int t, int l, int r, int x, int v) {
        t = t ? t : generate();
        if (r - l == 1) {
            nd[t].info += v;
            return t;
        }
        int m = (l + r) / 2;
        if (x < m) {
            nd[t].lc = modify(nd[t].lc, l, m, x, v);
        } else {
            nd[t].rc = modify(nd[t].rc, m, r, x, v);
        }
        pull(nd[t]);
        return t;
    }
    void add(int p, int x, int val) {
        for (int i = p + 1; i <= rt.size(); i += i & -i)
            rt[i - 1] = modify(rt[i - 1], 0, s.size(), x, val);
    }
    void modify(int p, int y) {
        add(p, dct(v[p]), -1);
        v[p] = y;
        add(p, dct(v[p]), 1);
    }
    int work(vector<int> &a, vector<int> &b, int l, int r, int k) {
        if (r - l == 1) return l;
        int m = (l + r) / 2;
        int res = 0;
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
        for (int i = l; i > 0; i -= i & -i)
            a.push_back(rt[i - 1]);
        for (int i = r; i > 0; i -= i & -i)
            b.push_back(rt[i - 1]);
        return s[work(a, b, 0, s.size(), k)];
    }
};