#include <bits/stdc++.h>
using namespace std;
// a^(m-1) ≡ 1 (mod m)
// a^(m-2) ≡ 1/a (mod m)
// EXP2: cout << fast_exp(x, fast_exp(y, p, MOD - 1), MOD)
// Filter + DP; DP save min factor，recur，factor decomposition
// FacNums = (x+1)(y+1)(z+1)...
// FacSum = (a^0+a^1...+a^x)(b^0+...+b^y)
// FacMul = N(x+1)(y+1)(z+1)/2
int main(){
    vector<int> is_prime(2e6 + 1, 1);
    // 1 代表是質數，非 1 不是
    for(int i = 2; i <= 1000; i++){
        if(is_prime[i] == 1){
            for(int j = i + i; j <= 1000000; j += i){
                is_prime[j] = i;
            }
        }
    }
    int ans = 1;
    int q; cin >> q;
    map<int, int> mp;
    while(is_prime[q] != 1){
        mp[is_prime[q]]++;
        q /= is_prime[q];
    }
    if(q != 1) mp[q]++;
    for(auto [a, b] : mp){
        ans *= b + 1;
    }
    cout << ans << "\n";
}