const int P = 1E9 + 7;
ll mul(ll a, ll b, ll p) { // P 超過 int 再用，慢
	ll res = a * b - ll(1.L * a * b / p) * p;
	res %= p;
	if (res < 0) res += p;
	return res;
}
template<class T> constexpr T power(T a, ll b) {
	T res{1};
	for (; b > 0; b >>= 1, a = a * a)
	if (b & 1) res = res * a;
	return res;
}
template<int P> struct Mint {
	static int Mod;
	static int p() { return P > 0 ? P : Mod; }
	static void setMod(int Mod_) { Mod = Mod_; }
	int x;
	void norm(int &x) {
		if (x < 0) x += p();
		if (x >= p()) x -= p();
	}
	Mint(ll v = 0) : x(v % p()) { norm(x); }
	explicit operator int() const { return x; }
	Mint operator-() const { return p() - x; }
	Mint inv() const { return power(*this, p() - 2); }
	
	Mint &operator+=(Mint a) { norm(x += a.x); return *this; }
	Mint &operator-=(Mint a) { norm(x -= a.x); return *this; }
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
}
Z binom(int n, int m) {
	if (n < m || m < 0) return 0;
	return fac[n] * invfac[m] * invfac[n - m];
}
Z lucas(ll n, ll m) { // O(p + T log(n)), p is prime
	return m ? binom(n % P, m % P) * lucas(n / P, m / P) : 1;
}