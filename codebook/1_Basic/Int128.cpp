using i128 = __int128_t; // 1.7E38
inline i128 read() {
    i128 sgn = 1, x = 0;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-') sgn = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * sgn;
}
inline void write(i128 x){
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}