struct VBCC {
	int n, cur = 0, cnt = 0;
	vector<vector<int>> adj, bcc;
	vector<int> dfn, low, stk;
	vector<bool> ap;
	VBCC(int n) : n(n), adj(n), dfn(n, 0), low(n, 0), ap(n) {}
	void addEdge(int u, int v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	void dfs(int x, int p = -1) {
		int ch = 0;
		dfn[x] = low[x] = ++cur;
		stk.push_back(x);
		for (int y : adj[x]) {
			if (!dfn[y]) {
				dfs(y, x);
				ch++;
				low[x] = min(low[x], low[y]);
				if (dfn[x] <= low[y]) {
					ap[x] = true;
					bcc.emplace_back();
					int v;
					do {
						v = stk.back();
						stk.pop_back();
						bcc.back().push_back(v);
					} while (v != y);
					bcc.back().push_back(x);
					cnt++;
				}
			} else if (dfn[y] < dfn[x] && y != p)
				low[x] = min(low[x], dfn[y]);
		}
		if (p == -1 && ch < 2) ap[x] = false;
	}
	void work() {
		for (int i = 0; i < n; i++)
			if (!dfn[i])
				if (adj[i].empty()) {
					bcc.emplace_back(1, i);
					cnt++;
				} else dfs(i);
	}
	struct Graph {
		int n;
		vector<pair<int, int>> edges;
		vector<int> bel, siz, cnte;
	};
	Graph compress() {
		Graph g;
		g.bel.assign(n, -1);
		g.siz.assign(cnt, 0);
		g.cnte.assign(cnt, 0);
		g.n = cnt;
		for (int i = 0; i < n; i++) {
			if (ap[i]) {
				g.bel[i] = g.n++;
				g.siz.push_back(1);
				g.cnte.push_back(0);
			}
		}
		vector<bool> in_bcc(n);
		for (int i = 0; i < cnt; i++) {
			for (int u : bcc[i]) in_bcc[u] = true;
			int edges = 0;
			for (int u : bcc[i]) {
				if (ap[u]) g.edges.emplace_back(g.bel[u], i); 
				else g.bel[u] = i, g.siz[i]++;
				for (int v : adj[u]) if (in_bcc[v]) edges++;
			}
			g.cnte[i] = edges / 2;
			for (int u : bcc[i]) in_bcc[u] = false;
		}
		return g;
	}
};