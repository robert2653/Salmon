#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
vector<ll> ans;
ll qmul(ll x,ll y,ll m){
    ll res = 0;
    for(;y > 0;y >>= 1,x = (x+x) % m){
        if(y & 1)res = (res+x) % m;
    }
    return res;
}
ll GCD(ll a, ll b){
    return b ? GCD(b, a % b) : a;
}
ll qpow(ll a,ll n,ll m){
    ll res = 1;
    while(n > 0){
        if(n & 1){
            res = qmul(res,a,m);
        }
        a = qmul(a,a,m);
        n >>= 1;
    }
    return res % m;
}
bool Isprime(ll n){  // O(k log N)
    if(n==2) return true;
    if((!(n & 1))|| n==1) return false;
    ll d = n - 1;
    ll s = 0;
    while(!(d & 1)){
        s++;
        d/=2;
    }
    for(int i = 0;i < 10;i++){
        ll x = rand() % (n-1) + 1;
        ll tmp = d;
        if(qpow(x,d,n) == 1){
            continue;
        }
        else{
            bool done = false;
            for(int j = 0;j < s;j++){
                if(qpow(x,tmp,n) == n-1){
                    done = true;
                    break;
                }
                tmp *= 2;
            }
            if(!done) return false;
        }
    }
    return true;
}
ll f(ll x,ll c,ll n){
    return (qmul(x,x,n) + c) %n;
}
void factor(ll n){ // O(N^1/4)
    if(n == 1)return;
    if(n == 4){
        ans.push_back(2);
        ans.push_back(2);
        return;
    }
    if(Isprime(n)){
        ans.push_back(n);
        return;
    }
    else{
        again:;
        ll c = rand() % (n-1) + 1;
        ll x = rand() % (n-1) + 1;
        ll y = x;
        ll d;
        bool done = false;
        do{
            x = f(x,c,n);
            y = f(f(y,c,n),c,n);
            d = GCD(abs(x-y),n);
            if(d > 1 && d < n){
                done = true;
                break;
            }
        }while(x!=y);
        if(done){
            factor(d);
            factor(n/d);
        }
        else goto again;
    }
    return ;
}
int main(){
    ll n;
    while(cin >> n){
        ans.clear();
        factor(n);
        sort(ans.begin(),ans.end());
        ll tmp = ans[0],cnt = 0;
        for(ll i = 0;i < (ll)ans.size();i++){
            if(ans[i]==tmp){
                cnt++;
            }
            else{
                cout << tmp << " " << cnt << " ";
                tmp = ans[i];
                cnt = 1;
            }
        }
        cout << tmp << " " << cnt << "\n";
    }
    return 0;
}