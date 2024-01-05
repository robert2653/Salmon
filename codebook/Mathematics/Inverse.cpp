struct gcdstruct{// ax + by = d
    ll d;
    ll x;
    ll y;
};
ll gcd(ll a,ll b){
    return b ? gcd(b , a % b) : a;
}
gcdstruct exgcd(ll a,ll b){
    gcdstruct aa,bb;
    if(b == 0){
        aa.d = a;
        aa.x = 1;
        aa.y = 0;
        return aa;
    }
    else{
        bb = exgcd(b,a % b);
        aa.d = bb.d;
        aa.x = bb.y;
        aa.y = bb.x - bb.y * (a / b);
    }
    return aa;
}
ll inverse(ll a,ll b){
    gcdstruct aa;
    aa = exgcd(a,b);
    return (aa.x % b + b) % b;
}
int main(){
    ll a,n;
    while(cin >> a >> n){
        a %= n;
        if(gcd(a,n) > 1){
            cout << "No Inverse\n";
            continue;
        }
        ll ans = inverse(a,n);
        if(!ans) cout << "No Inverse\n";
        else cout << ans << "\n";
    }
    return 0;
}