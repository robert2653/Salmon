template<class T> struct ZKW {
    int n;
    vector<T> a;
    ZKW(int n) : n(n), a(2 * n) {}
    ZKW(const vector<T> &v) : n(v.size()), a(2 * n) {
        for (int i = 0; i < n; i++) a[i + n] = v[i];
        for (int i = n - 1; i > 0; i--) a[i] = a[2 * i] + a[2 * i + 1];
    }
    void modify(int x, const T &i) {
        a[x += n] = i;
        for (x /= 2; x; x /= 2) a[x] = a[2 * x] + a[2 * x + 1];
    }
    T query(int l, int r) {
        T x{}, y{};
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l & 1) x = x + a[l++];
            if (r & 1) y = a[--r] + y;
        }
        return x + y;
    }
};
struct Info {};
Info operator+(const Info &a, const Info &b) {
    Info c;
    return c;
}