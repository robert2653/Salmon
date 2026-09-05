// P * P > ll => mul in pollard rho
// P * 2 > int => x int to ll
const int P = 1E9 + 7;
template<class T> constexpr T power(T a, ll b) {
	T res{1};
	for (; b > 0; b >>= 1, a *= a)
		if (b & 1) res *= a;
	return res;
} // b2c151
struct Z { // simple
	int x;
	Z(ll v = 0) : x(v % P) { if (x < 0) x += P; }
	Z operator-() const { return P - x; }
	Z inv() const { return power(*this, P - 2); }

	Z &operator+=(Z a) { if ((x += a.x) >= P) x -= P; return *this; }
	Z &operator-=(Z a) { if ((x -= a.x) < 0) x += P; return *this; }
	Z &operator*=(Z a) { x = 1LL * x * a.x % P; return *this; }
	Z &operator/=(Z a) { return *this *= a.inv(); }
	
	friend Z operator+(Z a, Z b) { return a += b; }
	friend Z operator-(Z a, Z b) { return a -= b; }
	friend Z operator*(Z a, Z b) { return a *= b; }
	friend Z operator/(Z a, Z b) { return a /= b; }

	friend istream &operator>>(istream &is, Z &a)
	{ ll v; is >> v; a = Z(v); return is; }
	friend ostream &operator<<(ostream &os, Z a)
	{ return os << a.x; }
}; // 902589
template<int P> struct Mint {
	static int Mod;
	static int p() { return P > 0 ? P : Mod; }
	static void setMod(int Mod_) { Mod = Mod_; }
	int x;
	Mint(ll v = 0) : x(v % p()) { if (x < 0) x += p(); }
	Mint operator-() const { return p() - x; }
	Mint inv() const { return power(*this, p() - 2); }

	Mint &operator+=(Mint a) { if ((x += a.x) >= p()) x -= p(); return *this; }
	Mint &operator-=(Mint a) { if ((x -= a.x) < 0) x += p(); return *this; }
	Mint &operator*=(Mint a) { x = 1LL * x * a.x % p(); return *this; }
	Mint &operator/=(Mint a) { return *this *= a.inv(); }
	
	friend Mint operator+(Mint a, Mint b) { return a += b; }
	friend Mint operator-(Mint a, Mint b) { return a -= b; }
	friend Mint operator*(Mint a, Mint b) { return a *= b; }
	friend Mint operator/(Mint a, Mint b) { return a /= b; }

	bool operator==(Mint y) const { return x == y.x; }
	bool operator!=(Mint y) const { return x != y.x; }

	friend istream &operator>>(istream &is, Mint &a)
	{ ll v; is >> v; a = Mint(v); return is; }
	friend ostream &operator<<(ostream &os, Mint a)
	{ return os << a.x; }
};
template<> int Mint<0>::Mod = 998244353;
using Z = Mint<P>;
// 260f7e
vector<Z> fac, invfac, inv;
void init(int n) {
	fac.resize(n + 1);
	invfac.resize(n + 1);
	inv.resize(n + 1);
	fac[0] = invfac[0] = 1;
	for (int i = 1; i <= n; i++) {
		fac[i] = fac[i - 1] * i;
	}
	invfac[n] = fac[n].inv();
	for (int i = n; i > 0; i--) {
		invfac[i - 1] = invfac[i] * i;
		inv[i] = invfac[i] * fac[i - 1];
	}
} // c5dd4f
Z binom(int n, int m) {
	if (n < m || m < 0) return 0;
	return fac[n] * invfac[m] * invfac[n - m];
} // 9326d0
Z lucas(ll n, ll m) { // O(p + T log(n)), p is prime
	return m ? binom(n % P, m % P) * lucas(n / P, m / P) : 1;
} // de3d87