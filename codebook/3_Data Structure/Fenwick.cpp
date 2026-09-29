template<class T> struct Fenwick {
	int n;
	vector<T> a;
	Fenwick(int n) : n(n), a(n) {}
	void add(int x, const T &v) {
		for (x++; x <= n; x += x & -x) a[x - 1] = a[x - 1] + v;
	}
	T sum(int x) {
		T v{};
		for (; x > 0; x -= x & -x) v = v + a[x - 1];
		return v;
	}
	T rangeSum(int l, int r) { return sum(r) - sum(l); } /*
	int select(const T &k, int start = 0) {
		// 找到最小的 x, 使得 sum(x + 1) - sum(start) > k
		// prefix sum 要有單調性
		int x = 0;
		T cur = -sum(start);
		for (int i = 1 << __lg(n); i > 0; i /= 2)
			if (x + i <= n && cur + a[x + i - 1] <= k)
				x += i, cur = cur + a[x - 1];
		return x;
	} */ // 8e1de2
}; // 9083e4
template<class T> struct Fenwick2D {
	int n, m;
	vector<vector<T>> a;
	Fenwick2D(int n, int m) : n(n), m(m), a(n, vector<T>(m)) {}
	void add(int x, int y, const T &v) {
		for (int i = x + 1; i <= n; i += i & -i)
			for (int j = y + 1; j <= m; j += j & -j)
				a[i - 1][j - 1] = a[i - 1][j - 1] + v;
	}
	T sum(int x, int y) {
		T v{};
		for (int i = x; i > 0; i -= i & -i)
			for (int j = y; j > 0; j -= j & -j)
				v = v + a[i - 1][j - 1];
		return v;
	}
	T rangeSum(int x1, int y1, int x2, int y2)
	{ return sum(x2, y2) - sum(x1, y2) - sum(x2, y1) + sum(x1, y1); }
}; // a71e39
template<class T> struct RangeFenwick {
	int n;
	vector<T> d, di;
	RangeFenwick(int n) : n(n), d(n), di(n) {}
	void add(int x, const T &v) {
		T vi = v * (x + 1);
		for (int i = x + 1; i <= n; i += i & -i)
			d[i - 1] = d[i - 1] + v, di[i - 1] = di[i - 1] + vi;
	}
	void rangeAdd(int l, int r, const T &v) { add(l, v), add(r, -v); }
	T sum(int x) {
		T v{};
		for (int i = x; i > 0; i -= i & -i)
			v = v + T(x + 1) * d[i - 1] - di[i - 1];
		return v;
	}
	T rangeSum(int l, int r) { return sum(r) - sum(l); } /*
	int select(const T &k, int start = 0) {
		int x = 0;
		T cur{}, curi{}, sub = sum(start);
		for (int i = 1 << __lg(n); i; i /= 2) {
			if (x + i <= n && T(x + i + 1) * (cur + d[x + i - 1]) - (curi + di[x + i - 1]) - sub <= k) {
				x += i;
				cur = cur + d[x - 1], curi = curi + di[x - 1];
			}
		}
		return x;
	} */ // e93ec7
}; // 03784e
template<class T> struct RangeFenwick2D {
	int n, m;
	vector<vector<T>> d, di, dj, dij;
	RangeFenwick2D(int n, int m) : n(n), m(m), dij(n, vector<T>(m))
	{ d = di = dj = dij; }
	void add(int x, int y, const T &v) {
		T vi = v * (x + 1), vj = v * (y + 1);
		T vij = v * (x + 1) * (y + 1);
		for (int i = x + 1; i <= n; i += i & -i)
			for (int j = y + 1; j <= m; j += j & -j) {
				d[i - 1][j - 1] = d[i - 1][j - 1] + v;
				di[i - 1][j - 1] = di[i - 1][j - 1] + vi;
				dj[i - 1][j - 1] = dj[i - 1][j - 1] + vj;
				dij[i - 1][j - 1] = dij[i - 1][j - 1] + vij;
			}
	}
	void rangeAdd(int x1, int y1, int x2, int y2, const T &v) {
		add(x1, y1, v), add(x2, y2, v);
		add(x1, y2, -v), add(x2, y1, -v);
	}
	T sum(int x, int y) {
		T v{};
		for (int i = x; i > 0; i -= i & -i)
			for (int j = y; j > 0; j -= j & -j)
				v = v + (x + 1) * (y + 1) * d[i - 1][j - 1]
				- (y + 1) * di[i - 1][j - 1]
				- (x + 1) * dj[i - 1][j - 1]
				+ dij[i - 1][j - 1];
		return v;
	}
	T rangeSum(int x1, int y1, int x2, int y2)
	{ return sum(x2, y2) - sum(x1, y2) - sum(x2, y1) + sum(x1, y1); }
}; // 60ea46