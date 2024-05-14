vector<vector<int>> g;
vector<int> id(n + 1, -1), dfn(n + 1, -1), low(n + 1, -1);
vector<int> stk;
function<void(int)> tarjan = [&](int u) {
    stk.push_back(u);
    dfn[u] = low[u] = now++;
    for (auto v : g[u]) {
        if (dfn[v] == -1) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (id[v] == -1) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        int v;
        do {
            v = stk.back();
            stk.pop_back();
            id[v] = cnt;
        } while (v != u);
        ++cnt;
    }
};
for (int i = 0; i < 2 * n; ++i) if (dfn[i] == -1) tarjan(i);
for (auto i : id) cout << i << " ";