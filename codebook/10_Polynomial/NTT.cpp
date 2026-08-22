template<class Z>
void ntt(vector<Z> &a, const int G = 3, bool inv = false) {
	static vector<int> rev;
	static vector<Z> w {0, 1};
	int n = a.size();
	if (rev.size() != n) {
		int k = __builtin_ctz(n) - 1;
		rev.resize(n);
		for (int i = 0; i < n; i++) rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
	}
	for (int i = 0; i < n; i++) if (rev[i] < i) swap(a[i], a[rev[i]]);
	if (w.size() < n) {
		int k = __builtin_ctz(w.size());
		w.resize(n);
		while ((1 << k) < n) {
			Z u = power(Z(G), (Z::p() - 1) >> (k + 1));
			for (int i = 1 << (k - 1); i < (1 << k); i++) {
				w[i * 2] = w[i];
				w[i * 2 + 1] = w[i] * u;
			}
			k++;
		}
	}
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k)
			for (int j = 0; j < k; j++) {
				Z u = a[i + j], v = a[i + j + k] * w[k + j];
				a[i + j] = u + v;
				a[i + j + k] = u - v;
			}
	if (inv) {
		reverse(a.begin() + 1, a.end());
		Z invn = Z(n).inv();
		for (auto &x : a) x *= invn;
	}
}
template<class Z>
vector<Z> conv(vector<Z> a, vector<Z> b, const int G = 3) {
	if (a.empty() || b.empty()) return {};
	int n = 1, tot = a.size() + b.size() - 1;
	while (n < tot) n <<= 1;
	a.resize(n), b.resize(n);
	ntt(a, G), ntt(b, G);
	for (int i = 0; i < n; i++) a[i] = a[i] * b[i];
	ntt(a, G, true);
	a.resize(tot);
	return a;
}