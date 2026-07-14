template<class T> struct RangeFenwick {
    int n;
    vector<T> d, di;
    RangeFenwick(int n) : n(n), d(n), di(n) {}
    void add(int x, const T &v) {
        T vi = v * (x + 1);
        for (int i = x + 1; i <= n; i += i & -i)
            d[i - 1] = d[i - 1] + v, di[i - 1] = di[i - 1] + vi;
    }
    void rangeAdd(int l, int r, const T &v) { add(l, v), add(r, -v); }
    T sum(int x) {
        T ans {};
        for (int i = x; i > 0; i -= i & -i)
            ans = ans + T(x + 1) * d[i - 1] - di[i - 1];
        return ans;
    }
    T rangeSum(int l, int r) { return sum(r) - sum(l); }
    int select(const T &k, int start = 0) {
        int x = 0;
        T cur {}, curi {}, sub = sum(start);
        for (int i = 1 << __lg(n); i; i /= 2) {
            if (x + i <= n && T(x + i + 1) * (cur + d[x + i - 1]) - (curi + di[x + i - 1]) - sub <= k) {
                x += i;
                cur = cur + d[x - 1], curi = curi + di[x - 1];
            }
        }
        return x;
    }
};
template<class T> struct RangeFenwick2D {
    int n, m;
    vector<vector<T>> d, di, dj, dij;
    RangeFenwick2D(int n, int m) : n(n), m(m), dij(n, vector<T>(m))
    { d = di = dj = dij; }
    void add(int x, int y, const T &v) {
        T vi = v * (x + 1), vj = v * (y + 1);
        T vij = v * (x + 1) * (y + 1);
        for (int i = x + 1; i <= n; i += i & -i)
            for (int j = y + 1; j <= m; j += j & -j) {
                d[i - 1][j - 1] = d[i - 1][j - 1] + v;
                di[i - 1][j - 1] = di[i - 1][j - 1] + vi;
                dj[i - 1][j - 1] = dj[i - 1][j - 1] + vj;
                dij[i - 1][j - 1] = dij[i - 1][j - 1] + vij;
            }
    }
    void rangeAdd(int x1, int y1, int x2, int y2, const T &v) {
        add(x1, y1, v), add(x2, y2, v);
        add(x1, y2, -v), add(x2, y1, -v);
    }
    T sum(int x, int y) {
        T ans {};
        for (int i = x; i > 0; i -= i & -i)
            for (int j = y; j > 0; j -= j & -j)
                ans = ans + (x + 1) * (y + 1) * d[i - 1][j - 1]
                - (y + 1) * di[i - 1][j - 1]
                - (x + 1) * dj[i - 1][j - 1]
                + dij[i - 1][j - 1];
        return ans;
    }
    T rangeSum(int x1, int y1, int x2, int y2)
    { return sum(x2, y2) - sum(x1, y2) - sum(x2, y1) + sum(x1, y1); }
};