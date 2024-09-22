template<class T>
struct Matrix {
    int n, m;
    vector<vector<T>> mat;
    constexpr Matrix(int n_, int m_) { init(n_, m_); }
    constexpr Matrix(vector<vector<T>> mat_) { init(mat_); }
    constexpr void init(int n_, int m_) {
        n = n_; m = m_;
        mat.assign(n, vector<T>(m));
    }
    constexpr void init(vector<vector<T>> mat_) {
        n = mat_.size();
        m = mat_[0].size();
        mat = mat_;
    }
    constexpr Matrix &operator*=(const Matrix &rhs) & {
        assert(mat[0].size() == rhs.mat.size());
        int n = mat.size(), k = mat[0].size(), m = rhs.mat[0].size();
        Matrix res(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                for (int l = 0; l < k; l++)
                    res.mat[i][j] += mat[i][l] * rhs.mat[l][j];
        mat = res.mat;
        return *this;
    }
    friend constexpr Matrix operator*(Matrix lhs, const Matrix &rhs) {
        return lhs *= rhs;
    }
};
template<class T>
constexpr Matrix<T> unit(int n) {
    Matrix<T> res(n, n);
    for (int i = 0; i < n; i++)
        res.mat[i][i] = 1;
    return res;
}
template<class T>
constexpr Matrix<T> power(Matrix<T> a, ll b) {
    assert(a.n == a.m);
    Matrix<T> res = unit<T>(a.n);
    for (; b; b /= 2, a *= a)
        if (b % 2) res *= a;
    return res;
}