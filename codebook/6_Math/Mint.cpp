ll mul(ll a, ll b, ll p) {
    ll res = a * b - ll(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) res += p;
    return res;
}
// 改 MLong: getMod() < (1ULL << 31)，會爆用 mul
template<class T>
constexpr T power(T a, ll b) {
    T res {1};
    for (; b > 0; b >>= 1, a = a * a)
        if (b & 1) res = res * a;
    return res;
}
template<int P>
struct Mint {
    static int Mod;
    static int getMod()
    { return P > 0 ? P : Mod; }
    static void setMod(int Mod_)
    { Mod = Mod_; }
    ll x;
    Mint(ll x = 0) : x {norm(x % getMod())} {}
    ll norm(ll x) const {
        if (x < 0) x += getMod();
        if (x >= getMod()) x -= getMod();
        return x;
    }
    explicit operator int() const { return x; }
    Mint operator-() const
    { return Mint(norm(getMod() - x)); }
    Mint inv() const
    { return power(*this, getMod() - 2); }
    Mint operator+(Mint rhs) const
    { return Mint(norm(x + rhs.x)); }
    Mint operator-(Mint rhs) const
    { return Mint(norm(x - rhs.x)); }
    Mint operator*(Mint rhs) const
    { return Mint(mul(x, rhs.x, getMod())); }
    Mint operator/(Mint rhs) const
    { return *this * rhs.inv(); }

    
    Mint &operator+=(Mint rhs) { return *this = *this + rhs; }
    Mint &operator-=(Mint rhs) { return *this = *this - rhs; }
    Mint &operator*=(Mint rhs) { return *this = *this * rhs; }
    Mint &operator/=(Mint rhs) { return *this = *this / rhs; }
    
    friend istream &operator>>(istream &is, Mint &a)
    { ll v; is >> v; a = Mint(v); return is; }
    friend ostream &operator<<(ostream &os, Mint a)
    { return os << a.x; }
    bool operator==(Mint y) const { return x == y.x; }
    bool operator!=(Mint y) const { return x != y.x; }
};
template<>
int Mint<0>::Mod = 998244353;
constexpr int P = 1E9 + 7;
using Z = Mint<P>;