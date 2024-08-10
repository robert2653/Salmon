struct D {
    double x;
    constexpr static double eps = 1E-12;
    D() : x{0.0} {}
    D(double v) : x{v} {}
    double val() const { return x; }
    explicit operator double() const { return x; }
    D operator-() const {
        return D(-x);
    }
    D &operator+=(const D &rhs) & {
        x += rhs.x; return *this;
    }
    D &operator-=(const D &rhs) & {
        x -= rhs.x; return *this;
    }
    D &operator*=(const D &rhs) & {
        x *= rhs.x; return *this;
    }
    D &operator/=(const D &rhs) & {
        assert(fabs(rhs.x) > eps);
        x /= rhs.x; return *this;
    }
    friend D operator+(D lhs, const D &rhs) {
        return lhs += rhs;
    }
    friend D operator-(D lhs, const D &rhs) {
        return lhs -= rhs;
    }
    friend D operator*(D lhs, const D &rhs) {
        return lhs *= rhs;
    }
    friend D operator/(D lhs, const D &rhs) {
        return lhs /= rhs;
    }
    friend bool operator<(const D &lhs, const D &rhs) {
        return lhs.x - rhs.x < -eps;
    }
    friend bool operator>(const D &lhs, const D &rhs) {
        return lhs.x - rhs.x > eps;
    }
    friend bool operator==(const D &lhs, const D &rhs) {
        return fabs(lhs.x - rhs.x) < eps;
    }
    friend bool operator<=(const D &lhs, const D &rhs) {
        return lhs < rhs || lhs == rhs;
    }
    friend bool operator>=(const D &lhs, const D &rhs) {
        return lhs > rhs || lhs == rhs;
    }
    friend bool operator!=(const D &lhs, const D &rhs) {
        return !(lhs == rhs);
    }
    friend istream &operator>>(istream &is, D &a) {
        double v; is >> v; a = D(v); return is;
    }
    friend ostream &operator<<(ostream &os, const D &a) {
        return os << fixed << setprecision(10) << a.val()
        + (a.val() > 0 ? eps : a.val() < 0 ? -eps : 0);
    } // eps should < precision
};