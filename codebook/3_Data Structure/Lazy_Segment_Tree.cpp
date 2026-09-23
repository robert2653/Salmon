template<class Info, class Tag> struct LazySegmentTree {
	int n;
	vector<Info> info;
	vector<Tag> tag;
	LazySegmentTree(int n) : n(n), info(4 << __lg(n)), tag(4 << __lg(n)) {}
	LazySegmentTree(const vector<Info> &v) : n(v.size()), info(4 << __lg(n)), tag(4 << __lg(n)) {
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
	void apply(int p, int l, int r, const Tag &t) {
		info[p].apply(t, l, r);
		tag[p].apply(t);
	}
	void push(int p, int l, int r) {
		int m = (l + r) / 2;
		apply(2 * p, l, m, tag[p]);
		apply(2 * p + 1, m, r, tag[p].offset(m - l)); // tag 可位移 (m - l)
		tag[p] = Tag();
	}
	void modify(int x, const Info &i) { modify(1, 0, n, x, i); }
	void modify(int p, int l, int r, int x, const Info &i) {
		if (r - l == 1) {
			info[p] = i;
			return;
		}
		int m = (l + r) / 2;
		push(p, l, r);
		if (x < m) modify(2 * p, l, m, x, i);
		else modify(2 * p + 1, m, r, x, i);
		pull(p);
	}
	Info query(int ql, int qr) { return query(1, 0, n, ql, qr); }
	Info query(int p, int l, int r, int ql, int qr) {
		if (qr <= l || ql >= r) return Info();
		if (ql <= l && r <= qr) return info[p];
		int m = (l + r) / 2;
		push(p, l, r);
		return query(2 * p, l, m, ql, qr) + query(2 * p + 1, m, r, ql, qr);
	}
	void rangeApply(int ql, int qr, const Tag &t) { rangeApply(1, 0, n, ql, qr, t); }
	void rangeApply(int p, int l, int r, int ql, int qr, const Tag &t) {
		if (qr <= l || ql >= r) return;
		if (ql <= l && r <= qr) {
			apply(p, l, r, t.offset(l - ql)); // tag 可位移 (l - ql)
			return;
		}
		int m = (l + r) / 2;
		push(p, l, r);
		rangeApply(2 * p, l, m, ql, qr, t);
		rangeApply(2 * p + 1, m, r, ql, qr, t);
		pull(p);
	} // da4291 (without findFirst)
	template<class F> int findFirst(int ql, int qr, F &&f) {
		return findFirst(1, 0, n, ql, qr, f);
	} // 若要找 last，先右子樹遞迴即可
	template<class F> int findFirst(int p, int l, int r, int ql, int qr, F &&f) {
		if (qr <= l || ql >= r || !f(info[p])) return -1;
		if (r - l == 1) return l;
		int m = (l + r) / 2;
		push(p, l, r);
		int res = findFirst(2 * p, l, m, ql, qr, f);
		if (res == -1) res = findFirst(2 * p + 1, m, r, ql, qr, f);
		return res;
	}
};
struct Tag { // 有些 Tag 不用 push 例如 sweepLine
	void apply(const Tag &t) & {}
	Tag offset(int d) const { return *this; }
};
struct Info {
	void apply(const Tag &t, int l, int r) & {} /*
	Info &operator=(const Info &i) & {
		// do something... 部分 assignment 使用
		return *this;
	} */
};
Info operator+(const Info &a, const Info &b) {
	Info c;
	return c;
}