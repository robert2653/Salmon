template<class Info> struct SegmentTreeDynamic {
	struct Node {
		Info info = Info();
		int lc = 0, rc = 0;
	};
	int n;
	vector<Node> nd;
	SegmentTreeDynamic(int n) : n(n), nd(1) {}
	int generate() {
		nd.emplace_back();
		return nd.size() - 1;
	}
	void pull(int p) { nd[p].info = nd[nd[p].lc].info + nd[nd[p].rc].info; }
	int modify(int x, const Info &i, int rt = 0) { return modify(rt, 0, n, x, i); }
	int modify(int p, int l, int r, int x, const Info &i) {
		if (p == 0) p = generate();
		if (r - l == 1) {
			nd[p].info = i; // leaf modify/add
			return p;
		}
		int m = (l + r) / 2;
		if (x < m) nd[p].lc = modify(nd[p].lc, l, m, x, i);
		else nd[p].rc = modify(nd[p].rc, m, r, x, i);
		pull(p);
		return p;
	}
	int merge(int p, int q) { return merge(p, q, 0, n); }
	int merge(int p, int q, int l, int r) {
		if (p == 0 || q == 0) return p + q;
		if (r - l == 1) {
			nd[p].info = nd[p].info + nd[q].info; // leaf add
			return p;
		}
		int m = (l + r) / 2;
		nd[p].lc = merge(nd[p].lc, nd[q].lc, l, m);
		nd[p].rc = merge(nd[p].rc, nd[q].rc, m, r);
		pull(p);
		return p;
	}
	Info query(int ql, int qr, int rt = 0) { return query(rt, 0, n, ql, qr); }
	Info query(int p, int l, int r, int ql, int qr) {
		if (l >= qr || r <= ql || p == 0) return Info();
		if (ql <= l && r <= qr) return nd[p].info;
		int m = (l + r) / 2;
		return query(nd[p].lc, l, m, ql, qr) + query(nd[p].rc, m, r, ql, qr);
	}
	template<class F> int findFirst(int ql, int qr, F &&f, int rt = 0) {
		return findFirst(rt, 0, n, ql, qr, f);
	}
	template<class F> int findFirst(int p, int l, int r, int ql, int qr, F &&f) {
		if (l >= qr || r <= ql || p == 0 || !f(nd[p].info)) return -1;
		if (r - l == 1) return l;
		int m = (l + r) / 2;
		int res = findFirst(nd[p].lc, l, m, ql, qr, f);
		if (res != -1) return res;
		return findFirst(nd[p].rc, m, r, ql, qr, f);
	}
};