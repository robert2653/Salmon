auto era = [&](set<pair<int, int>> &st, int x, int y, int inf) -> void {
    auto itl = st.upper_bound({x, inf + 1});
    auto itr = st.upper_bound({y, inf + 1});
    if (itl != st.begin() && prev(itl)->second >= x) --itl;
    if (itl != itr) {
        auto pl = *itl;
        auto pr = *prev(itr);
        st.erase(itl, itr);
        if (pl.first < x && x <= pl.second) st.emplace(pl.first, x - 1);
        if (pr.first <= y && y < pr.second) st.emplace(y + 1, pr.second);
    }
};
auto ins = [&](set<pair<int, int>> &st, int x, int y, int inf) -> void {
    auto itl = st.upper_bound({x, inf + 1});
    auto itr = st.upper_bound({y, inf + 1});
    if (itl != st.begin() && prev(itl)->second + 1 >= x) --itl;
    if (itr != st.end() && y + 1 >= itr->first) ++itr;
    if (itl != itr) {
        x = min(x, itl->first);
        y = max(y, prev(itr)->second);
        st.erase(itl, itr);
    }
    st.emplace(x, y);
};