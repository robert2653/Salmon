#include <bits/stdc++.h>
using namespace std;
typedef struct{
    int from; int to;
    int weight;
} edge;
// NegCyc_Finding_Road
vector<edge> graph;
int main(){
    int src = 0;
    int n, m;    cin >> n >> m;
    vector<int> par(n + 1), dis(n + 1);
    for(int i = 0; i < m; i++){
        int a, b, w; cin >> a >> b >> w;
        graph.push_back({a, b, w});
    }
    for(int i = 1; i <= n; i++){
        dis[i] = 1e9 + 5;
    }
    dis[1] = 0;
    for(int i = 0; i <= n; i++){
        src = 0;
        for(auto [a, b, w] : graph){
            if(dis[b] > dis[a] + w){
                dis[b] = dis[a] + w;
                par[b] = a;
                src = b;
            }
        }
    }
    if(src){
        vector<int> ans;
        cout << "YES" << endl;
        for(int i = 0; i <= n; i++) src = par[src];
        ans.push_back(src);
        for(int i = par[src]; i != src; i = par[i]){
            ans.push_back(i);
        }
        ans.push_back(src);
        reverse(ans.begin(), ans.end());
        for (auto i : ans){
            cout << i << " ";
        }
    }
    else {
        cout << "NO" << endl;
    }
}