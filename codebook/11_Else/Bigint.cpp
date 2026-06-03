struct Bigint { // not support hex division
private:
    static const int digit = 9;  // hex: 7
    static const int base = 10;  // hex: 16
    static const int B = power(ll(base), digit);
    Bigint(vector<int> x, int sgn) : x(x), sgn(sgn) {}
    template<class U> vector<int> norm(vector<U> a) {
        if (a.empty()) return {0};
        for (int i = 0; i < a.size(); i++) {
            U c = a[i];
            a[i] = c % B;
            c /= B;
            if (c) {
                if (i == a.size() - 1) a.push_back(c);
                else a[i + 1] += c;
            }
        }
        while (a.size() > 1 && a.back() == 0) a.pop_back();
        return {a.begin(), a.end()};
    }
    void resign() { sgn = x.back() == 0 ? 1 : sgn; }
    int toInt(char c) const {
        if (isdigit(c)) return c - '0';
        else return c - 'A' + 10;
    }
    char toChar(int c) const {
        if (c < 10) return c + '0';
        else return c - 10 + 'A';
    }
public:
    int sgn = 1;
    vector<int> x; // 反著存
    Bigint() : x {0}, sgn(1) {}
    Bigint(ll a) { *this = Bigint(std::to_string(a)); }
    Bigint(string s) {
        if (s.empty()) { *this = Bigint(); return; }
        if (s[0] == '-') s.erase(s.begin()), sgn = -1;
        int add = 0, cnt = 0, b = 1;
        while (s.size()) {
            if (cnt == digit) {
                x.push_back(add), add = cnt = 0;
                b = 1;
            }
            add += toInt(s.back()) * b;
            cnt++, b *= base;
            s.pop_back();
        }
        if (add) x.push_back(add);
        x = norm(x);
    }
    int size() const { return x.size(); }
    Bigint abs() const { return Bigint(x, 1); }
    string to_string() const {
        string res;
        for (int i = 0; i < x.size(); i++) {
            string add; int v = x[i];
            for (int j = 0; j < digit; j++)
                add += toChar(v % base), v /= base;
            res += add;
        }
        while (res.size() > 1 && res.back() == '0') res.pop_back();
        if (sgn == -1) res += '-';
        reverse(res.begin(), res.end());
        return res;
    }
    Bigint operator-() const { return Bigint(x, -sgn); }
    friend Bigint operator+(Bigint a, Bigint b) {
        if (a.sgn != b.sgn) return a - (-b);
        int n = max(a.size(), b.size());
        a.x.resize(n), b.x.resize(n);
        for (int i = 0; i < n; i++) a.x[i] += b.x[i];
        a.x = a.norm(a.x), a.resign();
        return a;
    }
    friend Bigint operator-(Bigint a, Bigint b) {
        if (a.sgn != b.sgn) return a + (-b);
        if (a.abs() < b.abs()) return -(b - a);
        int n = max(a.size(), b.size());
        a.x.resize(n), b.x.resize(n);
        for (int i = 0; i < n; i++) {
            a.x[i] -= b.x[i];
            if (a.x[i] < 0) a.x[i] += B, a.x[i + 1]--;
        }
        a.x = a.norm(a.x), a.resign();
        return a;
    }
    friend istream &operator>>(istream &is, Bigint &a)
    { string v; is >> v; a = Bigint(v); return is; }
    friend ostream &operator<<(ostream &os, Bigint a)
    { os << a.to_string(); return os; }
    friend bool operator<(Bigint a, Bigint b) {
        if (a.sgn != b.sgn) return a.sgn < b.sgn;
        if (a.x.size() != b.x.size()) {
            return a.x.size() < b.x.size();
        } else {
            for (int i = a.x.size() - 1; i >= 0; i--)
                if (a.x[i] != b.x[i]) return a.x[i] < b.x[i];
        }
        return 0;
    }
    friend bool operator>(Bigint a, Bigint b) {
        if (a.sgn != b.sgn) return a.sgn > b.sgn;
        if (a.x.size() != b.x.size()) {
            return a.x.size() > b.x.size();
        } else {
            for (int i = a.x.size() - 1; i >= 0; i--)
                if (a.x[i] != b.x[i]) return a.x[i] > b.x[i];
        }
        return 0;
    }
    friend bool operator==(const Bigint &a, const Bigint &b)
    { return a.sgn == b.sgn && a.x == b.x; }
    friend bool operator!=(const Bigint &a, const Bigint &b)
    { return a.sgn != b.sgn || a.x != b.x; }
    friend bool operator>=(const Bigint &a, const Bigint &b)
    { return a == b || a > b; }
    friend bool operator<=(const Bigint &a, const Bigint &b)
    { return a == b || a < b; }
};
Bigint abs(const Bigint &a) { return a.abs(); }
Bigint stoBigint(const string &s) { return Bigint(s); }