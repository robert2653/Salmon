#include <bits/stdc++.h>
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define all(x) (x).begin(), (x).end()
#define FOR(s,a,b) for (int s = a; s <= b; s++)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> pi;

ll nxt() {
    ll x;
    cin >> x;
    return x;
}

vector<vi> edge;
vi vis;
stack<ll> order;
bool dfs(ll u){
    if(vis[u]==2){
        return false;
    }
    else if(vis[u]==1)return true;
    bool cycle = false;
    vis[u] = 1;
    for(auto x:edge[u]){
        cycle = max(cycle,dfs(x));
    }
    order.push(u);
    vis[u] = 2;
    return cycle;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n = nxt();
    vi a(0);
    edge.assign(n+1,a);
    vis.assign(n+1,0);
    ll m = nxt();
    for(ll i = 0;i < m;i++){
        ll a = nxt();
        ll b = nxt();
        edge[a].push_back(b);
    }
    bool cycle = false;
    for(int i = 1;i <= n;i++){
        cycle = max(cycle,dfs(i));
        
    }
    if(cycle){
        cout << "IMPOSSIBLE\n";
    }
    else{
        while(order.size()){
            cout << order.top() << ' ';
            order.pop();
        }
    }
}