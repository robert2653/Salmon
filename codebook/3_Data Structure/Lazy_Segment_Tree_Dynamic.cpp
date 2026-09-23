template<class Info, class Tag> struct LazySegmentTreeDynamic {
	struct Node {
		Info info = Info();
		Tag tag = Tag();
		bool isLazy = false;
		int lc = 0, rc = 0;
	};
	int n;
	vector<Node> nd;
	LazySegmentTreeDynamic(int n) : n(n), nd(1) {}
	int generate() {
		nd.emplace_back();
		return nd.size() - 1;
	}
	void pull(int p) { nd[p].info = nd[nd[p].lc].info + nd[nd[p].rc].info; }
	void apply(int p, int l, int r, const Tag &t) {
		nd[p].info.apply(t, l, r);
		nd[p].tag.apply(t);
		nd[p].isLazy = true;
	}
	void push(int p, int l, int r) {
		if (!nd[p].isLazy) return;
		int m = (l + r) / 2;
		if (nd[p].lc == 0) nd[p].lc = generate();
		if (nd[p].rc == 0) nd[p].rc = generate();
		apply(nd[p].lc, l, m, nd[p].tag);
		apply(nd[p].rc, m, r, nd[p].tag.offset(m - l));
		nd[p].tag = Tag();
		nd[p].isLazy = false;
	}
	int modify(int x, const Info &i, int rt = 0) { return modify(rt, 0, n, x, i); }
	int modify(int p, int l, int r, int x, const Info &i) {
		if (p == 0) p = generate();
		if (r - l == 1) {
			nd[p].info = i;
			return p;
		}
		push(p, l, r);
		int m = (l + r) / 2;
		if (x < m) nd[p].lc = modify(nd[p].lc, l, m, x, i);
		else nd[p].rc = modify(nd[p].rc, m, r, x, i);
		pull(p);
		return p;
	}
	Info query(int ql, int qr, int rt = 0) { return query(rt, 0, n, ql, qr); }
	Info query(int p, int l, int r, int ql, int qr) {
		if (l >= qr || r <= ql || p == 0) return Info();
		if (ql <= l && r <= qr) return nd[p].info;
		push(p, l, r);
		int m = (l + r) / 2;
		return query(nd[p].lc, l, m, ql, qr) + query(nd[p].rc, m, r, ql, qr);
	}
	int rangeApply(int ql, int qr, const Tag &t, int rt = 0) { return rangeApply(rt, 0, n, ql, qr, t); }
	int rangeApply(int p, int l, int r, int ql, int qr, const Tag &t) {
		if (l >= qr || r <= ql) return p;
		if (p == 0) p = generate();
		if (ql <= l && r <= qr) {
			apply(p, l, r, t.offset(l - ql));
			return p;
		}
		push(p, l, r);
		int m = (l + r) / 2;
		nd[p].lc = rangeApply(nd[p].lc, l, m, ql, qr, t);
		nd[p].rc = rangeApply(nd[p].rc, m, r, ql, qr, t);
		pull(p);
		return p;
	}
	template<class F> int findFirst(int ql, int qr, F &&f, int rt = 0) {
		return findFirst(rt, 0, n, ql, qr, f);
	}
	template<class F> int findFirst(int p, int l, int r, int ql, int qr, F &&f) {
		if (l >= qr || r <= ql || p == 0 || !f(nd[p].info)) return -1;
		if (r - l == 1) return l;
		int m = (l + r) / 2;
		push(p, l, r);
		int res = findFirst(nd[p].lc, l, m, ql, qr, f);
		if (res != -1) return res;
		return findFirst(nd[p].rc, m, r, ql, qr, f);
	}
};