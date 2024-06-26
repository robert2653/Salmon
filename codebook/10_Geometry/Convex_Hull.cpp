vector<pii> P, L, U;
int cross(pii o, pii a, pii b){ // OA OB > 0 counterclock
    return (a.first - o.first) * (b.second - o.second) - (a.second-o.second) * (b.first-o.first);
}
int Andrew_monotone_chain(int n){
    sort(P.begin(), P.end());
    int l = 0, u = 0;   // upper and lower hull
    for (int i=0; i<n; ++i){
        while (l >= 2 && cross(L[l-2], L[l-1], P[i]) <= 0){
            l--;
            L.pop_back();
        }
        while (u >= 2 && cross(U[u-2], U[u-1], P[i]) >= 0){
            u--;
            U.pop_back();
        }
        l++;
        u++;
        L.push_back(P[i]);
        U.push_back(P[i]);
    }
    cout << l << ' ' <<  u << '\n';
    return l + u;
}
int main(){
    int n, x, y;
    cin >> n;
    for(int i = 0;i < n;i++){
        cin >> x >> y;
        P.push_back({x, y});
    }
    int ans = Andrew_monotone_chain(n) - 2;
    cout << ans << "\n";
    return 0;
}