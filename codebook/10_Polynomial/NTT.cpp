template<int P = 998244353, int G = 3>
struct Poly : public vector<Mint<P>> {
    using Z = Mint<P>;
    static vector<int> rev;
    static vector<Z> w;
    static void ntt(vector<Z> &a, bool inv = false) {
        int n = a.size();
        if (rev.size() != n) {
            int k = __builtin_ctz(n) - 1;
            rev.resize(n);
            for (int i = 0; i < n; i++) rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
        }
        for (int i = 0; i < n; i++) if (rev[i] < i) swap(a[i], a[rev[i]]);
        if (w.size() < n) {
            int k = __builtin_ctz(w.size());
            w.resize(n);
            while ((1 << k) < n) {
                Z u = power(Z(G), (P - 1) >> (k + 1));
                for (int i = 1 << (k - 1); i < (1 << k); i++) {
                    w[i * 2] = w[i];
                    w[i * 2 + 1] = w[i] * u;
                }
                k++;
            }
        }
        for (int k = 1; k < n; k *= 2) {
            for (int i = 0; i < n; i += 2 * k) {
                for (int j = 0; j < k; j++) {
                    Z u = a[i + j], v = a[i + j + k] * w[k + j];
                    a[i + j] = u + v; a[i + j + k] = u - v;
                }
            }
        }
        if (inv) {
            reverse(a.begin() + 1, a.end());
            Z inv_n = Z(n).inv();
            for (auto &x : a) x *= inv_n;
        }
    }
    explicit Poly(int n = 0) : vector<Z>(n) {}
    Poly(const vector<Z> &a) : vector<Z>(a) {}
    Poly(const initializer_list<Z> &a) : vector<Z>(a) {}
    template<class InputIt, class = _RequireInputIter<InputIt>>
    Poly(InputIt first, InputIt last) : vector<Z>(first, last) {}
    Poly operator-() const {
        vector<Z> res(this->size());
        for (int i = 0; i < int(res.size()); i++) res[i] = -(*this)[i];
        return Poly(res);
    }
    friend Poly operator+(Poly a, Poly b) {
        a.resize(max(a.size(), b.size()));
        for (int i = 0; i < b.size(); i++) a[i] += b[i];
        return a;
    }
    friend Poly operator-(Poly a, Poly b) {
        a.resize(max(a.size(), b.size()));
        for (int i = 0; i < b.size(); i++) a[i] -= b[i];
        return a;
    }
    friend Poly operator*(Poly a, Poly b) {
        if (a.empty() || b.empty()) return Poly();
        if (a.size() < b.size()) swap(a, b);
        int n = 1, tot = a.size() + b.size() - 1;
        while (n < tot) n *= 2;
        a.resize(n), b.resize(n);
        ntt(a), ntt(b);
        for (int i = 0; i < n; i++) a[i] *= b[i];
        ntt(a, true);
        a.resize(tot);
        return a;
    }
    friend Poly operator*(Poly a, Z x) {
        for (int i = 0; i < int(a.size()); i++) a[i] *= x;
        return a;
    }
    friend Poly operator/(Poly a, Z x) {
        for (int i = 0; i < int(a.size()); i++) a[i] /= x;
        return a;
    }
    Poly &operator+=(Poly a)
    { return (*this) = (*this) + a; }
    Poly &operator-=(Poly a)
    { return (*this) = (*this) - a; }
    Poly &operator*=(Poly a)
    { return (*this) = (*this) * a; }
    Poly &operator*=(Z a)
    { return (*this) = (*this) * a; }
    Poly &operator/=(Z a)
    { return (*this) = (*this) / a; }
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
        Poly f = *this; f.resize(k); return f;
    }
    Poly deriv() const {
        if (this->empty()) return Poly();
        Poly res(this->size() - 1);
        for (int i = 0; i < this->size() - 1; i++)
            res[i] = (*this)[i + 1] * (i + 1);
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
    Poly pow(ll k, int m) const {
        if (k == 0) { Poly res(m); res[0] = 1; return res; }
        int i = 0;
        while (i < this->size() && (*this)[i] == 0) i++;
        if (i == this->size() || i > 0 && k > (m - 1) / i) return Poly(m);
        Z v = (*this)[i];
        auto f = shift(-i) * v.inv();
        return (f.log(m - i * k) * Z(k)).exp(m - i * k).shift(i * k) * power(v, k);
    }
    Poly sqrt(int m) const { // need quadraticResidue
        int k = 0;
        while (k < this->size() && (*this)[k] == 0) k++; // 找前導零
        if (k == this->size()) return Poly(m); // 全零多項式
        if (k % 2 != 0) return Poly(); // 無解: 最低次項為奇數
        int s = quadraticResidue((*this)[k]);
        if (s == -1) return Poly(); // 無解: 係數無平方根
        int oft = k / 2, r = m - oft;
        if (r <= 0) return Poly(m);
        Poly h = this->shift(-k) * (*this)[k].inv(), g{1};
        for (int i = 1; i < r; i <<= 1) {
            int len = i << 1;
            g = (g + h.trunc(len) * g.inv(len)).trunc(len) / 2;
        }
        g.resize(r);
        g = (g * Z(s)).shift(oft).trunc(m);
        return g;
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
    Poly mulT(Poly b) const {
        if (b.empty()) return Poly();
        int n = b.size();
        reverse(b.begin(), b.end());
        return ((*this) * b).shift(-(n - 1));
    }
    vector<Z> eval(vector<Z> x) const {
        if (this->size() == 0) return vector<Z>(x.size(), 0);
        const int n = max(x.size(), this->size());
        vector<Poly> q(4 * n);
        vector<Z> ans(x.size());
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
                if (l < int(ans.size())) ans[l] = num[0];
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
template<int P, int G> vector<int> Poly<P, G>::rev;
template<int P, int G> vector<Mint<P>> Poly<P, G>::w = {0, 1};