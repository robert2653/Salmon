// Require:
// Mint, NTT ~constructor and * operator
using i128 = __int128_t;
const int P1 = 1045430273; // 2^20 * 997 + 1
const int P2 = 1051721729; // 2^20 * 1003 + 1
const int P3 = 1053818881; // 2^20 * 1007 + 1
using Poly1 = Poly<1045430273, 3>;
using Poly2 = Poly<1051721729, 6>;
using Poly3 = Poly<1053818881, 7>;
const i128 T1 = i128(P2) * P3;
const i128 T2 = i128(P1) * P3;
const i128 T3 = i128(P1) * P2;
const int I1 = Mint<P1>(T1).inv().x;
const int I2 = Mint<P2>(T2).inv().x;
const int I3 = Mint<P3>(T3).inv().x;
const i128 M = i128(P1) * P2 * P3;
vector<i128> arbitraryMult(const vector<int> &a, const vector<int> &b) {
    int n = a.size(), m = b.size();
    Poly1 x = Poly1(a.begin(), a.end()) * Poly1(b.begin(), b.end());
    Poly2 y = Poly2(a.begin(), a.end()) * Poly2(b.begin(), b.end());
    Poly3 z = Poly3(a.begin(), a.end()) * Poly3(b.begin(), b.end());
    vector<i128> res(x.size());
    for (int i = 0; i < x.size(); i++)
        res[i] = (x[i].x * T1 % M * I1 +
                  y[i].x * T2 % M * I2 +
                  z[i].x * T3 % M * I3) % M;
    return res;
}
public:
    friend Bigint operator*(Bigint a, Bigint b) {
        a.x = a.norm(arbitraryMult(a.x, b.x));
        a.sgn *= b.sgn, a.resign();
        return a;
    }