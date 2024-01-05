// Function to print the number
// 2n! / (n + 1)! / n!
ll qpow(ll a,ll n,ll m){
    ll res = 1;
    while(n > 0){
        if(n & 1){
            res = res * a % m;
        }
        a = a * a % m;
        n >>= 1;
    }
    return res % m;
}
const ll m = 1e9+7;
const ll maxn = 1e6+10;
ll fac[maxn];
ll inv[maxn];
void factoial(){
    fac[0] = 1;
    for(int i = 1;i < maxn;i++){
        fac[i] = fac[i - 1] * i % m;
    }
}
void inverse(){
    inv[0] = 1;
    for(int i = 1;i < maxn;i++){
        inv[i] = qpow(fac[i],m - 2,m);
    }
}
ll catalan(ll n)
{// ((()))
    ll res;
    res = fac[2 * n] * inv[n + 1] % m;
    res = res * inv[n] % m;
    return res;
}

int main()
{
    int n;
    cin >> n;
    // Function cal
    factoial();
    inverse();
    if(n & 1)cout << '0';
    else cout << catalan(n / 2) << '\n';
    return 0;
}
// there are Cn binary trees of n nodes
// there are Cn−1 rooted trees of n nodes