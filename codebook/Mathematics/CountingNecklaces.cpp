ll M = 1e9+7;

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
// Function to find result using
// Orbit counting theorem
// or Burnside's Lemma
void countDistinctWays(ll n, ll m)
{
    ll ans = 0;
    // According to Burnside's Lemma
    // calculate distinct ways for each
    // rotation
    for (ll i = 0; i < n; i++) {
        // Find GCD
        ll K = __gcd(i, n);
        ans += qpow(m, K, M);
        ans %= M;
    }
    // Divide By N
    ans *= qpow(n, M - 2, M);
    ans %= M;
    // Print the distinct ways
    cout << ans << endl;
}
// Driver Code
int main()
{
    // N stones and M colors
    ll n,m;
    cin >> n >> m;
    // Function call
    countDistinctWays(n, m);
    return 0;
}