#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;
vector<int> depth;
void dfs(vector<vector<int>> &tree, int u, int pre){
    for(auto v : tree[u]){
        if(v == pre)
        depth[v] = depth[u] + 1;
        dfs(tree, v, u);
    }
}