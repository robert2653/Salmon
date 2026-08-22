// Require: Mint, NTT
using i128 = __int128_t;
const int P1 = 167772161;
const int P2 = 104857601;
const int P3 = 998244353;
const i128 T1 = i128(P2) * P3;
const i128 T2 = i128(P1) * P3;
const i128 T3 = i128(P1) * P2;
const int I1 = Mint<P1>(T1).inv().x;
const int I2 = Mint<P2>(T2).inv().x;
const int I3 = Mint<P3>(T3).inv().x;
const i128 M = i128(P1) * P2 * P3;
vector<i128> arbitraryMult(const vector<int> &a, const vector<int> &b) {
	int n = a.size(), m = b.size();
	auto x = conv(vector<Mint<P1>>(a.begin(), a.end()), vector<Mint<P1>>(b.begin(), b.end()));
	auto y = conv(vector<Mint<P2>>(a.begin(), a.end()), vector<Mint<P2>>(b.begin(), b.end()));
	auto z = conv(vector<Mint<P3>>(a.begin(), a.end()), vector<Mint<P3>>(b.begin(), b.end()));
	vector<i128> res(x.size());
	for (int i = 0; i < x.size(); i++)
		res[i] = (x[i].x * T1 % M * I1 +
				  y[i].x * T2 % M * I2 +
				  z[i].x * T3 % M * I3) % M;
	return res;
}
public:
	friend Bigint operator*(Bigint a, const Bigint &b) {
		a.x = a.norm(arbitraryMult(a.x, b.x));
		a.sgn *= b.sgn, a.resign();
		return a;
	}