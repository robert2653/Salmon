using i128 = __int128_t; // 1.7E38
inline i128 read() {
    i128 sgn = 1, x = 0;
    string s; cin >> s;
    for (auto c : s) {
        if (c == '-') {
            sgn = -1;
        } else {
            x = x * 10 + c - '0';
        }
    }
    return x * sgn;
}
inline void write(i128 x){
    if (x < 0) {
        cout << '-';
        x = -x;
    }
    if (x > 9) write(x / 10);
    cout << char(x % 10 + '0');
}