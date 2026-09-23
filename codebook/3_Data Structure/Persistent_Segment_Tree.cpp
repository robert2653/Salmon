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
			int p = copy(0);
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
	int copy(int p) {
		nd.push_back(nd[p]);
		return nd.size() - 1;
	}
	void modify(int x, const Info &i, int ver = 0) {
		assert(rt.size() > ver);
		rt[ver] = modify(rt[ver], 0, n, x, i);
	}
	int modify(int p, int l, int r, int x, const Info &i) {
		p = copy(p);
		if (r - l == 1) {
			nd[p].info = i;
			return p;
		}
		int m = (l + r) / 2;
		if (x < m) nd[p].lc = modify(nd[p].lc, l, m, x, i);
		else nd[p].rc = modify(nd[p].rc, m, r, x, i);
		pull(nd[p]);
		return p;
	}
	Info query(int ql, int qr, int ver = 0) {
		return query(rt[ver], 0, n, ql, qr);
	}
	Info query(int p, int l, int r, int ql, int qr) {
		if (l >= qr || r <= ql || p == 0) return Info();
		if (ql <= l && r <= qr) return nd[p].info;
		int m = (l + r) / 2;
		return query(nd[p].lc, l, m, ql, qr) + query(nd[p].rc, m, r, ql, qr);
	}
	int createVersion(int ver) {
		rt.push_back(rt[ver]);
		return rt.size() - 1;
	}
};