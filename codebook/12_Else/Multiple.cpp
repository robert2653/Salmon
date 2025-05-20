// Require:
// Mint, NTT ~constructor and * operator
const int P1 = 1045430273;
const int P2 = 1051721729;
const int P3 = 1053818881;
const int r12 = Mint<P2>(Mint<P1>::getMod()).inv().x;
const int r13 = Mint<P3>(Mint<P1>::getMod()).inv().x;
const int r23 = Mint<P3>(Mint<P2>::getMod()).inv().x;
const int r1323 = Mint<P3>(ll(r13) * r23).x;
const ll w1 = Mint<P1>::getMod();
const ll w2 = w1 * Mint<P2>::getMod();
// Garner's Algorithm
template <typename T>
vector<T> arbitraryMult(const vector<int> &a, const vector<int> &b) {
    int n = a.size(), m = b.size();
    Poly<P1> x = Poly<P1>(a.begin(), a.end()) * Poly<P1>(b.begin(), b.end());
    Poly<P2> y = Poly<P2>(a.begin(), a.end()) * Poly<P2>(b.begin(), b.end());
    Poly<P3> z = Poly<P3>(a.begin(), a.end()) * Poly<P3>(b.begin(), b.end());
    vector<T> res(x.size());
    for (int i = 0; i < x.size(); i++) {
        ll p = x[i].x;
        ll q = (y[i].x + P2 - p) * r12 % P2;
        ll r = ((z[i] + P3 - p) * r1323 + (P3 - q) * r23).x % P3;
        res[i] = (T(r) * w2 + q * w1 + p);
    }
    return res;
}
private:
    vector<int> Multiple(vector<int> a, vector<int> b) {
        return norm(arbitraryMult<u128>(a, b));
    }
    vector<int> smallMul(vector<int> a, int v) {
        vector<ll> res(a.begin(), a.end());
        for (auto &x : res) x *= v;
        return norm(res);
    }
public:
    Bigint &operator*=(const Bigint &rhs) & {
        x = rhs.size() == 1 ? smallMul(x, rhs.x[0]) : Multiple(x, rhs.x);
        sgn *= rhs.sgn, resign();
        return *this;
    }
    friend Bigint operator*(Bigint lhs, Bigint rhs) {
        return lhs *= rhs;
    }