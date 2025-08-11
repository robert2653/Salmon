vector<bool> vis(n);
vector<int> siz(n), par(n, -1);
auto findSize = [&](auto self, int u, int p) -> int {
    siz[u] = 1;
    for (int v : g[u]) {
        if (v == p || vis[v]) continue;
        siz[u] += self(self, v, u);
    }
    return siz[u];
};
auto findCen = [&](auto self, int u, int p, int sz) -> int {
    for (int v : g[u]) {
        if (v == p || vis[v]) continue;
        if (siz[v] * 2 > sz) return self(self, v, u, sz);
    }
    return u;
};
auto buildCen = [&](auto self, int u, int p) -> void {
    findSize(findSize, u, p);
    int c = findCen(findCen, u, -1, siz[u]);
    vis[c] = true, par[c] = p;
    for (int v : g[c]) if (!vis[v]) self(self, v, c);
};
buildCen(buildCen, 0, -1);