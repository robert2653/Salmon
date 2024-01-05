#include <bits/stdc++.h>
using namespace std;
int n = 510;
int m = 510;
int mx[510], my[510];   // match x match y
bool vy[510];           // Graph Traversal visit
bool adj[510][510];     // adjacency matrix
bool DFS(int x){
    for (int y = 1;y <= m;y++){
        if (adj[x][y] && !vy[y]){
            vy[y] = true;
            if (my[y] == -1 || DFS(my[y])){
                mx[x] = y;
                my[y] = x;
                return true;
            }
        }
    }
    return false;
}
int main(){
    int k,a,b;
    cin >> n >> m; // boy girl
    cin >> k;// edges
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            adj[i][j] = 0;
        }
    }
    for(int i = 0;i < k;i++){
        cin >> a >> b;
        adj[a][b] = 1;
    }
    for(int i = 1;i <= n;i++){
        mx[i] = -1;
    }
    for(int i = 1;i <= m;i++){
        my[i] = -1;
    }
    int c = 0;
    for (int x = 1;x <= n;x++){
        if (mx[x] == -1){
            for(int i = 1;i <= m;i++){
                vy[i] = 0;
            }
            if (DFS(x)) c++;
        }
    }
    cout << c << "\n";//pairs
    for(int i = 1;i <= n;i++){ // boy to girl
         if(mx[i] != -1) cout << i << " " << mx[i] << "\n";
    }
    return 0;
}
