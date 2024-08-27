struct D {
    double x;
    constexpr D() : x{0} {}
    constexpr D(double x) : x{x} {}
    constexpr static double eps = 1E-12;
    explicit operator double() const { return x; }
    constexpr D operator-() const {
        return D(-x);
    }
    constexpr D &operator*=(D rhs) & {
        x *= rhs.x; return *this;
    }
    constexpr D &operator+=(D rhs) & {
        x += rhs.x; return *this;
    }
    constexpr D &operator-=(D rhs) & {
        x -= rhs.x; return *this;
    }
    constexpr D &operator/=(D rhs) & {
        assert(fabs(rhs.x) > eps);
        x /= rhs.x; return *this;
    }
    friend constexpr D operator*(D lhs, D rhs) {
        return lhs *= rhs;
    }
    friend constexpr D operator+(D lhs, D rhs) {
        return lhs += rhs;
    }
    friend constexpr D operator-(D lhs, D rhs) {
        return lhs -= rhs;
    }
    friend constexpr D operator/(D lhs, D rhs) {
        return lhs /= rhs;
    }
    friend istream &operator>>(istream &is, D &a) {
        double v; is >> v; a = D(v); return is;
    }
    friend ostream &operator<<(ostream &os, const D &a) {
        return os << fixed << setprecision(10) << a.x + (a.x > 0 ? eps : a.x < 0 ? -eps : 0);
    } // eps should < precision
    friend constexpr bool operator<(D lhs, D rhs) {
        return lhs.x - rhs.x < -eps;
    }
    friend constexpr bool operator>(D lhs, D rhs) {
        return lhs.x - rhs.x > eps;
    }
    friend constexpr bool operator==(D lhs, D rhs) {
        return fabs(lhs.x - rhs.x) < eps;
    }
    friend constexpr bool operator<=(D lhs, D rhs) {
        return lhs < rhs || lhs == rhs;
    }
    friend constexpr bool operator>=(D lhs, D rhs) {
        return lhs > rhs || lhs == rhs;
    }
    friend constexpr bool operator!=(D lhs, D rhs) {
        return !(lhs == rhs);
    }
};