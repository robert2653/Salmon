struct RollbackDSU {
	int n;
	vector<int> f, siz, stk;
	RollbackDSU(int n) : n(n), f(n), siz(n, 1)
	{ iota(f.begin(), f.end(), 0); }
	int find(int x) { return x == f[x] ? x : find(f[x]); }
	bool same(int x, int y) { return find(x) == find(y); }
	bool merge(int x, int y) {
		x = find(x), y = find(y);
		if (x == y) return false;
		if (siz[x] < siz[y]) swap(x, y);
		siz[x] += siz[y];
		f[y] = x;
		n--;
		stk.push_back(y);
		return true;
	}
	void undo(int x) {
		while (stk.size() > x) {
			int y = stk.back();
			stk.pop_back();
			n++;
			siz[f[y]] -= siz[y];
			f[y] = y;
		}
	}
	int size(int x) { return siz[find(x)]; }
};