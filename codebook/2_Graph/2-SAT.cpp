struct TwoSat : SCC {
    vector<int> ans;
    TwoSat(int n) : SCC(2 * n), ans(n) {}
    void addClause(int u, bool a, int v, bool b) {
        addEdge(2 * u + !a, 2 * v + b);
        addEdge(2 * v + !b, 2 * u + a);
    }
    void ifThen(int u, bool a, int v, bool b) {
        // 必取 A: not A -> A
        addEdge(2 * u + a, 2 * v + b);
    }
    bool work() {
        SCC::work(); // bel[!a] > bel[a] => !a -> a
        for (int i = 0; i < n / 2; i++) {
            if (bel[2 * i] == bel[2 * i + 1]) return false;
            ans[i] = bel[2 * i] > bel[2 * i + 1];
        }
        return true;
    }
};