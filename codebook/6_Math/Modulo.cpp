template<class T>
T power(T a, ll b) {
    T res {1};
    for (; b; b /= 2, a *= a)
        if (b & 1) res *= a;
    return res;
}
ll mul(ll a, ll b, ll p) { // 大模數再抄
    ll res = a * b - ll(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) res += p;
    return res;
}
template<ll P>
struct MInt {
    ll x;
    MInt() : x {0} {}
    MInt(ll x) : x {norm(x % getMod())} {}
    static ll Mod;
    static ll getMod() {
        return P > 0 ? P : Mod;
    }
    static void setMod(ll Mod_) {
        Mod = Mod_;
    }
    ll norm(ll x) const {
        if (x < 0) x += getMod();
        if (x >= getMod()) x -= getMod();
        return x;
    }
    MInt operator-() const {
        return MInt(norm(getMod() - x));
    }
    MInt inv() const {
        return power(*this, getMod() - 2);
    }
    MInt &operator*=(MInt rhs) & {
        if (getMod() < (1ULL << 31)) {
            x = x * rhs.x % int(getMod());
        } else {
            x = mul(x, rhs.x, getMod());
        }
        return *this;
    }
    MInt &operator+=(MInt rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    MInt &operator-=(MInt rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    MInt &operator/=(MInt rhs) & {
        return *this *= rhs.inv();
    }
    friend MInt operator*(MInt lhs, MInt rhs) {
        return lhs *= rhs;
    }
    friend MInt operator+(MInt lhs, MInt rhs) {
        return lhs += rhs;
    }
    friend MInt operator-(MInt lhs, MInt rhs) {
        return lhs -= rhs;
    }
    friend MInt operator/(MInt lhs, MInt rhs) {
        return lhs /= rhs;
    }
    friend istream &operator>>(istream &is, MInt &a) {
        ll v; is >> v; a = MInt(v); return is;
    }
    friend ostream &operator<<(ostream &os, const MInt &a) {
        return os << a.x;
    }
    friend bool operator==(MInt lhs, MInt rhs) {
        return lhs.x == rhs.x;
    }
    friend bool operator!=(MInt lhs, MInt rhs) {
        return lhs.x != rhs.x;
    }
    friend bool operator<(MInt lhs, MInt rhs) {
        return lhs.x < rhs.x;
    }
};
template<>
ll MInt<0>::Mod = 998244353;
constexpr ll P = 1E9 + 7;
using Z = MInt<P>;