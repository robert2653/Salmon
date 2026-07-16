template<class Info> struct SegmentTreeDynamic {
	struct Node {
		Info info = Info();
		int lc = 0, rc = 0;
	};
	int n, rt;
	vector<Node> nd;
	SegmentTreeDynamic(int n) : n(n), rt(0), nd(1) {}
	int generate() {
		nd.emplace_back();
		return nd.size() - 1;
	}
	void pull(int p) { nd[p].info = nd[nd[p].lc].info + nd[nd[p].rc].info; }
	void modify(int x, const Info &i) { rt = modify(x, i, 0, n, rt); }
	int modify(int x, const Info &i, int l, int r, int p) {
		if (p == 0) p = generate();
		if (r - l == 1) {
			nd[p].info = i;
			return p;
		}
		int m = (l + r) / 2;
		if (x < m) {
			int y = modify(x, i, l, m, nd[p].lc);
			nd[p].lc = y;
		} else {
			int y = modify(x, i, m, r, nd[p].rc);
			nd[p].rc = y;
		}
		pull(p);
		return p;
	}
	Info query(int ql, int qr) { return query(ql, qr, 0, n, rt); }
	Info query(int ql, int qr, int l, int r, int p) {
		if (l >= qr || r <= ql || p == 0) return Info();
		if (ql <= l && r <= qr) return nd[p].info;
		int m = (l + r) / 2;
		return query(ql, qr, l, m, nd[p].lc) + query(ql, qr, m, r, nd[p].rc);
	}
	template<class T> int findFirst(int ql, int qr, T &&f) { return findFirst(ql, qr, f, 0, n, rt); }
	template<class T> int findFirst(int ql, int qr, T &&f, int l, int r, int p) {
		if (l >= qr || r <= ql || p == 0 || !f(nd[p].info)) return -1;
		if (r - l == 1) return l;
		int m = (l + r) / 2;
		int res = findFirst(ql, qr, f, l, m, nd[p].lc);
		if (res != -1) return res;
		return findFirst(ql, qr, f, m, r, nd[p].rc);
	}
};
struct Info {};
Info operator+(const Info &a, const Info &b) {
	Info c;
	return c;
}