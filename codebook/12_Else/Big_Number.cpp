struct BigNum { // require Mint and NTT ~idft
    int sgn;
    deque<int> x;
    BigNum() : x {0}, sgn(1) {}
    BigNum(deque<int> x, int sgn = 1) : x(norm(x)), sgn(sgn) {
        resign();
    }
    BigNum(string s) {
        if (s.empty()) {
            *this = BigNum();
        } else if (s[0] == '-') {
            sgn = -1;
            for (auto &c : s) x.push_back(c - '0');
            x.pop_front();
        } else {
            sgn = 1;
            for (auto &c : s) x.push_back(c - '0');
        }
        x = norm(x);
    }
    void resign() {
        sgn = x[0] == 0 ? 1 : sgn;
    }
    int cmp(const deque<int> &a, const deque<int> &b) const { // abs cmp
        if (a.size() != b.size()) {
            return a.size() - b.size();
        } else {
            return (a < b ? -1 : 1);
        }
    }
    deque<int> norm(deque<int> s) {
        if (s.empty()) return s = {0};
        for (int i = s.size() - 1; i >= 0; i--) {
            int c = s[i];
            s[i] = c % 10;
            c /= 10;
            if (c) {
                if (i == 0) s.push_front(c), i++;
                else s[i - 1] += c;
            }
        }
        while (s.size() > 1 && s.front() == 0) s.pop_front();
        return s;
    }
    deque<int> Add(deque<int> a, deque<int> b) {
        int i = a.size() - 1, j = b.size() - 1;
        deque<int> res;
        while (i >= 0 || j >= 0) {
            int x = i >= 0 ? a[i] : 0, y = j >= 0 ? b[j] : 0;
            res.push_front(x + y);
            i--, j--;
        }
        return res;
    }
    deque<int> Minus(deque<int> a, deque<int> b) {
        int i = a.size() - 1, j = b.size() - 1;
        deque<int> res;
        while (i >= 0) {
            int x = a[i], y = j >= 0 ? b[j] : 0;
            if (x < y) x += 10, a[i - 1]--;
            res.push_front(x - y);
            i--, j--;
        }
        return res;
    }
    vector<Z> Multiple(vector<Z> a, vector<Z> b) {
        if (a.size() < b.size()) swap(a, b);
        int n = 1, tot = a.size() + b.size() - 1;
        while (n < tot) n *= 2;
        if (((P - 1) & (n - 1)) != 0 || b.size() < 128) {
            vector<Z> c(a.size() + b.size() - 1);
            for (int i = 0; i < a.size(); i++)
                for (int j = 0; j < b.size(); j++)
                    c[i + j] += a[i] * b[j];
            return c;
        }
        a.resize(n), b.resize(n);
        dft(a), dft(b);
        for (int i = 0; i < n; i++) a[i] *= b[i];
        idft(a);
        a.resize(tot);
        return a;
    }
    BigNum operator-() const {
        return BigNum(x, -sgn);
    }
    BigNum &operator+=(const BigNum &rhs) & {
        if (sgn == 1) {
            if (rhs.sgn == -1) {
                if (cmp(x, rhs.x) < 0) {
                    sgn = -1, x = Minus(rhs.x, x);
                } else {
                    sgn = 1, x = Minus(x, rhs.x);
                }
            } else {
                sgn = 1, x = Add(x, rhs.x);
            }
        } else {
            if (rhs.sgn == -1) {
                sgn = -1, x = Add(x, rhs.x);
            } else {
                if (cmp(x, rhs.x) <= 0) {
                    sgn = 1, x = Minus(rhs.x, x);
                } else {
                    sgn = -1, x = Minus(x, rhs.x);
                }
            }
        }
        x = norm(x), resign();
        return *this;
    }
    BigNum &operator-=(const BigNum &rhs) & {
        return *this += -rhs;
    }
    BigNum &operator*=(const BigNum &rhs) & {
        vector<Z> a(x.rbegin(), x.rend()), b(rhs.x.rbegin(), rhs.x.rend()), c = Multiple(a, b);
        x = norm(deque<int>(c.rbegin(), c.rend()));
        sgn *= rhs.sgn, resign();
        return *this;
    }
    friend BigNum operator+(BigNum lhs, BigNum rhs) {
        return lhs += rhs;
    }
    friend BigNum operator-(BigNum lhs, BigNum rhs) {
        return lhs -= rhs;
    }
    friend BigNum operator*(BigNum lhs, BigNum rhs) {
        return lhs *= rhs;
    }
    friend istream &operator>>(istream &is, BigNum &a) {
        string v; is >> v; a = BigNum(v); return is;
    }
    friend ostream &operator<<(ostream &os, const BigNum &a) {
        os << (a.sgn == 1 ? "" : "-");
        for (auto x : a.x) os << x;
        return os;
    }
};