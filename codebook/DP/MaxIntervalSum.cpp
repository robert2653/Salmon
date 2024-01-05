#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

int main(){
    vector<ll>v1;
    ll t; // test
    cin >> t;
    while (t--){
        v1.clear();
        ll n,last,ans;
        cin >> n; // number
        for(int i = 0;i < n;i++){
            ll tmp;
            cin >> tmp;
            v1.push_back(tmp);
        }
        ll l = 0; // answer_left
        ll r = 0; // right
        ll tmpl = 0; // temp_left
        ans = v1[0];
        last = v1[0];
        for(int i = 1;i < n;i++){
            if(0 > last){
                tmpl = i;
            }
            last = max((ll)0,last) + v1[i];
            if(ans < last){
                l = tmpl;
                r = i;
            }
            ans = max(ans,last);
        }
        cout << ans << "\n";
        cout << l + 1 << " " << r + 1 << "\n";
    }
    return 0;
}