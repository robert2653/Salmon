using i128 = __int128_t; // 1.7E38
istream &operator>>(istream &is, i128 &a) {
    i128 sgn = 1; a = 0;
    string s; cin >> s;
    for (auto c : s) {
        if (c == '-') {
            sgn = -1;
        } else {
            a = a * 10 + c - '0';
        }
    }
    a *= sgn;
    return is;
}
ostream &operator<<(ostream &os, i128 a) {
    string res; int sgn = 1;
    if (a < 0) {
        sgn = -1, a = -a;
    }
    while (a) {
        res.push_back(a % 10 + '0');
        a /= 10;
    }
    if (sgn == -1) res.push_back('-');
    reverse(res.begin(), res.end());
    cout << res;
    return os;
}