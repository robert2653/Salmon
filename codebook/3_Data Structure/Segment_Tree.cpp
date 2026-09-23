template<class Info> struct SegmentTree {
	int n;
	vector<Info> info;
	SegmentTree(int n) : n(n), info(4 << __lg(n)) {}
	SegmentTree(const vector<Info> &v) : n(v.size()), info(4 << __lg(n)) {
		auto build = [&](auto &&self, int p, int l, int r) {
			if (r - l == 1) {
				info[p] = v[l];
				return;
			}
			int m = (l + r) / 2;
			self(self, 2 * p, l, m);
			self(self, 2 * p + 1, m, r);
			pull(p);
		};
		build(build, 1, 0, n);
	}
	void pull(int p) { info[p] = info[2 * p] + info[2 * p + 1]; }
	void modify(int x, const Info &i) { modify(1, 0, n, x, i); }
	void modify(int p, int l, int r, int x, const Info &i) {
		if (r - l == 1) {
			info[p] = i;
			return;
		}
		int m = (l + r) / 2;
		if (x < m) modify(2 * p, l, m, x, i);
		else modify(2 * p + 1, m, r, x, i);
		pull(p);
	}
	Info query(int ql, int qr) { return query(1, 0, n, ql, qr); }
	Info query(int p, int l, int r, int ql, int qr) {
		if (qr <= l || ql >= r) return Info();
		if (ql <= l && r <= qr) return info[p];
		int m = (l + r) / 2;
		return query(2 * p, l, m, ql, qr) + query(2 * p + 1, m, r, ql, qr);
	}
	template<class F> int findFirst(int ql, int qr, F &&f) {
		return findFirst(1, 0, n, ql, qr, f);
	} // 若要找 last，先右子樹遞迴即可
	template<class F> int findFirst(int p, int l, int r, int ql, int qr, F &&f) {
		if (qr <= l || ql >= r) return -1;
		if (ql <= l && r <= qr && !f(info[p])) return -1;
		if (r - l == 1) return l;
		int m = (l + r) / 2;
		int res = findFirst(2 * p, l, m, ql, qr, f);
		if (res == -1) res = findFirst(2 * p + 1, m, r, ql, qr, f);
		return res;
	}
};
struct Info {};
Info operator+(const Info &a, const Info &b) {
	Info c;
	return c;
}