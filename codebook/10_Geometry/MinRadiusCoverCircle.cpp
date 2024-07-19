template<class T>
Point<T> getCir(const Point<T> &a, const Point<T> &b, const Point<T> &c) {
    T d = T(2) * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
    T h = ((a.x * a.x + a.y * a.y) * (b.y - c.y) + (b.x * b.x + b.y * b.y) * (c.y - a.y) + (c.x * c.x + c.y * c.y) * (a.y - b.y)) / d;
    T k = ((a.x * a.x + a.y * a.y) * (c.x - b.x) + (b.x * b.x + b.y * b.y) * (a.x - c.x) + (c.x * c.x + c.y * c.y) * (b.x - a.x)) / d;
    return Point<T>(h, k);
}
template<class T>
pair<T, Point<T>> MinCircular(vector<Point<T>> &a) {
    random_shuffle(a.begin(), a.end());
    int n = a.size();
    Point<T> c = a[0]; T r = 0;
    for (int i = 1; i < n; i++) {
        if (T(length(c - a[i]) - r) > 0.0) {
            c = a[i], r = 0;
            for (int j = 0; j < i; j++) {
                if (T(length(c - a[j]) - r) > 0.0) {
                    c = (a[i] + a[j]) / 2.0;
                    r = length(c - a[i]);
                    for (int k = 0; k < j; k++) {
                        if (T(length(c - a[k]) - r) > 0.0) {
                            c = getCir(a[i], a[j], a[k]);
                            r = length(c - a[i]);
                        }
                    }
                }
            }
        }
    }
    return make_pair(r, c);
}