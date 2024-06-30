template <class Info>
struct Seg {    // 左開右閉寫法
    int n;
    vector<Info> info;
    Seg(int n_, Info v_ = Info()) {
        init(n_, v_);
    }
    template <class T>
    Seg(vector<T> init_) {
        init(init_);
    }
    void init(int n_, Info v_ = Info()) {
        init(vector(n_, v_));
    }
    template <class T>
    void init(vector<T> init_) {
        n = init_.size();
        info.assign(4 << __lg(n), Info());
        function <void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init_[l];
                return;
            }
            int m = (l + r) / 2;
            build(p * 2, l, m);
            build(p * 2 + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }
    void pull(int p) { info[p] = info[p * 2] + info[p * 2 + 1]; }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info &i) {
        modify(1, 0, n, p, i);
    }
    Info query(int p, int l, int r, int ql, int qr) {
        if (qr <= l || ql >= r) return Info();
        if (ql <= l && r <= qr) return info[p];
        int m = (l + r) / 2;
	    return query(p * 2, l, m, ql, qr) + query(p * 2 + 1, m, r, ql, qr);
    }
    Info query(int ql, int qr) { return query(1, 0, n, ql, qr); }
    template<class F>   // 尋找區間內，第一個符合條件的
    int findFirst(int p, int l, int r, int x, int y, F &&pred) {
        if (l >= y || r <= x) {
            return -1;
        }
        if (l >= x && r <= y && !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int res = findFirst(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = findFirst(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }
    template<class F>   // 若要找 last，先右子樹遞迴即可
    int findFirst(int l, int r, F &&pred) {
        return findFirst(1, 0, n, l, r, pred);
    }
};
// ---define structure and info plus---
struct Info {
    int sum;
};
Info operator + (const Info &a, const Info &b) {
    return { a.sum + b.sum };
}
// ---pizza_queries---
// 左邊的店(s < t): dis_l = (pizza[s] - s) + t;
// 右邊的店(t < s): dis_r = (pizza[s] + s) - t;
// 實作: 建左查詢線段樹跟右查詢線段樹，用最小值pull
// 答案是 min(left_query(1, s) + t, right_query(s, end) + t);
// ---List Removals---
// 維護區間內有幾個數字被選過
// 用二分搜找右區間最小位，使得 ans - query == 1 ~ ans 被選過的數量
// ---CSES subarray queries:---
// tree[now].prefix = max(tree[lc].sum + tree[rc].prefix, tree[lc].prefix);
// tree[now].suffix = max(tree[lc].suffix+tree[rc].sum, tree[rc].suffix);
// tree[now].middle_max = max(lc 中, rc 中, lc 後 + rc 前, now 前, now 後)