template<class T>
double polygonUnion(vector<vector<Point<T>>> ps) {
    int n = ps.size();
    for (auto &v : ps) v.push_back(v[0]);
    double res = 0;
    auto seg = [&](const Point<T> &o, const Point<T> &a, const Point<T> &b) -> double {
        if (b.x - a.x == 0) return double((o.y - a.y) / (b.y - a.y));
        return double((o.x - a.x) / (b.x - a.x));
    };
    for (int pi = 0; pi < n; pi++) {
        for (int i = 0; i + 1 < ps[pi].size(); i++) {
            vector<pair<double, int>> e;
            e.emplace_back(0, 0);
            e.emplace_back(1, 0);
            for (int pj = 0; pj < n; pj++) {
                if (pi == pj) continue;
                for (int j = 0; j + 1 < ps[pj].size(); j++) {
                    T c1 = cross(ps[pi][i + 1] - ps[pi][i], ps[pj][j] - ps[pi][i]);
                    T c2 = cross(ps[pi][i + 1] - ps[pi][i], ps[pj][j + 1] - ps[pi][i]);
                    if (c1 == 0 && c2 == 0) {
                        if (dot(ps[pi][i + 1] - ps[pi][i], ps[pj][j + 1] - ps[pj][j]) > 0 && pi > pj) {
                            e.emplace_back(seg(ps[pj][j], ps[pi][i], ps[pi][i + 1]), 1);
                            e.emplace_back(seg(ps[pj][j + 1], ps[pi][i], ps[pi][i + 1]), -1);
                        }
                    } else {
                        T s1 = cross(ps[pj][j + 1] - ps[pj][j], ps[pi][i] - ps[pj][j]);
                        T s2 = cross(ps[pj][j + 1] - ps[pj][j], ps[pi][i + 1] - ps[pj][j]);
                        if (c1 >= 0 && c2 < 0) e.emplace_back(s1 / (s1 - s2), 1);   
                        else if (c1 < 0 && c2 >= 0) e.emplace_back(s1 / (s1 - s2), -1);   
                    }
                }
            }
            sort(e.begin(), e.end());
            double pre = clamp(e[0].first, 0.0, 1.0), sum = 0;
            int cov = e[0].second;
            for (int j = 1; j < e.size(); j++) {
                double now = clamp(e[j].first, 0.0, 1.0);
                if (!cov) sum += now - pre;
                cov += e[j].second;
                pre = now;
            }
            res += double(cross(ps[pi][i], ps[pi][i + 1])) * sum;
        }
    }
    return res / 2;
}