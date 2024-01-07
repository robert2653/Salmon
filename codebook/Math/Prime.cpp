#include <bits/stdc++.h>
using namespace std;
// a^(m-1) ≡ 1 (mod m)
// a^(m-2) ≡ 1/a (mod m)
// EXP2: cout << fast_exp(x, fast_exp(y, p, MOD - 1), MOD)
// Filter + DP; DP save min factor，recur，factor decomposition
// FacNums = (x+1)(y+1)(z+1)...
// FacSum = (a^0+a^1...+a^x)(b^0+...+b^y)
// FacMul = N(x+1)(y+1)(z+1)/2
int Is_Prime[1000005][2];
int main(){
    for(int i = 1; i <= 1000000; i++) Is_Prime[i][0] = 1;
    Is_Prime[1][0] = 0;
    for(int i = 2; i <= 1000; i++){
        if(Is_Prime[i][0]){
            for(int j = i + i; j <= 1000000; j += i){
                Is_Prime[j][0] = 0;
                Is_Prime[j][1] = i;
            }
        }
    }
    int ans = 1;
    int q; cin >> q;
    if(q == 1) {
        cout << 1 << endl;
        return;
    }
    map<int, int> mp;
    while(!Is_Prime[q][0]){
        mp[Is_Prime[q][1]]++;
        q /= Is_Prime[q][1];
    }
    mp[q]++;

    for(auto [a, b] : mp){
        ans *= b + 1;
    }
    cout << ans << endl;
}