ll M = 1;
struct gcdstruct{// ax + by = d
    ll d;
    ll x;
    ll y;
};
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
    return aa.x;
}
int main(){
    ll n,t1,t2;
    cin >> n;// equations
    vector<ll> v1[2];
	for(int i = 0;i < n;i++){
        cin >> t1 >> t2;//ans % m = a
        v1[0].push_back(t1);
        v1[1].push_back(t2);
        M *= t1;
	}
	ll x = 0;
	for(int i = 0;i < n;i++){
        ll m = v1[0][i];
        ll Mi = (M / m);
        x += (v1[1][i] * ((inverse(Mi,m) + m) % m) * Mi) % M;
        //a * t * Mi
	}
	cout << x % M << "\n";
	return 0;
}

