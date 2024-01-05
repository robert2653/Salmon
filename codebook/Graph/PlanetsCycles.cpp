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
vi dis;
vi v;
vector<bool> vis;
ll step;
ll one;
queue<ll> path;
void dfs(ll x){
    path.push(x);
    if(vis[x]){
        step += dis[x];
        return;
    }
    vis[x] = true;
    step++;
    dfs(v[x]);
}
// count pathdis to rep
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n = nxt();
    v.assign(n+1,0);
    dis.assign(n+1,0);
    vis.assign(n+1,false);
    for(int i = 1;i <= n;i++){
        cin >> v[i];
    }
    for(int i = 1;i <= n;i++){
        step = 0;
        one = 1;
        dfs(i);
        while(!path.empty()){
            if(path.front() == path.back()){
                one = 0;
            }
            dis[path.front()] = step;
            step -= one;
            path.pop();
        }
    }
    for(int i = 1;i <= n;i++){
        cout << dis[i] << ' ';
    }
    cout << '\n';
}