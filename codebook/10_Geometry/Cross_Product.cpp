#include <bits/stdc++.h>
using namespace std;
#define int long long
const double EPS = 1e-9;
template <typename T>
struct Point {
    struct component {
        T val;
        bool operator == (component a) { return fabs(val - a.val) < EPS; }
        bool operator < (component a) { return a.val - val > EPS; }
        bool operator <= (component a) { return *this < a || *this == a; }
        component () : val (0) { }
        component (T val) : val (val) {}
    };
    component x, y;
    component new_component() { return component(); }
    Point () : x(0), y(0) { }
    Point (T x, T y) : x(x), y(y) { }
    Point operator * (T a) { return { a * x.val, a * y.val }; }
    Point operator + (Point b) { return { x.val + b.x.val, y.val + b.y.val }; }
    Point operator - (Point b) { return { x.val - b.x.val, y.val - b.y.val }; }
    bool operator == (Point b) { return x == b.x && y == b.y; }
    bool operator < (Point b) { return x == b.x ? y < b.y : x < b.x; }
    component dot (Point b) {
        return x.val * b.x.val + y.val * b.y.val;
    }
    component cross (Point b) {
        return x.val * b.y.val - y.val * b.x.val;
    }
    double length () {
        return sqrt(x.val * x.val + y.val * y.val);
    }
};
template <class Point>
struct Geometry {
    int destination (Point a, Point b, Point c) {  // c 在 ab 的哪裡
        if ((b - a).cross(c - a) == Point().new_component()) return 0;  // 共線
        else if ((b - a).cross(c - a) < Point().new_component()) return -1;  // 左邊
        else return 1;  // 右邊
    }
    bool between (Point a, Point b, Point c) {
        if (destination(a, b, c) != 0) return false;
        else return (c - a).dot(c - b) <= Point().new_component();
    }
    bool intersect(Point a, Point b, Point c, Point d) {    // ab 跟 cd 是否相交
        if(between(a, b, c) || between(a, b, d) || between(c, d, a) || between(c, d, b)) return true;
        bool check1 = destination(a, b, c) * destination(a, b, d) < 0;  // c, d 在 ab 的不同方位
        bool check2 = destination(c, d, a) * destination(c, d, b) < 0;  // a, b 在 cd 的不同方位
        return check1 & check2;
    }
};
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    Geometry<Point<int>> geometry;
    while(n--){
        Point<int> a, b, c, d;
        cin >> a.x.val >> a.y.val >> b.x.val >> b.y.val >> c.x.val >> c.y.val >> d.x.val >> d.y.val;
        cout << (geometry.intersect(a, b, c, d) ? "YES\n" : "NO\n") << endl;
    }
}