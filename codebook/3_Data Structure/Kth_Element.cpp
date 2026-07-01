template<class T> struct StaticKth : PST<int> {
    int dct(T x) { return lower_bound(s.begin(), s.end(), x) - s.begin(); }
    vector<T> a, s; // array, sorted
    StaticKth(const vector<T> &a, const vector<T> &s) : a(a), s(s), PST<int>(s.size()) {
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
        if (x >= k) return work(nd[a].lc, nd[b].lc, l, m, k);
        else return work(nd[a].rc, nd[b].rc, m, r, k - x);
    }
    int work(int l, int r, int k) { // [l, r), k > 0
        return s[work(rt[l], rt[r], 0, n, k)];
    }
}; // Dynamic -> Fenwick 包動態開點值域線段樹