int exgcd(int a, int b, int &x, int &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }

    int g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}
int inv(int x, int m){
    int a, b;
    exgcd(x, m, a, b);
    a %= m;
    if (a < 0) a += m;
    return a;
}
// remain, mod
int CRT(vector<pair<int,int>> &a){
    int prod = 1;
    for (auto x : a) {
        prod *= x.second;
    }
    int res = 0;
    for (auto x : a) {
        auto t = prod / x.second;
        res += x.first * t % prod * inv(t, x.second) % prod;
        if(res >= prod) res -= prod;
    }
    return res;
}