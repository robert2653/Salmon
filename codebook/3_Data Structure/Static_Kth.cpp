template<class T>
struct StaticKth : PST<int> {
    int dct(T x) {
        return lower_bound(s.begin(), s.end(), x) - s.begin();
    }
    vector<T> v, s; // array, sorted
    map<T, int> cnt;
    StaticKth(const vector<T> &v_) {
        s = v = v_;
        sort(s.begin(), s.end());
        s.resize(unique(s.begin(), s.end()) - s.begin());
        init(s.size());
        for (int i = 0; i < v.size(); i++) {
            createVersion(i);
            int d = dct(v[i]);
            modify(i + 1, d, ++cnt[d]);
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