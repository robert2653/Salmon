template<class T>
T power(T a, ll b) {
    T res {1};
    for (; b; b /= 2, a *= a)
        if (b & 1) res *= a;
    return res;
}
constexpr int Mod = 1E9 + 7;
struct Z {
    ll x;
    Z(ll x = 0) : x {norm(x % Mod)} {}
    ll norm(ll x) const {
        if (x < 0) x += Mod;
        if (x >= Mod) x -= Mod;
        return x;
    }
    explicit operator int() const { return x; }
    Z operator-() const {
        return Z(norm(Mod - x));
    }
    Z inv() const {
        return power(*this, Mod - 2);
    }
    Z &operator+=(Z rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    Z &operator-=(Z rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    Z &operator*=(Z rhs) & {
        x = x * rhs.x % Mod;
        return *this;
    }
    Z &operator/=(Z rhs) & {
        return *this *= rhs.inv();
    }
    friend Z operator+(Z lhs, Z rhs) {
        return lhs += rhs;
    }
    friend Z operator-(Z lhs, Z rhs) {
        return lhs -= rhs;
    }
    friend Z operator*(Z lhs, Z rhs) {
        return lhs *= rhs;
    }
    friend Z operator/(Z lhs, Z rhs) {
        return lhs /= rhs;
    }
    friend istream &operator>>(istream &is, Z &a) {
        ll v; is >> v; a = Z(v); return is;
    }
    friend ostream &operator<<(ostream &os, const Z &a) {
        return os << a.x;
    }
};