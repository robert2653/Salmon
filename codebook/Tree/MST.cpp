struct Union_find{
    ll link[100100];
    ll size[100100];
    void init(){
        for(int i = 0;i < 100100;i++){
            link[i] = i;
            size[i] = 1;
        }
    }
    ll find(ll x){
        if(x == link[x]) return x;
        return link[x] = find(link[x]);
    }
    bool same(ll x, ll y){
        return find(x) == find(y);
    }
    void unite(ll x,ll y){
        x = find(x);
        y = find(y);
        if(size[x] < size[y]) swap(x,y);
        size[x] += size[y];
        link[y] = x;
    }
} uf;

int main(){
    ll n = nxt();
    ll m = nxt();
    vector<tuple<ll, ll, ll> > v;
    uf.init();
    for(int i = 0;i < m;i++){
        ll a = nxt();
        ll b = nxt();
        ll w = nxt();
        v.push_back({w,a,b});
    }
    sort(all(v));
    ll ans = 0;
    for(auto x:v){
        ll a, b, w;
        tie(w,a,b) = x;
        if(!uf.same(a,b)){
            uf.unite(a,b);
            ans += w;
        }
    }
    if(uf.size[uf.find(1)]==n)cout << ans << '\n';
    else cout << "IMPOSSIBLE\n";    
    return 0;
}