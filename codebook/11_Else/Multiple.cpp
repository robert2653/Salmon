// Require: Mint, NTT
using i128 = __int128_t;
vector<i128> arbitraryMult(const vector<int> &a, const vector<int> &b) {
	auto x = conv(vector<Z1>(a.begin(), a.end()), vector<Z1>(b.begin(), b.end()));
	auto y = conv(vector<Z2>(a.begin(), a.end()), vector<Z2>(b.begin(), b.end()));
	auto z = conv(vector<Z3>(a.begin(), a.end()), vector<Z3>(b.begin(), b.end()));
	vector<i128> res(x.size());
	for (int i = 0; i < x.size(); i++)
		res[i] = garner<i128>(x[i].x, y[i].x, z[i].x);
	return res;
}
public:
	friend Bigint operator*(Bigint a, const Bigint &b) {
		a.x = a.norm(arbitraryMult(a.x, b.x));
		a.sgn *= b.sgn, a.resign();
		return a;
	}