lli adj[510][510];       // adjacency matrix
lli q[510], *qf, *qb;    // BFS queue
lli p[510];              // BFS tree
lli n,m,a,b,c;
lli Edmonds_Karp(lli s, lli t)
{
    lli f = 0;// max flow
    while(true){ // BFS
        for(int i = 0;i <= n;i++){
            p[i] = -1;
        }
        qf = qb = q;
        p[*qb++ = s] = s;
        while (qf < qb && p[t] == -1)
            for (lli i = *qf++, j = 1; j <= n; ++j)
                if (p[j] == -1 && adj[i][j])
                    p[*qb++ = j] = i;
        if (p[t] == -1) break;

        lli df = 1e18;
        for (lli i = p[t], j = t; i != j; i = p[j = i])
            df = min(df, adj[i][j]);
        for (lli i = p[t], j = t; i != j; i = p[j = i]){
            adj[i][j] -= df;
            adj[j][i] += df;
        }
        f += df;
    }
    return f;
}
int main(){
    cin >> n >> m; // nodes edges
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            adj[i][j] = 0;
        }
    }
    for(int i = 0;i < m;i++){
        cin >> a >> b >> c; // from to capacity
        if(a == b) continue;
        adj[a][b] += c;
    }
    cout << Edmonds_Karp(1,n) << "\n";
    return 0;
}
