int main() {
    // Polygun 內整數點數
    int n; cin >> n;
    vector<Point<i64>> polygon(n);
    for (int i = 0; i < n; i++) cin >> polygon[i];
    i64 area = 0;
    for (int i = 0; i < n; i++) {
        area += cross(polygon[i], polygon[(i + 1) % n]);
    }
    area = abs(area);
    auto countBoundaryPoints = [](const vector<Point<i64>>& polygon) -> i64 {
        i64 res = 0;
        int n = polygon.size();
        for (int i = 0; i < n; i++) {
            i64 dx = polygon[(i + 1) % n].x - polygon[i].x;
            i64 dy = polygon[(i + 1) % n].y - polygon[i].y;
            res += std::gcd(abs(dx), abs(dy));
        }
        return res;
    };
    i64 res = countBoundaryPoints(polygon);
    i64 ans = (area - res + 2) / 2;
    cout << ans << " " << res << "\n";
}