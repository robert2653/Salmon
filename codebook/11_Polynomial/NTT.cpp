template<int V, int P>
Mint<P> CInv = Mint<P>(V).inv();
vector<int> rev;
template<int P>
vector<Mint<P>> roots {0, 1};
template<int P>
Mint<P> findPrimitiveRoot() {
    Mint<P> i = 2;
    int k = __builtin_ctz(P - 1);
    while (true) {
        if (power(i, (P - 1) / 2) != 1) break;
        i += 1;
    }
    return power(i, (P - 1) >> k);
}
template<int P>
Mint<P> primitiveRoot = findPrimitiveRoot<P>();
template<>
Mint<998244353> primitiveRoot<998244353> {31};
template<int P>
void dft(vector<Mint<P>> &a) {
    int n = a.size();
    if (int(rev.size()) != n) {
        int k = __builtin_ctz(n) - 1;
        rev.resize(n);
        for (int i = 0; i < n; i++)
            rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
    }
    for (int i = 0; i < n; i++)
        if (rev[i] < i) swap(a[i], a[rev[i]]);
    if (roots<P>.size() < n) {
        int k = __builtin_ctz(roots<P>.size());
        roots<P>.resize(n);
        while ((1 << k) < n) {
            auto e = power(primitiveRoot<P>, 1 << (__builtin_ctz(P - 1) - k - 1));
            for (int i = 1 << (k - 1); i < (1 << k); i++) {
                roots<P>[2 * i] = roots<P>[i];
                roots<P>[2 * i + 1] = roots<P>[i] * e;
            }
            k++;
        }
    }
    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                Mint<P> u = a[i + j];
                Mint<P> v = a[i + j + k] * roots<P>[k + j];
                a[i + j] = u + v;
                a[i + j + k] = u - v;
            }
        }
    }
}
template<int P>
void idft(vector<Mint<P>> &a) {
    int n = a.size();
    reverse(a.begin() + 1, a.end());
    dft(a);
    Mint<P> inv = (1 - P) / n;
    for (int i = 0; i < n; i++) a[i] *= inv;
}
template<int P = 998244353>
struct Poly : public vector<Mint<P>> {
    using Value = Mint<P>;
    Poly() : vector<Value>() {}
    explicit Poly(int n) : vector<Value>(n) {}
    explicit Poly(const vector<Value> &a) : vector<Value>(a) {}
    Poly(const initializer_list<Value> &a) : vector<Value>(a) {}
    template<class InputIt, class = _RequireInputIter<InputIt>>
    explicit Poly(InputIt first, InputIt last) : vector<Value>(first, last) {}
    template<class F>
    explicit Poly(int n, F f) : vector<Value>(n) {
        for (int i = 0; i < n; i++)
            (*this)[i] = f(i);
    }
    Poly shift(int k) const {
        if (k >= 0) {
            auto b = *this;
            b.insert(b.begin(), k, 0);
            return b;
        } else if (this->size() <= -k) {
            return Poly();
        } else {
            return Poly(this->begin() + (-k), this->end());
        }
    }
    Poly trunc(int k) const {
        Poly f = *this;
        f.resize(k);
        return f;
    }
    friend Poly operator+(const Poly &a, const Poly &b) {
        Poly res(max(a.size(), b.size()));
        for (int i = 0; i < a.size(); i++)
            res[i] += a[i];
        for (int i = 0; i < b.size(); i++)
            res[i] += b[i];
        return res;
    }
    friend Poly operator-(const Poly &a, const Poly &b) {
        Poly res(max(a.size(), b.size()));
        for (int i = 0; i < a.size(); i++)
            res[i] += a[i];
        for (int i = 0; i < b.size(); i++)
            res[i] -= b[i];
        return res;
    }
    friend Poly operator-(const Poly &a) {
        vector<Value> res(a.size());
        for (int i = 0; i < int(res.size()); i++)
            res[i] = -a[i];
        return Poly(res);
    }
    friend Poly operator*(Poly a, Poly b) {
        if (a.size() == 0 || b.size() == 0)
            return Poly();
        if (a.size() < b.size()) swap(a, b);
        int n = 1, tot = a.size() + b.size() - 1;
        while (n < tot) n *= 2;
        if (((P - 1) & (n - 1)) != 0 || b.size() < 128) {
            Poly c(a.size() + b.size() - 1);
            for (int i = 0; i < a.size(); i++)
                for (int j = 0; j < b.size(); j++)
                    c[i + j] += a[i] * b[j];
            return c;
        }
        a.resize(n), b.resize(n);
        dft(a), dft(b);
        for (int i = 0; i < n; i++)
            a[i] *= b[i];
        idft(a);
        a.resize(tot);
        return a;
    }
    friend Poly operator*(Value a, Poly b) {
        for (int i = 0; i < int(b.size()); i++)
            b[i] *= a;
        return b;
    }
    friend Poly operator*(Poly a, Value b) {
        for (int i = 0; i < int(a.size()); i++)
            a[i] *= b;
        return a;
    }
    friend Poly operator/(Poly a, Value b) {
        for (int i = 0; i < int(a.size()); i++)
            a[i] /= b;
        return a;
    }
    Poly &operator+=(Poly b) {
        return (*this) = (*this) + b;
    }
    Poly &operator-=(Poly b) {
        return (*this) = (*this) - b;
    }
    Poly &operator*=(Poly b) {
        return (*this) = (*this) * b;
    }
    Poly &operator*=(Value b) {
        return (*this) = (*this) * b;
    }
    Poly &operator/=(Value b) {
        return (*this) = (*this) / b;
    }
    Poly deriv() const {
        if (this->empty()) return Poly();
        Poly res(this->size() - 1);
        for (int i = 0; i < this->size() - 1; i++)
            res[i] = (i + 1) * (*this)[i + 1];
        return res;
    }
    Poly integr() const {
        Poly res(this->size() + 1);
        for (int i = 0; i < this->size(); i++)
            res[i + 1] = (*this)[i] / (i + 1);
        return res;
    }
    Poly inv(int m) const {
        Poly x{(*this)[0].inv()};
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x * (Poly{2} - trunc(k) * x)).trunc(k);
        }
        return x.trunc(m);
    }
    Poly log(int m) const {
        return (deriv() * inv(m)).integr().trunc(m);
    }
    Poly exp(int m) const {
        Poly x{1};
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x * (Poly{1} - x.log(k) + trunc(k))).trunc(k);
        }
        return x.trunc(m);
    }
    Poly pow(int k, int m) const {
        int i = 0;
        while (i < this->size() && (*this)[i] == 0) i++;
        if (i == this->size() || 1LL * i * k >= m)
            return Poly(m);
        Value v = (*this)[i];
        auto f = shift(-i) * v.inv();
        return (f.log(m - i * k) * k).exp(m - i * k).shift(i * k) * power(v, k);
    }
    Poly sqrt(int m) const {
        Poly x{1};
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x + (trunc(k) * x.inv(k)).trunc(k)) * CInv<2, P>;
        }
        return x.trunc(m);
    }
    Poly mulT(Poly b) const {
        if (b.size() == 0) return Poly();
        int n = b.size();
        reverse(b.begin(), b.end());
        return ((*this) * b).shift(-(n - 1));
    }
    vector<Value> eval(vector<Value> x) const {
        if (this->size() == 0)
            return vector<Value>(x.size(), 0);
        const int n = max(x.size(), this->size());
        vector<Poly> q(4 * n);
        vector<Value> ans(x.size());
        x.resize(n);
        function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                q[p] = Poly{1, -x[l]};
            } else {
                int m = (l + r) / 2;
                build(2 * p, l, m);
                build(2 * p + 1, m, r);
                q[p] = q[2 * p] * q[2 * p + 1];
            }
        };
        build(1, 0, n);
        function<void(int, int, int, const Poly &)> work = [&](int p, int l, int r, const Poly &num) {
            if (r - l == 1) {
                if (l < int(ans.size()))
                    ans[l] = num[0];
            } else {
                int m = (l + r) / 2;
                work(2 * p, l, m, num.mulT(q[2 * p + 1]).resize(m - l));
                work(2 * p + 1, m, r, num.mulT(q[2 * p]).resize(r - m));
            }
        };
        work(1, 0, n, mulT(q[1].inv(n)));
        return ans;
    }
};
template<int P = 998244353>
Poly<P> berlekampMassey(const Poly<P> &s) {
    Poly<P> c, oldC;
    int f = -1;
    for (int i = 0; i < s.size(); i++) {
        auto delta = s[i];
        for (int j = 1; j <= c.size(); j++)
            delta -= c[j - 1] * s[i - j];
        if (delta == 0) continue;
        if (f == -1) {
            c.resize(i + 1);
            f = i;
        } else {
            auto d = oldC;
            d *= -1;
            d.insert(d.begin(), 1);
            Mint<P> df1 = 0;
            for (int j = 1; j <= d.size(); j++)
                df1 += d[j - 1] * s[f + 1 - j];
            assert(df1 != 0);
            auto coef = delta / df1;
            d *= coef;
            Poly<P> zeros(i - f - 1);
            zeros.insert(zeros.end(), d.begin(), d.end());
            d = zeros;
            auto temp = c;
            c += d;
            if (i - temp.size() > f - oldC.size()) {
                oldC = temp;
                f = i;
            }
        }
    }
    c *= -1;
    c.insert(c.begin(), 1);
    return c;
}
template<int P = 998244353>
Mint<P> linearRecurrence(Poly<P> p, Poly<P> q, ll n) {
    int m = q.size() - 1;
    while (n > 0) {
        auto newq = q;
        for (int i = 1; i <= m; i += 2)
            newq[i] *= -1;
        auto newp = p * newq;
        newq = q * newq;
        for (int i = 0; i < m; i++)
            p[i] = newp[i * 2 + n % 2];
        for (int i = 0; i <= m; i++)
            q[i] = newq[i * 2];
        n /= 2;
    }
    return p[0] / q[0];
}