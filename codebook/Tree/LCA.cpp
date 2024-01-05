#include <bits/stdc++.h> // LCA from 1
using namespace std;
const int maxn = 2e5+5;
int boss[maxn];
int height[maxn];
int arr[18][maxn];
vector<int> tree[maxn];
void Calculate_H(int now_node){
    for(auto nxt_node : tree[now_node]){
        height[nxt_node] = height[now_node] + 1;
        Calculate_H(nxt_node);
    }
}
int Find_Ancestor(int k, int h){
    for(int i = 0; i <= 17; i++){
        if(h & (1 << i)) k = arr[i][k];
    }
    return k;
}
int main(){
    memset(arr, 0, sizeof(arr));
    int n, q; cin >> n >> q;
    boss[1] = 1;
    for(int i = 2; i <= n; i++){
        int tmp; cin >> tmp;    // tmp to i
        boss[i] = tmp;
        tree[tmp].push_back(i);
    }
    Calculate_H(1);
    for(int i = 2; i <= n; i++){
        arr[0][i] = boss[i];
    }
    for(int i = 1; i <= 17; i++){   // make chart
        for(int j = 1; j <= n; j++){
            arr[i][j] = arr[i - 1][arr[i - 1][j]];
        }
    }
    while(q--){
        int a, b; cin >> a >> b;
        if(height[a] < height[b]) swap(a, b);
        a = Find_Ancestor(a, height[a] - height[b]); // same depth from 1
        if(a == b){ // same point 
            cout << a << "\n";
            continue;
        }
        for(int i = 17; i >= 0; i--){
            if(arr[i][a] != arr[i][b]){ // if a, b up 2 ^ i not the same point
                a = arr[i][a];
                b = arr[i][b];
            }
        }
        cout << arr[0][a] << "\n"; // more one
    }
}