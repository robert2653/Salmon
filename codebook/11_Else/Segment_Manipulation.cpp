auto era = [&](set<pair<int, int>> &st, int L, int R) -> void {
	auto it = st.lower_bound({L, -1});
	if (it != st.begin() && prev(it)->second >= L) --it;
	while (it != st.end() && it->first <= R) {
		auto [l, r] = *it;
		it = st.erase(it);
		if (l < L) st.emplace(l, L - 1);
		if (R < r) st.emplace(R + 1, r);
	}
};
auto ins = [&](set<pair<int, int>> &st, int L, int R) -> void {
	auto it = st.lower_bound({L, -1});
	if (it != st.begin() && prev(it)->second + 1 >= L) --it;
	while (it != st.end() && it->first <= R + 1) {
		L = min(L, it->first);
		R = max(R, it->second);
		it = st.erase(it);
	}
	st.emplace(L, R);
};