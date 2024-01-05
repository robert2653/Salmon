int parent[20][300100]; // n < 2^20
int depth[300100];
int LCA(int u,int v){
    if(depth[u] > depth[v]) swap(u,v);
    int diff = depth[v] - depth[u];
    for(int i = 19;i >= 0;i--){
        if(diff&(1 << i)){
            v = parent[i][v];
        }
    }
    if(u == v) return u;
    for(int i = 19;i >= 0;i--){
        if(parent[i][u]!=parent[i][v]){
            u = parent[i][u];
            v = parent[i][v];
        }
    }
    return parent[0][u];
}
int main(){
    int n,m;
    cin >> n >> m; // nodes tests
    parent[0][1] = 1; // root
    depth[1] = 1; // root
    for(int i = 2;i <= n;i++){
        int tmp;
        cin >> tmp; // parent
        parent[0][i] = tmp;
        depth[i] = depth[tmp] + 1;
    }
    for(int i = 1;i < 20;i++){
        for(int j = n;j >= 1;j--){
            parent[i][j] = parent[i-1][parent[i-1][j]];
        }
    }
    int u,v;
    for(int i = 0;i < m;i++){
        cin >> u >> v;
        int ans = LCA(u,v);
        cout << ans << "\n";
        //-(depth[ans] - depth[u] + depth[ans] - depth[v]) level
    }
    return 0;
}
