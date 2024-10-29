constexpr int B = 59;
vector<Z> hash(string &s) {
    vector<Z> ans {0};
    for (auto c : s)
        ans.push_back(ans.back() * B + (c - 'a' + 1));
    return ans;
}
void solve() {
    string s, sub;
    cin >> s >> sub;
    Z a = hash(s), q = hash(sub);
    Z find = q.back();
    int ans = 0, l = 1, r = sub.size(), len = sub.size();
    while (r <= s.size()) {
        if (a[r] - a[l - 1] * power(Z(B), len) == find)
            ans++;
        l++, r++;
    }
}