template<class Tf, class Tc> struct MCMF {
	struct Edge {
		int to;
		Tf f, cap; // 流量跟容量
		Tc cost;
	};
	int n, m, s, t;
	const Tf INF_FLOW = numeric_limits<Tf>::max() / 2;
	const Tc INF_COST = numeric_limits<Tc>::max() / 2;
	vector<Edge> e;
	vector<vector<int>> g;
	vector<Tc> dis;
	vector<int> rt, inq;
	MCMF(int n) : n(n), m(0), g(n) {}
	void addEdge(int u, int v, Tf cap, Tc cost) {
		e.push_back({v, 0, cap, cost});
		e.push_back({u, 0, 0, -cost});
		g[u].push_back(m++);
		g[v].push_back(m++);
	}
	bool spfa() { // O(VE)
		dis.assign(n, INF_COST);
		rt.assign(n, -1), inq.assign(n, 0);
		queue<int> q; q.push(s);
		dis[s] = 0, inq[s] = 1;
		while (!q.empty()) {
			int u = q.front(); q.pop();
			inq[u] = 0;
			for (int id : g[u]) {
				auto [v, f, cap, cost] = e[id];
				Tc ndis = dis[u] + cost;
				if (f < cap && dis[v] > ndis) {
					dis[v] = ndis, rt[v] = id;
					if (!inq[v])
						q.push(v), inq[v] = 1;
				}
			}
		}
		return dis[t] != INF_COST;
	}
	// spfa: O(FVE), dijkstra: O(VE + FElogV)
	pair<Tf, Tc> work(int s_, int t_, Tf need) {
		s = s_, t = t_;
		Tf flow{}; Tc cost{};
		while (spfa()) { // dijkstra: flow == 0 ? spfa() : dijkstra()
			Tf f = need;
			for (int i = t; i != s; i = e[rt[i] ^ 1].to)
				f = min(f, e[rt[i]].cap - e[rt[i]].f);
			for (int i = t; i != s; i = e[rt[i] ^ 1].to)
				e[rt[i]].f += f, e[rt[i] ^ 1].f -= f;
			flow += f, need -= f;
			cost += f * dis[t];
			if (need == 0) break;
		}
		return {flow, cost};
	} /*
	vector<Tc> pot;
	bool dijkstra() { // O(ElogV), 用上一輪的 dis 當 pot, 邊權變非負
		pot = dis;
		dis.assign(n, INF_COST), rt.assign(n, -1);
		priority_queue<pair<Tc, int>, vector<pair<Tc, int>>, greater<>> pq;
		dis[s] = 0;
		pq.emplace(dis[s], s);
		while (!pq.empty()) {
			auto [d, u] = pq.top(); pq.pop();
			if (dis[u] < d) continue;
			for (int id : g[u]) {
				auto [v, f, cap, cost] = e[id];
				Tc ndis = dis[u] + cost + pot[u] - pot[v];
				if (f < cap && dis[v] > ndis) {
					dis[v] = ndis, rt[v] = id;
					pq.emplace(ndis, v);
				}
			}
		}
		for (int i = 0; i < n; i++)
			if (dis[i] != INF_COST) dis[i] += pot[i];
		return dis[t] != INF_COST;
	} */ // 54295b
}; // a224e5