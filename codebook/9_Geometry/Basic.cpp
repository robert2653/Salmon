const double eps = 1E-9;
template<class T>
struct Pt {
    T x, y;
    Pt(T x = 0, T y = 0) : x(x), y(y) {}
    Pt operator-() const { return Pt(-x, -y); }
    Pt operator+(Pt p) const { return Pt(x + p.x, y + p.y); }
    Pt operator-(Pt p) const { return Pt(x - p.x, y - p.y); }
    Pt operator*(T k) const { return Pt(x * k, y * k); }
    Pt operator/(T k) const { return Pt(x / k, y / k); }
    bool operator==(Pt p) const { return x == p.x && y == p.y; }
    bool operator!=(Pt p) const { return x != p.x || y != p.y; }
    friend istream &operator>>(istream &is, Pt &p)
    { return is >> p.x >> p.y; }
    friend ostream &operator<<(ostream &os, const Pt &p)
    { return os << "(" << p.x << ", " << p.y << ")"; }
};
int sign(double x)
{ return fabs(x) <= eps ? 0 : (x > 0 ? 1 : -1); }
using P = Pt<double>;

struct Line { P a, b; };
double dot(P a, P b) { return a.x * b.x + a.y * b.y; }
double cross(P a, P b) { return a.x * b.y - a.y * b.x; }
double square(P p) { return dot(p, p); }
double abs(P p) { return sqrt(square(p)); }
double dist(P a, P b) { return abs(a - b); }
double abs(Line l) { return abs(l.a - l.b); }
int dir(P p, Line l) // left -1, right 1, on 0
{ return -sign(cross(l.b - l.a, p - l.a)); }
bool btw(P p, Line l) // c on segment ab?
{ return dir(p, l) == 0 && sign(dot(p - l.a, p - l.b)) <= 0; }
P norm(P p) { return p / abs(p); }
P rot(P p) { return { -p.y, p.x }; } // 90 degree CCW
P rot(P p, double d) {
    double c = cos(d), s = sin(d);
    return { p.x * c - p.y * s, p.x * s + p.y * c };
}

bool parallel(Line l1, Line l2)
{ return cross(l1.b - l1.a, l2.b - l2.a) == 0; }
P lineIntersection(Line l1, Line l2)
{ return l1.a + (l1.b - l1.a) * (cross(l2.b - l2.a, l1.a - l2.a) / cross(l2.b - l2.a, l1.a - l1.b)); }
bool pointOnSegment(P p, Line l)
{ return dir(p, l) == 0 && sign(dot(p - l.a, p - l.b)) <= 0; }
P projvec(P p, Line l) {
    P v = l.b - l.a;
    return l.a + v * (dot(p - l.a, v) / square(v));
}
// 0 : not intersect
// 1 : strictly intersect
// 2 : overlap
// 3 : intersect at endpoint
tuple<int, P, P> segmentIntersection(Line l1, Line l2) {
    if (max(l1.a.x, l1.b.x) < min(l2.a.x, l2.b.x) ||
        min(l1.a.x, l1.b.x) > max(l2.a.x, l2.b.x) ||
        max(l1.a.y, l1.b.y) < min(l2.a.y, l2.b.y) ||
        min(l1.a.y, l1.b.y) > max(l2.a.y, l2.b.y))
        return {0, {}, {}};
    if (cross(l1.b - l1.a, l2.b - l2.a) == 0) {
        if (cross(l1.b - l1.a, l2.a - l1.a) != 0) {
            return {0, {}, {}};
        } else {
            auto maxx1 = max(l1.a.x, l1.b.x);
            auto minx1 = min(l1.a.x, l1.b.x);
            auto maxy1 = max(l1.a.y, l1.b.y);
            auto miny1 = min(l1.a.y, l1.b.y);
            auto maxx2 = max(l2.a.x, l2.b.x);
            auto minx2 = min(l2.a.x, l2.b.x);
            auto maxy2 = max(l2.a.y, l2.b.y);
            auto miny2 = min(l2.a.y, l2.b.y);
            P p1(max(minx1, minx2), max(miny1, miny2));
            P p2(min(maxx1, maxx2), min(maxy1, maxy2));
            if (!pointOnSegment(p1, l1)) swap(p1.y, p2.y);
            if (p1 == p2) return {3, p1, p2};
            else return {2, p1, p2};
        }
    }
    auto cp1 = cross(l2.a - l1.a, l2.b - l1.a);
    auto cp2 = cross(l2.a - l1.b, l2.b - l1.b);
    auto cp3 = cross(l1.a - l2.a, l1.b - l2.a);
    auto cp4 = cross(l1.a - l2.b, l1.b - l2.b);
    if ((cp1 > 0 && cp2 > 0) || (cp1 < 0 && cp2 < 0) || (cp3 > 0 && cp4 > 0) || (cp3 < 0 && cp4 < 0)) return {0, P(), P()};
    P p = lineIntersection(l1, l2);
    if (cp1 != 0 && cp2 != 0 && cp3 != 0 && cp4 != 0) return {1, p, p};
    else return {3, p, p};
}

