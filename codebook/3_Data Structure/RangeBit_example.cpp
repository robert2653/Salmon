#include <bits/stdc++.h>
using namespace std;
template<class T>
struct rangeFenwick { // 全部以 0 based 使用
    int n;
    vector<T> a, b; // (𝑥+1)*(∑_𝑖=1^𝑥𝐷𝑖)−(∑_𝑖=1^𝑥𝐷𝑖*𝑖)
    rangeFenwick(int n_ = 0) {
        init(n_);
    }
    void init(int n_) {
        n = n_;
        a.assign(n, T{});
        b.assign(n, T{});
    }
    void add(int x, const T &v) {
        T vi = v * (x + 1);
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] = a[i - 1] + v;
            b[i - 1] = b[i - 1] + vi;
        }
    }
    void rangeAdd(int l, int r, const T &v) {
        add(l, v); add(r, -v);
    }
    T sum(int x) { // 左閉右開查詢
        T ans{};
        for (int i = x; i > 0; i -= i & -i) {
            ans = ans + T(x + 1) * a[i - 1];
            ans = ans - b[i - 1];
        }
        return ans;
    }
    T rangeSum(int l, int r) { // 左閉右開查詢
        return sum(r) - sum(l);
    }
    int select(const T &k) { // 找到最小的 x, 使得 sum(x) > k
        int x = 0;
        T cur{};
        for (int i = 1 << __lg(n); i; i /= 2) {
            if (x + i <= n) {
                T val = T(x + i + 1) * a[x + i - 1] - b[x + i - 1];
                if (cur + val <= k) {
                    x += i;
                    cur = cur + val;
                }
            }
        }
        return x;
    }
};

template<class T>
struct rangeTwoDFenwick {  // 全部以 0 based 使用
    // d(i,j) = a(i,j) - a(i-1,j) - a(i,j-1) + a(i-1,j-1)
    int nx, ny;  // row, col 個數
    vector<vector<T>> d, di, dj, dij;
    rangeTwoDFenwick(int nx_ = 0, int ny_ = 0) {
        init(nx_, ny_);
    }
    void init(int nx_, int ny_) {
        nx = nx_; ny = ny_;
        d.assign(nx, vector<T>(ny, T{}));
        di.assign(nx, vector<T>(ny, T{}));
        dj.assign(nx, vector<T>(ny, T{}));
        dij.assign(nx, vector<T>(ny, T{}));
    }
    void add(int x, int y, const T &v) {
        T vi = v * (x + 1);
        T vj = v * (y + 1);
        T vij = v * (x + 1) * (y + 1);
        for (int i = x + 1; i <= nx; i += i & -i) {
            for (int j = y + 1; j <= ny; j += j & -j) {
                d[i - 1][j - 1] = d[i - 1][j - 1] + v;
                di[i - 1][j - 1] = di[i - 1][j - 1] + vi;
                dj[i - 1][j - 1] = dj[i - 1][j - 1] + vj;
                dij[i - 1][j - 1] = dij[i - 1][j - 1] + vij;
            }
        }
    }
    void rangeAdd(int lx, int ly, int rx, int ry, const T &v) {
        add(rx, ry, v);
        add(lx, ry, -v);
        add(rx, ly, -v);
        add(lx, ly, v);
    }
    T sum(int x, int y) { // 左閉右開查詢
        T ans{};
        for (int i = x; i > 0; i -= i & -i) {
            for (int j = y; j > 0; j -= j & -j) {
                ans = ans + T(x * y + x + y + 1) * d[i - 1][j - 1];
                ans = ans - T(y + 1) * di[i - 1][j - 1];
                ans = ans - T(x + 1) * dj[i - 1][j - 1];
                ans = ans + dij[i - 1][j - 1];
            }
        }
        return ans;
    }
    T rangeSum(int lx, int ly, int rx, int ry) { // 左閉右開查詢
        return sum(rx, ry) - sum(lx, ry) - sum(rx, ly) + sum(lx, ly);
    }
};

int main() {
    // int n, q;
    // cin >> n >> q;
    // rangeFenwick<int> bit(n);
    // for (int i = 0; i < n; i++) {
    //     int x; cin >> x;
    //     bit.rangeAdd(i, i + 1, x);
    // }
    // for (int i = 0; i < q; i++) {
    //     int op;
    //     cin >> op;
    //     if (op == 1) {
    //         // range add;
    //         int l, r; cin >> l >> r;
    //         int add; cin >> add;
    //         bit.rangeAdd(l, r, add);
    //     } else if (op == 2) {
    //         int l, r; cin >> l >> r;
    //         cout << bit.rangeSum(l, r) << "\n";
    //     } else {
    //         int val; cin >> val;
    //         cout << bit.select(val) << "\n";
    //     }
    // }

    int n, m, q;
    cin >> n >> m >> q;
    rangeTwoDFenwick<int> bit(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x; cin >> x;
            bit.rangeAdd(i, j, i + 1, j + 1, x);
        }
    }
    for (int i = 0; i < q; i++) {
        int op; cin >> op;
        int lx, ly, rx, ry;
        cin >> lx >> ly >> rx >> ry;
        if (op == 1) {
            int x; cin >> x;
            bit.rangeAdd(lx, ly, rx + 1, ry + 1, x);
        } else {
            cout << bit.rangeSum(lx, ly, rx + 1, ry + 1) << "\n";
        }
    }
}