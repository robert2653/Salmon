constexpr i64 b = 233;
vector<Z> Hash(string s) {
    vector<Z> ans{0};
    for (auto c : s) {
        ans.push_back(ans.back() * b + (c - 'a' + 1));
    }
    return ans;
}
int main() { // KMP 詢問
    string s, sub;
    cin >> s >> sub;
    auto a = Hash(s);
    auto q = Hash(sub);
    auto find = q.back();
    int ans = 0;
    int l = 1, r = sub.size(), length = sub.size();
    while (r <= s.size()) {
        if (a[r] - a[l - 1] * power(Z(b), length) == find)
            ans++;
        l++, r++;
    }
    cout << ans << "\n";
}