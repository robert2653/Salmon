const int P = 998244353, G = 3; // Mint
void ntt(vector<Z> &a, bool inv) {
	int n = a.size();
	for (int i = 1, j = 0; i < n; i++) {
		int b = n >> 1;
		for (; j & b; b >>= 1) j ^= b;
		j ^= b;
		if (i < j) swap(a[i], a[j]);
	}
	for (int len = 2; len <= n; len <<= 1) {
		Z w = power(Z(G), (P - 1) / len);
		if (inv) w = w.inv();
		for (int i = 0; i < n; i += len) {
			Z wn = 1;
			for (int j = 0; j < len / 2; j++) {
				Z u = a[i + j], v = a[i + j + len / 2] * wn;
				a[i + j] = u + v;
				a[i + j + len / 2] = u - v;
				wn *= w;
			}
		}
	}
	if (inv) for (auto &x : a) x /= n;
}
vector<Z> conv(vector<Z> a, vector<Z> b) {
	if (a.empty() || b.empty()) return {};
	int tot = a.size() + b.size() - 1, sz = 1;
	while (sz < tot) sz <<= 1;
	a.resize(sz), b.resize(sz);
	ntt(a, false), ntt(b, false);
	for (int i = 0; i < sz; i++) a[i] = a[i] * b[i];
	ntt(a, true);
	a.resize(tot);
	return a;
}