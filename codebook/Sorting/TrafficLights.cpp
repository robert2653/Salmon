// after each add light longest distance
set<ll> st =  {0,x};
multiset<ll> mst = {x};
for(int i = 0;i <n;i++){
    ll k = nxt();
    auto it1 = st.upper_bound(k);
    auto it2 = it1;
    it2--;
    mst.erase(mst.find(*it1 - *it2));
    mst.insert(*it1 - k);
    mst.insert(k - * it2);
    st.insert(k);
    auto it = mst.end();
    it--;
    cout << *it << ' ';
}