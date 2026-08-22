private:
	pair<vector<int>, int> smallDivMod(vector<int> a, int v) {
		ll add = 0;
		for (int i = a.size() - 1; i >= 0; i--) {
			add = add * B + a[i];
			int q = add / v;
			a[i] = q, add %= v;
		}
		return {norm(a), add};
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
	friend pair<Bigint, Bigint> divmod(const Bigint &a, const Bigint &b) {
		int qsgn = a.sgn * b.sgn, rsgn = a.sgn;
		Bigint av = a.abs(), bv = b.abs();
		Bigint quot, rem;
		if (av < bv) {
			rem = av;
		} else if (bv.size() == 1) {
			auto [qd, r] = quot.smallDivMod(av.x, bv.x[0]);
			quot.x = qd;
			rem = Bigint((ll)r);
		} else {
			Bigint inv = 1LL * B * B / bv.x.back();
			Bigint pre = 0, res = 0;
			int d = av.size() + 1 - bv.size();
			int cur = 2, bcur = 1;
			while (inv != pre || bcur < bv.size()) {
				bcur = min(bcur << 1, bv.size());
				res.x = {bv.x.end() - bcur, bv.x.end()};
				pre = inv;
				inv = inv * ((Bigint(2) << (cur + bcur - 1)) - inv * res);
				cur = min(cur << 1, d);
				inv.x = {inv.x.end() - cur, inv.x.end()};
			}
			inv.x = {inv.x.end() - d, inv.x.end()};
			res = (av * inv) >> av.size();
			Bigint mul = res * bv;
			while (mul + bv <= av) res = res + 1, mul = mul + bv;
			quot.x = quot.norm(res.x);
			rem = av - mul; // 重用 mul，不再重算一次 quot * b
		}
		quot.sgn = qsgn, quot.resign();
		rem.sgn = rsgn, rem.resign();
		return {quot, rem};
	}
	friend Bigint operator/(const Bigint &a, const Bigint &b) { return divmod(a, b).first; }
	friend Bigint operator%(const Bigint &a, const Bigint &b) { return divmod(a, b).second; }
Bigint gcd(Bigint a, Bigint b) {
	while (b != 0) {
		Bigint r = a % b;
		a = b, b = r;
	} return a;
}