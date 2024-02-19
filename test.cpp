#include <bits/stdc++.h>
using namespace std;
const double EPS = 1e-9;
template <typename T>
struct point {
    struct component {
        T val;
        bool operator == (component a) { return abs(val - a.val) < EPS; }
        bool operator < (component a) { return a.val - val > EPS; }
        bool operator > (component a) { return val - a.val > EPS; }
    };
    component x, y;
    point(T x, T y) {
        this->x.val = x;
        this->y.val = y;
    }
    point operator * (T a) { return { a * x.val, a * y.val }; }
    point operator + (point b) { return { x.val + b.x.val, y.val + b.y.val }; }
    point operator - (point b) { return { x.val - b.x.val, y.val - b.y.val }; }
    T dot (point b) {
        return x.val * b.x.val + y.val * b.y.val;
    }
    T cross(point b) {
        return x.val * b.y.val - y.val * b.x.val;
    }
    bool operator == (point b) { return x == b.x && y == b.y; }
    bool operator < (point b) { return x == b.x ? y < b.y : x < b.x; }
    double length() {
        return sqrt(x.val * x.val + y.val * y.val);
    }
};
int main(){
    point<double> a(1.0, 2.0);
    point<double> b(1.0, 2.0);
    cout << (a < b) << endl;
}