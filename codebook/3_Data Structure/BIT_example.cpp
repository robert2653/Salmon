#include <bits/stdc++.h>
using namespace std;
template<class T>
struct BIT {    // 全部以 0 based 使用
    int n;
    vector<T> bit;
    BIT(int n = 0) {    // 有幾個數
        init(vector<T>(n));
    }
    BIT(vector<T> init_) { // 必須是 0-based
        init(init_);
    }
    void init(int n_ = 0) {
        init(vector<T>(n_));
    }
    void init(vector<T> init_) { // 必須是 0-based
        n = init_.size();
        bit.assign(n + 1, T());
        for (int i = 0; i < n; i++) {
            modify(i, init_[i]);
        }
    }
    void modify(int i, T val) {
        for (i++; i <= n; i += i & -i) {
            bit[i] += val;
        }
    }
    T query(int r) {
	    T ans = 0;
	    for (r++; r; r -= r & -r) ans += bit[r];
	    return ans;
    }
    T query(int l, int r) {
        return query(r) - query(l - 1);
    }
};
template <class T>
struct TwoDimensionBIT {
    int nx, ny;
    vector<vector<T>> bit;
    TwoDimensionBIT(int x = 0, int y = 0) {
        init(vector<vector<T>>(x + 1, vector<T>(y + 1)));
    }
    TwoDimensionBIT(vector<vector<T>> init_) { // 必須是 0-based
        init(init_);
    }
    void init(int x = 0, int y = 0) {
        init(vector<vector<T>>(x + 1, vector<T>(y + 1)));
    }
    void init(vector<vector<T>> init_) { // 必須是 0-based
        nx = init_.size();
        ny = init_[0].size();
        bit.assign(nx + 1, vector<T>(ny + 1, T()));
        for (int i = 0; i < nx; i++) {
            for (int j = 0; j < ny; j++) {
                modify(i, j, init_[i][j]);
            }
        }
    }
    void modify(int x, int y, T mod) {
        for (x++; x <= nx; x += x & -x) {
            for (int tmp = y + 1; tmp <= ny; tmp += tmp & -tmp) {
                bit[x][tmp] += mod;
            }
        }
    }
    T query(int rx, int ry) {
        T ans = 0;
        for (rx++; rx; rx -= rx & -rx) {
            for (int tmp = ry + 1; tmp; tmp -= tmp & -tmp) {
                ans += bit[rx][tmp];
            }
        }
        return ans;
    }
    T query(int lx, int ly, int rx, int ry) {
        T ans = 0;
        return query(rx, ry) - query(lx - 1, ry) - query(rx, ly - 1) + query(lx - 1, ly - 1);
    }
};
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> g[i][j];
        }
    }
    TwoDimensionBIT<int> bit;
    bit.init(g);
    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        int lx, ly, rx, ry;
        cin >> lx >> ly >> rx >> ry;
        cout << bit.query(lx, ly, rx, ry) << "\n";
    }
    return 0;
}