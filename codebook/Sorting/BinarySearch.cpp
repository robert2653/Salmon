bool ans[100100];
ll bi_se(ll a,ll b){
    while (b > a)
    {//0 0 0 0...1 1 1 1
        ll mid = (a + b) / 2;
        if(!ans[mid]) a = mid + 1;
        else b = mid;
    }
    return a;
}
bool valid(int x){
    if (x > 10) return true;
    else return false;
}
int main(){
    ll k = -1,z = 20;
    for(ll i = z;i >= 1;i /= 2){
        while(!valid(k+i))k+=i;
    }
    ll ans = k + 1;
    cout << ans << '\n';
    sort(all(v));
    v.erase(unique(all(v),v.end());// left unique value
    return 0;
}