// 郵差要送 k 個包裹到 n 地，每個邊有最大量跟，Cost per parcel
// 求 1 到 n 的最小成本
struct edge {
    int from, to, w, cost;
};
int n, m, parcel;
vector<edge> adj;   // 幫每個 edge 編號
vector<int> p[505]; // u 存 edge 編號
int now_edge = 0;
void add_edge(int u, int v, int w, int cost){
    adj.push_back({u, v, w, cost});
    p[u].push_back(now_edge);
    now_edge++;
    adj.push_back({v, u, 0, -cost});
    p[v].push_back(now_edge);
    now_edge++;
}
int Bellman_Ford(){
    vector<int> dis(n + 1, inf); dis[1] = 0;
    vector<int> par(m);
    vector<int> flow_rec(n + 1, 0); flow_rec[1] = 1e9;
    for (int i = 1; i < n; i++) {
        bool flag = 1;
        int size = adj.size();
        for (int i = 0; i < size; i++) {
            auto &[from, to, w, cost] = adj[i];
            if (w > 0 && dis[to] > dis[from] + cost){
                flag = 0;
                dis[to] = dis[from] + cost;
                par[to] = i;   // 紀錄編號
                flow_rec[to] = min(flow_rec[from], w);
            }
        }
        if (flag) break;
    }
    if (dis[n] == 1e9) return 0;
    int mn_flow = flow_rec[n];
    int v = n;
    while(v != 1){
        int u = adj[par[v]].from;
        adj[par[v]].w -= mn_flow;
        adj[par[v] ^ 1].w += mn_flow;
        v = u;
    }
    mn_flow = min(mn_flow, parcel);
    parcel -= mn_flow;
    return mn_flow * dis[n];
}
int main(){
    cin >> n >> m >> parcel;
    int ans = 0;
    for (int i = 1; i < m; i++) {
        int u, v, w, cost; cin >> u >> v >> w >> cost;
        add_edge(u, v, w, cost);
    }
    while (parcel > 0){
        int tmp = Bellman_Ford();
        if (tmp == 0) break;
        ans += tmp;
    }
    cout << (parcel > 0 ? -1 : ans);
}