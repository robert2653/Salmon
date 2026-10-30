// 應用: dp(i) = h(i) + min/max(A(j)X(i) + B(j)), for j <= r(i)
//        y    =  c   +          m  x   +   b
template<class T> struct Line {
	static inline vector<ll> pts; // 離散化, 記得 clear
	T m, b;
	T eval(ll x) const {
		return m * pts[x] + b;
	}
};
template<class T, class F = less<T>> struct LiChaoSeg {
	F cmp = F();
	static constexpr T inf = max(numeric_limits<T>::lowest() / 2, numeric_limits<T>::max() / 2, F());
	struct Node {
		Line<T> line{0, inf};
		int l = -1, r = -1;
	};
	ll n;
	vector<Node> nd;
	LiChaoSeg(ll n) : n(n) { newNode(); }
	void addLine(Line<T> line) { update(0, 0, n, line); }
	void rangeAddLine(Line<T> line, ll ql, ll qr) { rangeUpdate(0, 0, n, ql, qr, line); }
	T query(ll x) { return query(x, 0, 0, n); }
private:
	int newNode() {
		nd.emplace_back();
		return nd.size() - 1;
	}
	void update(int p, ll l, ll r, Line<T> line) {
		ll m = (l + r) / 2;
		bool left = cmp(line.eval(l), nd[p].line.eval(l));
		bool mid = cmp(line.eval(m), nd[p].line.eval(m));
		if (mid) swap(nd[p].line, line);
		if (r - l == 1) return;
		if (left != mid) {
			if (nd[p].l == -1) nd[p].l = newNode();
			update(nd[p].l, l, m, line);
		} else {
			if (nd[p].r == -1) nd[p].r = newNode();
			update(nd[p].r, m, r, line);
		}
	}
	void rangeUpdate(int p, ll l, ll r, ll ql, ll qr, Line<T> line) {
		if (r <= ql || l >= qr) return;
		if (ql <= l && r <= qr) return update(p, l, r, line);
		if (nd[p].l == -1) nd[p].l = newNode();
		if (nd[p].r == -1) nd[p].r = newNode();
		ll m = (l + r) / 2;
		rangeUpdate(nd[p].l, l, m, ql, qr, line);
		rangeUpdate(nd[p].r, m, r, ql, qr, line);
	}
	T query(ll x, int p, ll l, ll r) {
		if (p == -1) return inf;
		ll m = (l + r) / 2;
		if (x < m) return min(nd[p].line.eval(x), query(x, nd[p].l, l, m), cmp);
		else return min(nd[p].line.eval(x), query(x, nd[p].r, m, r), cmp);
	}
};
auto &pts = Line<ld>::pts; // shorten