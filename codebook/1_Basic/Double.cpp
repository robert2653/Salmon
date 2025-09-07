struct D {
    double x;
    D(double x = 0.0) : x{x} {}
    constexpr static double eps = 1E-12;
    explicit operator double() const { return x; }
    D operator-() const { return D(-x); }
    D &operator+=(D b) & { x += b.x; return *this; }
    D &operator-=(D b) & { x -= b.x; return *this; }
    D &operator*=(D b) & { x *= b.x; return *this; }
    D &operator/=(D b) & {
        assert(fabs(b.x) > eps);
        x /= b.x; return *this;
    }
    friend D operator+(D a, D b) { return a += b; }
    friend D operator-(D a, D b) { return a -= b; }
    friend D operator*(D a, D b) { return a *= b; }
    friend D operator/(D a, D b) { return a /= b; }
    friend istream &operator>>(istream &is, D &a) {
        double v; is >> v; a = D(v); return is;
    }
    friend ostream &operator<<(ostream &os, const D &a) {
        return os << fixed << setprecision(9) << a.x + (a.x > 0 ? eps : a.x < 0 ? -eps : 0);
    } // eps should < precision
    friend bool operator<(D lhs, D rhs) {
        return lhs.x - rhs.x < -eps;
    }
    friend bool operator>(D lhs, D rhs) {
        return lhs.x - rhs.x > eps;
    }
    friend bool operator==(D lhs, D rhs) {
        return fabs(lhs.x - rhs.x) < eps;
    }
};
D abs(D a) { return a < 0 ? -a : a; }