vector<P> convexHull(vector<P> a) {
    sort(a.begin(), a.end(), [](const P &l, const P &r) {
        return l.x == r.x ? l.y < r.y : l.x < r.x;
    });
    a.resize(unique(a.begin(), a.end()) - a.begin());
    if (a.size() <= 1) return a;
    vector<P> h(a.size() + 1);
    int s = 0, t = 0;
    for (int i = 0; i < 2; i++, s = --t) {
        for (P p : a) {
            while (t >= s + 2 && cross(h[t - 1] - h[t - 2], p - h[t - 2]) <= 0) t--;
            h[t++] = p;
        }
        reverse(a.begin(), a.end());
    }
    return {h.begin(), h.begin() + t};
}

double distPL(P &p, Line &l)
{ return abs(cross(l.a - l.b, l.a - p)) / abs(l); }
double distancePS(P &p, Line &l) {
    if (dot(p - l.a, l.b - l.a) < 0) return dist(p, l.a);
    if (dot(p - l.b, l.a - l.b) < 0) return dist(p, l.b);
    return distPL(p, l);
}
double distanceSS(Line l1, Line l2) {
    if (get<0>(segmentIntersection(l1, l2)) != 0) return 0.0;
    return min({distancePS(l1.a, l2), distancePS(l1.b, l2), distancePS(l2.a, l1), distancePS(l2.b, l1)});
}

