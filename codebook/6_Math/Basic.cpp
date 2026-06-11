#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int mod = 1E9 + 7;
template<class T> constexpr T power(T a, ll b) {
    T res {1};
    for (; b > 0; b >>= 1, a = a * a)
    if (b & 1) res = res * a;
    return res;
}
struct Z {
    ll x;
    Z(ll v = 0) {
        x = v % mod;
        if (x < 0) x += mod;
    }
    explicit operator ll() const { return x; }
    Z operator-() const { return mod - x; }
    Z inv() const { return power(*this, mod - 2); }
    Z operator+(Z a) const { return x + a.x; }
    Z operator-(Z a) const { return x - a.x; }
    Z operator*(Z a) const { return x * a.x; }
    Z operator/(Z a) const { return *this * a.inv(); }
    
    Z &operator+=(Z a) { return *this = *this + a; }
    Z &operator-=(Z a) { return *this = *this - a; }
    Z &operator*=(Z a) { return *this = *this * a; }
    Z &operator/=(Z a) { return *this = *this / a; }
};
istream &operator>>(istream &is, Z &a)
{ ll v; is >> v; a = Z(v); return is; }
ostream &operator<<(ostream &os, Z a)
{ return os << a.x; }

vector<Z> fac, invfac, inv;
void init(int n) {
    fac.resize(n + 1);
    invfac.resize(n + 1);
    inv.resize(n + 1);
    fac[0] = invfac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i;
    }
    for (int i = n; i > 0; i--) {
        invfac[i - 1] = invfac[i] * i;
        inv[i] = invfac[i] * fac[i - 1];
    }
}
Z binom(int n, int m) {
    if (n < m || m < 0) return 0;
    return fac[n] * invfac[m] * invfac[n - m];
}
Z lucas(ll n, ll m) { // O(p + T log(n)), p is prime
    return m ? binom(n % mod, m % mod) * lucas(n / mod, m / mod) : 1;
}