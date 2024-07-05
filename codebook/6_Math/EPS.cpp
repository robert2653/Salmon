struct EDouble {
    double x;
    constexpr static double Epi = 1e-9;
    constexpr EDouble() : x{} {}
    constexpr EDouble(double v) : x{v} {}
    constexpr double val() const {
        return x;
    }
    explicit constexpr operator double() const {
        return x;
    }
    constexpr EDouble operator-() const {
        return EDouble(-x);
    }
    constexpr EDouble &operator+=(const EDouble &rhs) & {
        x += rhs.x;
        return *this;
    }
    constexpr EDouble &operator-=(const EDouble &rhs) & {
        x -= rhs.x;
        return *this;
    }
    constexpr EDouble &operator*=(const EDouble &rhs) & {
        x *= rhs.x;
        return *this;
    }
    constexpr EDouble &operator/=(const EDouble &rhs) & {
        assert(fabs(rhs.x) > Epi);
        x /= rhs.x;
        return *this;
    }
    friend constexpr EDouble operator+(EDouble lhs, const EDouble &rhs) {
        lhs += rhs;
        return lhs;
    }
    friend constexpr EDouble operator-(EDouble lhs, const EDouble &rhs) {
        lhs -= rhs;
        return lhs;
    }
    friend constexpr EDouble operator*(EDouble lhs, const EDouble &rhs) {
        lhs *= rhs;
        return lhs;
    }
    friend constexpr EDouble operator/(EDouble lhs, const EDouble &rhs) {
        lhs /= rhs;
        return lhs;
    }
    friend constexpr bool operator<(const EDouble &lhs, const EDouble &rhs) {
        return lhs.x - rhs.x < Epi;
    }
    friend constexpr bool operator>(const EDouble &lhs, const EDouble &rhs) {
        return lhs.x - rhs.x > Epi;
    }
    friend constexpr bool operator==(const EDouble &lhs, const EDouble &rhs) {
        return fabs(lhs.x - rhs.x) < Epi;
    }
    friend constexpr bool operator<=(const EDouble &lhs, const EDouble &rhs) {
        return lhs < rhs || lhs == rhs;
    }
    friend constexpr bool operator>=(const EDouble &lhs, const EDouble &rhs) {
        return lhs > rhs || lhs == rhs;
    }
    friend constexpr bool operator!=(const EDouble &lhs, const EDouble &rhs) {
        return !(lhs == rhs);
    }
    friend istream &operator>>(istream &is, EDouble &a) {
        double v; is >> v;
        a = EDouble(v);
        return is;
    }
    friend ostream &operator<<(ostream &os, const EDouble &a) {
        return os << a.val();
    }
};
 
namespace std {
    template<>
    class numeric_limits<EDouble> {
    public:
        static constexpr EDouble max() noexcept {
            return EDouble(numeric_limits<double>::max());
        }
        static constexpr EDouble min() noexcept {
            return EDouble(numeric_limits<double>::min());
        }
    };
}
 
using E = EDouble;