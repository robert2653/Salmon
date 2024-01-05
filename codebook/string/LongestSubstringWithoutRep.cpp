ll ans = 0;
ll i = 1;
for(ll i = 1; i <= n; i++) {
    cin >> v[i];
}
for(ll j = 1; j <= n;j++){
    i = max(i, mp[v[j]]+1);
    ans = max(ans, j - i + 1);
    mp[v[j]] = j;
}