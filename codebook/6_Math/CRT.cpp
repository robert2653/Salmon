// ax = b (mod m) 的前提是 gcd(a, m) | b
// Ax + By = C    (g = gcd(A, B))
// (A/g) * x + (B/g) * y = C/g
// solve (A/g) * x' + (B/g) * y' = 1
// x = (x' * (C/g)) + i(B/g)
pair<ll, ll> exgcd(ll a, ll b) {
	if (b == 0) return {1, 0};
	auto [y, x] = exgcd(b, a % b);
	return {x, y - (a / b) * x};
} // 結果可能為負，注意正規化
// Smallest non-negative solution
using i128 = __int128_t;
pair<ll, ll> CRT(ll r1, ll m1, ll r2, ll m2) {
	ll g = __gcd(m1, m2);
	if ((r2 - r1) % g) return {-1, g};
	m1 /= g, m2 /= g;
	auto [p1, p2] = exgcd(m1, m2);
	i128 lcm = i128(m1) * m2 * g;
	i128 res = i128(p1) * (r2 - r1) * m1 + r1;
	return {(res % lcm + lcm) % lcm, lcm};
}
pair<ll, ll> EXCRT(vector<pair<int, int>> a) {
	ll R = 0, M = 1;
	for (auto [r, m] : a) {
		auto [res, lcm] = CRT(R, M, r, m);
		if (res == -1) return {-1, -1};
		R = res, M = lcm;
	}
	return {R, M};
}
// gcd(mod) = 1, support 3 1E9 Mod
pair<i128, i128> CRT(vector<pair<int, int>> a) {
	i128 s = 1, res = 0;
	for (auto [r, m] : a) s *= m;
	for (auto [r, m] : a) {
		i128 t = s / m;
		res = (res + r * t % s * exgcd(t, m).first % s) % s;
	}
	return {(res + s) % s, s};
}