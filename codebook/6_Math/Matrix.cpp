template<class T> struct Mat {
    int n = 0, m = 0; // n == 0: identity of any size
    vector<vector<T>> a;
    Mat(int) {} // for power's T res{1}
    Mat(int n, int m) : n(n), m(m), a(n, vector<T>(m)) {}
    Mat(const vector<vector<T>> &a) : n(a.size()), m(a[0].size()), a(a) {}
    Mat operator*(const Mat &b) const {
        if (!n) return b;
        if (!b.n) return *this;
        assert(m == b.n);
        Mat res(n, b.m);
        for (int i = 0; i < n; i++)
            for (int l = 0; l < m; l++)
                for (int j = 0; j < b.m; j++)
                    res.a[i][j] += a[i][l] * b.a[l][j];
        return res;
    }
    Mat &operator*=(const Mat &b) { return *this = *this * b; }
};