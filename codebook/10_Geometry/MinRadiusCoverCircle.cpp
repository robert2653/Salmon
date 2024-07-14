constexpr double Eps = 1e-7;
void solve(int n, vector<P> a, double maxR) {
    auto cal = [&](P center) {
        double mx = 0;
        for (auto& p : a)
            mx = max(mx, distance(center, p));
        return mx;
    };
    auto searchY = [&](double x) {
        double l = -maxR, r = maxR;
        while (r - l > Eps) {
            double d = (r - l) / 3;
            double ml = l + d, mr = r - d;
            double ansl = cal({x, ml}), ansr = cal({x, mr});
            if (ansl > ansr) l = ml;
            else r = mr;
        }
        return (l + r) / 2;
    };
    double l = -maxR, r = maxR;
    while (r - l > Eps) {
        double d = (r - l) / 3;
        double ml = l + d, mr = r - d;
        double yl = searchY(ml), yr = searchY(mr);
        double ansl = cal({ml, yl}), ansr = cal({mr, yr});
        if (ansl > ansr) l = ml;
        else r = mr;
    }
    double ansX = (l + r) / 2, ansY = searchY(ansX);
}