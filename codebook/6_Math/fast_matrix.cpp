struct Mat {
    int m, n;
    vector<vector<ll>> matrix;
    void init(int m, int n) {
        this->m = m; this->n = n;
        matrix.resize(m);
        for (int i = 0; i < m; i++) {
            matrix[i].resize(n);
        }
    }
    Mat(int m, int n) { init(m, n); }
    Mat(int n) { init(n, n); }
    Mat(vector<vector<ll>> matrix) {
        this->m = matrix.size();
        this->n = matrix[0].size();
        this->matrix = matrix;
    }
    Mat unit(int n) {   // 單位矩陣
        Mat res(n);
        for (int i = 0; i < n; i++) {
            res.matrix[i][i] = 1;
        }
        return res;
    }
    Mat operator * (Mat b) {
        int m = matrix.size(), n = b.matrix[1].size(), k = matrix[0].size();
        Mat ans(m, n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    (ans.matrix[i][j] += (matrix[i][k] * b.matrix[k][j] % mod)) %= mod;
                }
            }
        }
        return ans;
    }
    Mat operator *= (Mat b) { *this = *this * b; return *this; }
    Mat operator ^ (ll p) {
        if (p == 0) return unit(n);
        Mat ans = *this; p--;
        while (p > 0) {
            if (p & 1) {
                ans *= *this;
            }
            *this *= *this;
            p >>= 1;
        }
        return ans;
    }
    Mat operator ^= (ll p) { *this = *this ^ p; return *this; }
};
signed main() {
    int n; cin >> n; ll ans;
    if (n <= 4) {
        vector<int> v = {0, 1, 1, 2, 4};
        ans = v[n];
    }
    else {
        Mat init({{4, 2, 1}, {2, 1, 1}, {1, 1, 0}});
        Mat T(3);
        T.matrix = {{1, 1, 0}, {1, 0, 1}, {1, 0, 0}};
        T ^= n - 4;
        init *= T;
        ans = init.matrix[0][0];
    }
    cout << ans << "\n";
}
// 初始矩陣   轉移式
// f4 f3 f2   1 1 0    f5 f4 f3
// f3 f2 f1   1 0 1 => f4 f3 f2
// f2 f1 f0   1 0 0    f3 f2 f1