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
const int NP0 = 167772161, NP1 = 104857601, NP2 = 998244353;
using Z0 = Mint<167772161>;
using Z1 = Mint<104857601>;
using Z2 = Mint<998244353>;
template<class Z>
vector<Z> convArb(vector<Z> a, vector<Z> b) {
	vector<Z0> a0(a.size()), b0(b.size());
	vector<Z1> a1(a.size()), b1(b.size());
	vector<Z2> a2(a.size()), b2(b.size());
	for (int i = 0; i < a.size(); i++) {
		a0[i] = a[i].x;
		a1[i] = a[i].x;
		a2[i] = a[i].x;
	}
	for (int i = 0; i < b.size(); i++) {
		b0[i] = b[i].x;
		b1[i] = b[i].x;
		b2[i] = b[i].x;
	}
	auto c0 = conv(a0, b0);
	auto c1 = conv(a1, b1);
	auto c2 = conv(a2, b2);
	int inv01 = Z1(NP0).inv().x;
	int inv012 = Z2(1LL * NP0 * NP1).inv().x;
	int tot = a.size() + b.size() - 1;
	vector<Z> res(tot);
	for (int i = 0; i < tot; i++) {
		int r0 = c0[i].x, r1 = c1[i].x, r2 = c2[i].x;
		Z1 t1 = Z1(r1 - r0) * inv01;
		Z2 t2 = Z2(r2 - r0 - 1LL * NP0 * t1.x) * inv012;
		res[i] = Z(r0) + Z(NP0) * t1.x + Z(NP0) * NP1 * t2.x;
	}
	return res;
} // f5a0db