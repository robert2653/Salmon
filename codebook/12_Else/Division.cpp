private:
    vector<int> smallDiv(vector<int> a, int v) {
        ll add = 0;
        for (int i = a.size() - 1; i >= 0; i--) {
            add = add * B + a[i];
            int q = add / v;
            a[i] = q, add %= v;
        }
        return norm(a);
    }
    friend Bigint operator<<(Bigint a, int k) {
        if (!a.x.empty()) {
            vector<int> add(k, 0);
            a.x.insert(a.x.begin(), add.begin(), add.end());
        }
        return a;
    }
    friend Bigint operator>>(Bigint a, int k) {
        a.x = vector<int>(a.x.begin() + min(k, int(a.x.size())), a.x.end());
        a.x = a.norm(a.x);
        return a;
    }
public:
    friend Bigint operator/(Bigint a, Bigint b) {
        a = a.abs(), b = b.abs();
        a.sgn *= b.sgn;
        if (a < b) return Bigint();
        if (b.size() == 1) {
            a.x = a.smallDiv(a.x, b.x[0]);
        } else {
            Bigint inv = 1LL * B * B / b.x.back();
            Bigint pre = 0, res = 0;
            int d = a.size() + 1 - b.size();
            int cur = 2, bcur = 1;
            while (inv != pre || bcur < b.size()) {
                bcur = min(bcur << 1, b.size());
                res.x = {b.x.end() - bcur, b.x.end()};
                pre = inv;
                inv = inv * ((Bigint(2) << (cur + bcur - 1)) - inv * res);
                cur = min(cur << 1, d);
                inv.x = {inv.x.end() - cur, inv.x.end()};
            }
            inv.x = {inv.x.end() - d, inv.x.end()};
            res = (a * inv) >> a.size();
            Bigint mul = res * b;
            while (mul + b <= a) res = res + 1, mul = mul + b;
            a.x = a.norm(res.x);
        }
        return a;
    }
    friend Bigint operator%(Bigint a, Bigint b)
    { return a = a - (a / b) * b; }
Bigint gcd(Bigint a, Bigint b) {
    while (b != 0) {
        Bigint r = a % b;
        a = b, b = r;
    } return a;
}