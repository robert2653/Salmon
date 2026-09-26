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
} // 53376c
const int G = 3;
const int P1 = 167772161, P2 = 104857601, P3 = 998244353;
using Z1 = Mint<P1>;
using Z2 = Mint<P2>;
using Z3 = Mint<P3>;
const int I12 = Z2(P1).inv().x;
const int I123 = Z3(1LL * P1 * P2).inv().x;
template<class T> T garner(int r1, int r2, int r3) {
	Z2 t1 = Z2(r2 - r1) * I12;
	Z3 t2 = Z3(r3 - r1 - 1LL * P1 * t1.x) * I123;
	return T(r1) + T(P1) * t1.x + T(P1) * P2 * t2.x;
} // 6def25
template<class Z>
vector<Z> convArb(vector<Z> a, vector<Z> b) {
	vector<Z1> a1(a.size()), b1(b.size());
	vector<Z2> a2(a.size()), b2(b.size());
	vector<Z3> a3(a.size()), b3(b.size());
	for (int i = 0; i < a.size(); i++) {
		a1[i] = a[i].x;
		a2[i] = a[i].x;
		a3[i] = a[i].x;
	}
	for (int i = 0; i < b.size(); i++) {
		b1[i] = b[i].x;
		b2[i] = b[i].x;
		b3[i] = b[i].x;
	}
	auto c1 = conv(a1, b1);
	auto c2 = conv(a2, b2);
	auto c3 = conv(a3, b3);
	int tot = a.size() + b.size() - 1;
	vector<Z> res(tot);
	for (int i = 0; i < tot; i++)
		res[i] = garner<Z>(c1[i].x, c2[i].x, c3[i].x);
	return res;
} // 7e3465