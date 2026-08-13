// a_i = c[0] * a_{i - 1} + c[1] * a_{i - 2} + ... + c[k - 1] * a_{i - k}
// q(x) = 1 - c[0] * x - c[1] * x^2 - ... - c[k - 1] * x^k
// p(x) = (a * q).trunc(c.size())
// return : a_n
template<int P = 998244353> // O(m log m log n)
Mint<P> linearRecurrence(Poly<P> p, Poly<P> q, ll n) {
	int m = q.size() - 1;
	while (n > 0) {
		auto nq = q;
		for (int i = 1; i <= m; i += 2) nq[i] *= -1;
		auto np = p * nq;
		nq = q * nq;
		for (int i = 0; i < m; i++) p[i] = np[i * 2 + n % 2];
		for (int i = 0; i <= m; i++) q[i] = nq[i * 2];
		n /= 2;
	}
	return p[0] / q[0];
}