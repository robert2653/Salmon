// 找極值問題，遞增遞減
void solve() {
    int l = 0, r = 10, ans = 0; // ans 紀錄答案
    while (l <= r) {
        int d = (r - l) / 3;    // 差
        int ml = l + d, mr = r - d; // mr 要用減的
        auto cal = [&](int m) -> int {
            int x = 0;
            return x;   // 計算答案
        };
        int ansl = cal(ml), ansr = cal(mr);
        if (ansl < ansr) {
            l = ml + 1;
        }
        else r = mr - 1;
    }
}