bool lineIntersectsPolygon(Line l, const vector<P> &p) {
    int n = p.size();
    P a = l.a, b = l.b;
    for (int i = 0; i < n; i++) {
        Line seg {p[i], p[(i + 1) % n]};
        if (cross(b - a, seg.a - a) == 0 || cross(b - a, seg.b - a) == 0) return true;
        if ((cross(b - a, seg.a - a) > 0) ^ (cross(b - a, seg.b - a) > 0)) return true;
    }
    return false;
}
bool pointInPolygon(P a, const vector<P> &p) {
    int n = p.size(), t = 0;
    for (int i = 0; i < n; i++)
        if (pointOnSegment(a, {p[i], p[(i + 1) % n]})) return true;
    for (int i = 0; i < n; i++) {
        P u = p[i], v = p[(i + 1) % n];
        if (u.x < a.x && v.x >= a.x && dir(a, {v, u}) < 0) t ^= 1;
        if (u.x >= a.x && v.x < a.x && dir(a, {u, v}) < 0) t ^= 1;
    }
    return t == 1;
}
// 0 : strictly outside
// 1 : on boundary
// 2 : strictly inside
int pointInConvexPolygon(P a, const vector<P> &p) {
    int n = p.size();
    if (n == 0) return 0;
    else if (n <= 2) return pointOnSegment(a, {p[0], p.back()});
    if (pointOnSegment(a, {p[0], p[1]}) || pointOnSegment(a, {p[0], p[n - 1]})) return 1;
    else if (dir(a, {p[0], p[1]}) < 0 || dir(a, {p[0], p[n - 1]}) < 0) return 0;
    int lo = 1, hi = n - 2;
    while (lo < hi) {
        int x = (lo + hi + 1) / 2;
        if (dir(a, {p[0], p[x]}) < 0) lo = x;
        else hi = x - 1;
    }
    if (dir(a, {p[lo], p[lo + 1]}) < 0) return 2;
    else return pointOnSegment(a, {p[lo], p[lo + 1]});
}
bool segmentInPolygon(Line l, const vector<P> &p) {
    int n = p.size();
    if (!pointInPolygon(l.a, p)) return false;
    if (!pointInPolygon(l.b, p)) return false;
    for (int i = 0; i < n; i++) {
        auto u = p[i];
        auto v = p[(i + 1) % n];
        auto w = p[(i + 2) % n];
        auto [t, p1, p2] = segmentIntersection(l, {u, v});
        if (t == 1) return false;
        if (t == 0) continue;
        if (t == 2) {
            if (pointOnSegment(v, l) && v != l.a && v != l.b && cross(u - v, w - v) < 0) return false;
        } else {
            if (p1 != u && p1 != v) {
                if (dir(l.a, {v, u}) < 0 || dir(l.b, {v, u}) < 0) return false;
            } else if (p1 == v) {
                if (l.a == v) {
                    if (dir(u, l) < 0) {
                        if (dir(w, l) < 0 && dir(w, {u, v}) < 0) return false;
                    } else if (dir(w, l) < 0 || dir(w, {u, v}) < 0) return false;
                } else if (l.b == v) {
                    if (dir(u, {l.b, l.a}) < 0) {
                        if (dir(w, {l.b, l.a}) < 0 && dir(w, {u, v}) < 0) return false;
                    } else if (dir(w, {l.b, l.a}) < 0 || dir(w, {u, v}) < 0) return false;
                } else {
                    if (dir(u, l) < 0) {
                        if (dir(w, {l.b, l.a}) < 0 || dir(w, {u, v}) < 0) return false;
                    } else if (dir(w, l) < 0 || dir(w, {u, v}) < 0) return false;
                }
            }
        }
    }
    return true;
}
vector<P> hp(vector<Line> lines) {
    auto sgn = [](P p) { return p.y > 0 || (p.y == 0 && p.x > 0) ? 1 : -1; };
    sort(lines.begin(), lines.end(), [&](auto l1, auto l2) {
        auto d1 = l1.b - l1.a;
        auto d2 = l2.b - l2.a;
        if (sgn(d1) != sgn(d2))
            return sgn(d1) == 1;
        return cross(d1, d2) > 0;
    });
    deque<Line> ls;
    deque<P> ps;
    for (auto l : lines) {
        if (ls.empty()) {
            ls.push_back(l);
            continue;
        }
        while (!ps.empty() && dir(ps.back(), l) >= 0) ps.pop_back(), ls.pop_back();
        while (!ps.empty() && dir(ps[0], l) >= 0) ps.pop_front(), ls.pop_front();
        if (cross(l.b - l.a, ls.back().b - ls.back().a) == 0) {
            if (dot(l.b - l.a, ls.back().b - ls.back().a) > 0) {
                if (dir(ls.back().a, l) >= 0) {
                    assert(ls.size() == 1);
                    ls[0] = l;
                }
                continue;
            }
            return {};
        }
        ps.push_back(lineIntersection(ls.back(), l));
        ls.push_back(l);
    }
    while (!ps.empty() && dir(ps.back(), ls[0]) >= 0)
        ps.pop_back(), ls.pop_back();
    if (ls.size() <= 2) return {};
    ps.push_back(lineIntersection(ls[0], ls.back()));
    return vector(ps.begin(), ps.end());
}