int mex(vector<int> v) {
    unordered_set<int> s;
    for (auto e : v) s.insert(e);
    for (int i = 0; ; i++) {
        if (s.find(i) == s.end()) return i;
    }
}