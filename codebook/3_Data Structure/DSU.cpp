template<class T = ll> struct PotDSU {
	vector<int> f, siz;
	vector<T> d; // pot[i] - pot[f[i]]
	PotDSU(int n) : f(n), siz(n, 1), d(n) {
		iota(f.begin(), f.end(), 0);
	}
	int find(int x) {
		if (x != f[x]) {
			int y = f[x];
			f[x] = find(y);
			d[x] += d[y];
		}
		return f[x];
	}
	bool same(int a, int b) { return find(a) == find(b); }
	bool merge(int a, int b, T w) {
		// P[b] - P[a] = w, P[x] = P[rx] + d[x]
		int ra = find(a), rb = find(b);
		if (ra == rb) return d[b] - d[a] == w;
		if (siz[ra] < siz[rb]) {
			swap(a, b);
			swap(ra, rb);
			w = -w;
		}
		f[rb] = ra;
		d[rb] = d[a] - d[b] + w;
		siz[ra] += siz[rb];
		return true;
	}
	T diff(int a, int b) {
		find(a), find(b);
		return d[b] - d[a];
	}
}; // f1abeb
template<class T = ll> struct LazyDSU {
	vector<int> f, siz;
	vector<T> d, tag;
	LazyDSU(int n) : f(n), siz(n, 1), d(n), tag(n) {
		iota(f.begin(), f.end(), 0);
	}
	int find(int x) {
		if (x != f[x]) {
			int y = f[x];
			f[x] = find(y);
			d[x] += d[y];
		}
		return f[x];
	}
	bool same(int x, int y) { return find(x) == find(y); }
	bool merge(int x, int y) {
		x = find(x), y = find(y);
		if (x == y) return false;
		if (siz[x] < siz[y]) swap(x, y);
		siz[x] += siz[y];
		f[y] = x;
		d[y] = tag[y] - tag[x];   // 抵消 x 的舊 tag，保留 y 的舊 tag
		return true;
	}
	void add(int x, T v) { // x 所在集合的所有元素加 v
		tag[find(x)] += v;
	}
	T get(int x) { // 查詢單點 x 的值
		int r = find(x);
		return d[x] + tag[r];
	}
	int size(int x) { return siz[find(x)]; }
}; // 31c59f
struct RollbackDSU {
	vector<int> f, siz, stk;
	RollbackDSU(int n) : f(n), siz(n, 1) {
		iota(f.begin(), f.end(), 0);
	}
	int find(int x) {
		return x == f[x] ? x : find(f[x]);
	}
	bool same(int x, int y) { return find(x) == find(y); }
	bool merge(int x, int y) {
		x = find(x), y = find(y);
		if (x == y) return false;
		if (siz[x] < siz[y]) swap(x, y);
		siz[x] += siz[y];
		f[y] = x;
		stk.push_back(y);
		return true;
	}
	void undo(int x) {
		while (stk.size() > x) {
			int y = stk.back();
			stk.pop_back();
			siz[f[y]] -= siz[y];
			f[y] = y;
		}
	}
	int size(int x) { return siz[find(x)]; }
}; // 35c68a