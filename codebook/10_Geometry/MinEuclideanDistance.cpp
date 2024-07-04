template<class T>
T distanceSquare(const Point<T> &a, const Point<T> &b) {
    return square(a - b);
}
int main() {
    int n; cin >> n;
    constexpr i64 inf = 8e18;
    vector<Point<i64>> a(n);
    for (int i = 0; i < n; i++) cin >> a[i]l
    struct sortY {
        bool operator()(const Point<i64> &a, const Point<i64> &b) const {
            return a.y < b.y;
        }
    };
    struct sortXY {
        bool operator()(const Point<i64> &a, const Point<i64> &b) const {
            return a.x == b.x ? a.y < b.y : a.x < b.x;
        }
    };
    sort(a.begin(), a.end(), sortXY());
    i64 ans = inf;
    vector<Point<i64>> t(n);
    auto devide = [&](auto &&self, int l, int r) -> void {
        if (r - l <= 3) {
            for (int i = l; i <= r; ++i)
                for (int j = i + 1; j <= r; ++j) {
                    ans = min(ans, distanceSquare(a[i], a[j]));
                }
            sort(a.begin() + l, a.begin() + r + 1, sortY());
            return;
        }
        int m = (l + r) >> 1;
        int midx = a[m].x;
        self(self, l, m), self(self, m + 1, r);
        inplace_merge(a.begin() + l, a.begin() + m + 1, a.begin() + r + 1, sortY());
        int tsz = 0;
        for (int i = l; i <= r; ++i) {
            if (abs(a[i].x - midx) < ans) {
                for (int j = tsz - 1; j >= 0 && a[i].y - t[j].y < ans; j--) {
                    ans = min(ans, distanceSquare(a[i], t[j]));
                }
                t[tsz++] = a[i];
            }
        }
    };
    devide(devide, 0, n - 1);
    cout << ans << "\n";
}