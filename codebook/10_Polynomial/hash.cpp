template<class Z>
void ntt(vector<Z> &a, const int G = 3, bool inv = false) {
	static vector<Z> w {0, 1};
	int n = a.size();
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
	if (!inv) {
		for (int k = n / 2; k >= 1; k /= 2)
			for (int i = 0; i < n; i += 2 * k)
				for (int j = 0; j < k; j++) {
					Z u = a[i + j], v = a[i + j + k];
					a[i + j] = u + v;
					a[i + j + k] = (u - v) * w[k + j];
				}
		return;
	}
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k)
			for (int j = 0; j < k; j++) {
				Z u = a[i + j], v = a[i + j + k] * w[k + j];
				a[i + j] = u + v;
				a[i + j + k] = u - v;
			}
	reverse(a.begin() + 1, a.end());
	Z invn = Z(n).inv();
	for (auto &x : a) x *= invn;
} // 49b183