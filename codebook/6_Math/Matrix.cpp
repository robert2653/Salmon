using Matrix = vector<vector<Z>>;
Matrix operator*(const Matrix &a, const Matrix &b) {
    int n = a.size(), k = a[0].size(), m = b[0].size();
    assert(k == b.size());
    Matrix res(n, vector<Z>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int l = 0; l < k; l++)
                res[i][j] += a[i][l] * b[l][j];
    return res;
}
Matrix power(Matrix a, ll b) {
    int n = a.size();
    Matrix res(n, vector<Z>(n));
    for (int i = 0; i < n; i++) res[i][i] = 1;
    for (; b > 0; b >>= 1, a = a * a)
        if (b & 1) res = res * a;
    return res;
}