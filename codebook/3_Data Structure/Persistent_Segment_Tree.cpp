template<class Info> struct PST {
	struct Node {
		Info info = Info();
		int lc = 0, rc = 0;
	};
	int n;
	vector<Node> nd;
	vector<int> rt;
	PST(int n) : n(n), nd(1), rt(1) {}
	PST(const vector<Info> &v) : n(v.size()), nd(1) {
		auto build = [&](auto &&self, int l, int r) -> int {
			int p = generate();
			if (r - l == 1) {
				nd[p].info = v[l];
				return p;
			}
			int m = (l + r) / 2;
			int lc = self(self, l, m);
			int rc = self(self, m, r);
			nd[p].lc = lc;
			nd[p].rc = rc;
			pull(nd[p]);
			return p;
		};
		rt.push_back(build(build, 0, n));
	}
	void pull(Node &p) { p.info = nd[p.lc].info + nd[p.rc].info; }
	int copy(int p) { // copy 一個 node
		nd.push_back(nd[p]);
		return nd.size() - 1;
	}
	int generate() { // 創立新的 node
		nd.emplace_back();
		return nd.size() - 1;
	}
	void modify(int x, const Info &i, int ver = 0) {
		if (int(rt.size()) <= ver) rt.resize(ver + 1);
		rt[ver] = modify(x, i, 0, n, rt[ver]);
	}
	int modify(int x, const Info &i, int l, int r, int p) {
		p = p ? copy(p) : generate();
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
		pull(nd[p]);
		return p;
	}
	Info query(int ql, int qr, int ver = 0)
	{ return query(ql, qr, 0, n, rt[ver]); }
	Info query(int ql, int qr, int l, int r, int p) {
		if (l >= qr || r <= ql || p == 0) return Info();
		if (ql <= l && r <= qr) return nd[p].info;
		int m = (l + r) / 2;
		return query(ql, qr, l, m, nd[p].lc) + query(ql, qr, m, r, nd[p].rc);
	}
	void createVersion(int ver) { rt.push_back(rt[ver]); }
};