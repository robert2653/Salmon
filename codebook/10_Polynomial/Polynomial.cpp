struct Poly : public vector<Mint<P>> {
	using Z = Mint<P>;
	using vector::vector;
	Poly(const vector<Z> &a) : vector<Z>(a) {}
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
		return conv(a, b, G);
	}
	friend Poly operator*(Poly a, Z x) {
		for (int i = 0; i < a.size(); i++) a[i] *= x;
		return a;
	}
	friend Poly operator/(Poly a, Z x) {
		for (int i = 0; i < a.size(); i++) a[i] /= x;
		return a;
	}
	Poly &operator+=(Poly a) { return *this = *this + a; }
	Poly &operator-=(Poly a) { return *this = *this - a; }
	Poly &operator*=(Poly a) { return *this = *this * a; }
	Poly &operator*=(Z a) { return *this = *this * a; }
	Poly &operator/=(Z a) { return *this = *this / a; }
	// 53f01c
	Poly shift(int k) const { // 乘 x^k, k < 0 時捨去低次項
		if (k >= 0) {
			auto b = *this;
			b.insert(b.begin(), k, 0);
			return b;
		} else if (this->size() <= -k) {
			return Poly();
		} else {
			return Poly(this->begin() + (-k), this->end());
		}
	} // e6ab95
	Poly trunc(int k) const {
		Poly f = *this; f.resize(k); return f;
	} // 217dbc
	Poly deriv() const {
		if (this->empty()) return Poly();
		Poly res(this->size() - 1);
		for (int i = 0; i < this->size() - 1; i++)
			res[i] = (*this)[i + 1] * (i + 1);
		return res;
	} // cceaf0
	Poly integr() const {
		Poly res(this->size() + 1);
		for (int i = 0; i < this->size(); i++)
			res[i + 1] = (*this)[i] / (i + 1);
		return res;
	} // f86ffe
	// 以下帶 m 的都是 mod x^m, 結果只留前 m 項
	Poly inv(int m) const { // 1 / f, need f[0] != 0
		Poly x{(*this)[0].inv()};
		int k = 1;
		while (k < m) {
			k *= 2;
			x = (x * (Poly{2} - trunc(k) * x)).trunc(k);
		}
		return x.trunc(m);
	} // 8287e6
	Poly log(int m) const { // need f[0] = 1
		return (deriv() * inv(m)).integr().trunc(m);
	} // bfd979
	Poly pow(ll k, int m) const { // f^k, f[0] 可為 0
		if (k == 0) { Poly res(m); res[0] = 1; return res; }
		int i = 0;
		while (i < this->size() && (*this)[i].x == 0) i++;
		if (i == this->size() || i > 0 && k > (m - 1) / i) return Poly(m);
		Z v = (*this)[i];
		auto f = shift(-i) * v.inv();
		return (f.log(m - i * k) * Z(k)).exp(m - i * k).shift(i * k) * power(v, k);
	} // 23cb76
	Poly sqrt(int m) const { // need quadraticResidue, 無解回傳空
		int k = 0;
		while (k < this->size() && (*this)[k].x == 0) k++; // 找前導零
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
	} // 1a3aea
	Poly exp(int m) const { // need f[0] = 0
		Poly x{1};
		int k = 1;
		while (k < m) {
			k *= 2;
			x = (x * (Poly{1} - x.log(k) + trunc(k))).trunc(k);
		}
		return x.trunc(m);
	} // 78baba
	// 轉置乘法, res[i] = sum_j f[i + j] * b[j], res.size() = f.size()
	Poly mulT(Poly b) const {
		if (b.empty()) return Poly();
		int n = b.size();
		reverse(b.begin(), b.end());
		return ((*this) * b).shift(-(n - 1));
	} // f7c257
	// 多點求值, 回傳 f(x[0]), f(x[1]), ..., O(n log^2 n)
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
				work(2 * p, l, m, num.mulT(q[2 * p + 1]).trunc(m - l));
				work(2 * p + 1, m, r, num.mulT(q[2 * p]).trunc(r - m));
			}
		};
		work(1, 0, n, mulT(q[1].inv(n)));
		return ans;
	} // 9698d5
};