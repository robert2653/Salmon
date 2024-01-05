// Permutation such that no element appears in its original position
ll countDer(ll n)
{
    // base case
    if (n == 1 or n == 2) return n - 1;

    // Variable for just storing
    // previous values
    ll a = 0;
    ll b = 1;
 
    // using above recursive formula
    for (ll i = 3; i <= n; ++i) {
        ll cur = (i - 1) * (a + b);
        a = b;
        b = cur;
    }
 
    // Return result for n
    return b;
}
 
// Driver Code
int main()
{
    cout << "Count of Derangements is " << countDer(4);
    return 0;
}