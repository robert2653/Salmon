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
    Bigint &operator<<=(int n) & {
        if (!x.empty()) {
            vector<int> add(n, 0);
            x.insert(x.begin(), add.begin(), add.end());
        }
        return *this;
    }
    Bigint &operator>>=(int n) & {
        x = vector<int>(x.begin() + min(n, int(x.size())), x.end());
        x = norm(x);
        return *this;
    }
    friend Bigint operator<<(Bigint lhs, int n) {
        return lhs <<= n;
    }
    friend Bigint operator>>(Bigint lhs, int n) {
        return lhs >>= n;
    }
public:
    Bigint &operator/=(const Bigint &rhs) & {
        Bigint a = abs(), b = rhs.abs();
        sgn *= rhs.sgn;
        if (a < b) return *this = Bigint();
        if (b.size() == 1) {
            x = smallDiv(x, rhs.x[0]);
        } else {
            Bigint inv = 1LL * B * B / b.x.back();
            Bigint pre = 0, res = 0;
            int d = a.size() + 1 - b.size();
            int cur = 2, bcur = 1;
            while (inv != pre || bcur < b.size()) {
                bcur = min(bcur << 1, b.size());
                res.x = {b.x.end() - bcur, b.x.end()};
                pre = inv;
                inv *= ((Bigint(2) << (cur + bcur - 1)) - inv * res);
                cur = min(cur << 1, d);
                inv.x = {inv.x.end() - cur, inv.x.end()};
            }
            inv.x = {inv.x.end() - d, inv.x.end()};
            res = a * inv;
            res >>= a.size();
            Bigint mul = res * b;
            while (mul + b <= a) res += 1, mul += b;
            x = norm(res.x);
        }
        return *this;
    }
    Bigint &operator%=(const Bigint &rhs) & {
        return *this = *this - (*this / rhs) * rhs;
    }
    friend Bigint operator/(Bigint lhs, Bigint rhs) {
        return lhs /= rhs;
    }
    friend Bigint operator%(Bigint lhs, Bigint rhs) {
        return lhs %= rhs;
    }