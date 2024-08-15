template<class T>
vector<Point<T>> convexHull(vector<Point<T>> a) {
    sort(a.begin(), a.end(), [](const Point<T> &l, const Point<T> &r) {
        return l.x == r.x ? l.y < r.y : l.x < r.x;
    });
    a.resize(unique(a.begin(), a.end()) - a.begin());
    if (a.size() <= 1) return a;
    vector<Point<T>> hull; 
    for(int i = 0; i < 2; i++){
        int t = hull.size();
        for (Point<T> p : a) {
            while (hull.size() - t >= 2 && cross(hull.back() - hull[hull.size() - 2], p - hull[hull.size() - 2]) <= 0) {
                hull.pop_back(); // 要不要有等於要看點有沒有在邊上
            }
            hull.push_back(p);
        }
        hull.pop_back();
        reverse(a.begin(), a.end());
    }
    return hull;
}