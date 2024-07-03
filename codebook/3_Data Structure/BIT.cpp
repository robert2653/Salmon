template<class T>
struct BIT {    // BIT 都是 1-based 的查詢
    int n;
    vector<T> bit;
    BIT(int n = 0) {    // 有幾個數
        init(vector<T>(n));
    }
    BIT(vector<T> init_) { // 必須是 0-based
        init(init_);
    }
    void init(vector<T> init_) { // 必須是 0-based
        n = init_.size();
        bit.assign(n + 1, T());
        for (int i = 1; i <= n; i++) {
            modify(i, init_[i - 1]);
        }
    }
    void modify(int i, T val) {
        for (; i <= n; i += i & -i) {
            bit[i] += val;
        }
    }
    T query(int r) {
	    T ans = 0;
	    for (; r; r -= r & -r) ans += bit[r];
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
    void init(vector<vector<T>> init_) { // 必須是 0-based
        nx = init_.size();
        ny = init_[0].size();
        bit.assign(nx + 1, vector<T>(ny + 1, T()));
        for (int i = 1; i <= nx; i++) {
            for (int j = 1; j <= ny; j++) {
                modify(i, j, init_[i - 1][j - 1]);
            }
        }
    }
    void modify(int x, int y, T mod) {
        for (; x <= nx; x += x & -x) {
            for (int tmp = y; tmp <= ny; tmp += tmp & -tmp) {
                bit[x][tmp] += mod;
            }
        }
    }
    T query(int rx, int ry) {
        T ans = 0;
        for (; rx; rx -= rx & -rx) {
            for (int tmp = ry; tmp; tmp -= tmp & -tmp) {
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