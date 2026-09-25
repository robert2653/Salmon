const double PI = acos(-1.0);
using cd = complex<double>;
void fft(vector<cd> &a, bool inv = false) {
	static vector<cd> w {0, 1};
	int n = a.size();
	for (int k = w.size(); k < n; k *= 2) {
		w.resize(2 * k);
		for (int j = 0; j < k; j++) w[k + j] = polar(1.0, PI * j / k);
	}
	if (!inv) {
		for (int k = n / 2; k >= 1; k /= 2)
			for (int i = 0; i < n; i += 2 * k)
				for (int j = 0; j < k; j++) {
					cd u = a[i + j], v = a[i + j + k];
					a[i + j] = u + v;
					a[i + j + k] = (u - v) * w[k + j];
				}
		return;
	}
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k)
			for (int j = 0; j < k; j++) {
				cd u = a[i + j], v = a[i + j + k] * w[k + j];
				a[i + j] = u + v;
				a[i + j + k] = u - v;
			}
	reverse(a.begin() + 1, a.end());
	for (auto &x : a) x /= n;
}
// i + j = k, res[1] = a[1] * b[0] + a[0] * b[1]
// reverse b for i - j = k, res[k + b.size() - 1]
template<class T> vector<double> conv(vector<T> a, vector<T> b) {
	vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	int n = 1, tot = a.size() + b.size() - 1;
	while (n < tot) n <<= 1;
	fa.resize(n), fb.resize(n);
	fft(fa), fft(fb);
	for (int i = 0; i < n; i++) fa[i] = fa[i] * fb[i];
	fft(fa, true);
	vector<double> res(tot);
	for (int i = 0; i < tot; i++) res[i] = fa[i].real();
	return res; // use lround to int
}