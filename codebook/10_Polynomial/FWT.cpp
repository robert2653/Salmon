void fwt(vector<ll> &a, bool inv = false) {
    // Or : [[1, 0], [1, 1]] -> [[1, 0], [-1, 1]]
    // And: [[1, 1], [0, 1]] -> [[1, -1], [0, 1]]
    // Xor: [[1, 1], [1, -1]] -> [[0.5, 0.5], [0.5, -0.5]]
    int n = __lg(int(a.size()));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 1 << n; ++j) {
            if (j >> i & 1) { // And
                ll x = a[j ^ (1 << i)];
                ll y = a[j];
                if (!inv) {
                    a[j ^ (1 << i)] = x + y;
                    a[j] = y;
                } else {
                    a[j ^ (1 << i)] = x - y;
                    a[j] = y;
                }
            }
        }
    }
}