template<class T>
pair<double, vector<Point<double>>> minRectangleCover(vector<Point<T>> p) {
    if (p.size() <= 2) return {0, {}};
    auto get = [&](const Point<T> &p, const Line<T> &l) -> T {
        return abs(cross(l.a - l.b, l.a - p));
    }; // line 到 p 圍成的四邊形面積
    int n = p.size(), j = 2, l = 1, r = 1;
    p.push_back(p.front());
    double ans = 8E18;
    vector<Point<double>> ps;
    for (int i = 0; i < n; i++) {
        while (get(p[j], Line(p[i], p[i + 1])) <= get(p[(j + 1) % n], Line(p[i], p[i + 1])))
            j = (j + 1) % n;
        while (dot(p[i + 1] - p[i], p[r] - p[i]) <= dot(p[i + 1] - p[i], p[(r + 1) % n] - p[i]))
            r = (r + 1) % n;
        if (i == 0) l = j;
        while (dot(p[i + 1] - p[i], p[l] - p[i]) >= dot(p[i + 1] - p[i], p[(l + 1) % n] - p[i]))
            l = (l + 1) % n;
        double area = get(p[j], Line(p[i], p[i + 1]));
        double w = dot(p[i] - p[i + 1], p[l] - p[i]) + dot(p[i + 1] - p[i], p[r] - p[i]);
        area *= w / square(p[i + 1] - p[i]);
        if (area < ans) {
            ps.clear(), ans = area;
            Line l1(p[i], p[i + 1]);
            for (auto u : {p[r], p[j], p[l], p[i]}) {
                if (u == l1.b) {
                    ps.push_back(u);
                    l1 = Line(u, u + rotate(l1.b - l1.a));
                } else {
                    Line l2 = Line(u, u + rotate(l1.b - l1.a));
                    Point<T> res = lineIntersection(l1, l2);
                    ps.push_back(res);
                    l1 = Line(res, u);
                }
            }
        }
    }
    return {ans, ps};
}