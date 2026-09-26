template<class Info, class Tag = bool()>
struct Treap { // 0 -> initial root
	vector<Info> info;
	// vector<Tag> tag;
	vector<int> siz, par, rev, pri;
	vector<array<int, 2>> ch;
	Treap(int n) : info(n + 1), siz(n + 1), par(n + 1), rev(n + 1), pri(n + 1), ch(n + 1) {
		// tag.resize(n + 1);
		for (int i = 1; i <= n; i++) siz[i] = 1, pri[i] = rng();
	} /*
	void apply(int p, const Tag &t) {
		info[p].apply(siz[p], t);
		tag[p].apply(t);
	} */
	void push(int p) {
		if (rev[p]) {
			swap(ch[p][0], ch[p][1]);
			if (ch[p][0]) rev[ch[p][0]] ^= 1;
			if (ch[p][1]) rev[ch[p][1]] ^= 1;
			rev[p] = 0;
		} /*
		apply(ch[p][0], tag[p]);
		apply(ch[p][1], tag[p]);
		tag[p] = Tag(); */
	}
	void pull(int p) {
		siz[p] = 1 + siz[ch[p][0]] + siz[ch[p][1]];
		par[ch[p][0]] = par[ch[p][1]] = p;
		info[p].pull(info[ch[p][0]], info[ch[p][1]]);
	}
	int merge(int a, int b) {
		if (!a || !b) return a ? a : b;
		push(a), push(b);
		if (pri[a] > pri[b]) {
			ch[a][1] = merge(ch[a][1], b);
			pull(a); return a;
		} else {
			ch[b][0] = merge(a, ch[b][0]);
			pull(b); return b;
		}
	}
	pair<int, int> split(int p, int k) {
		if (!p) return {0, 0};
		push(p);
		if (siz[ch[p][0]] >= k) {
			auto [a, b] = split(ch[p][0], k);
			ch[p][0] = b, pull(p);
			return {a, p};
		} else {
			auto [a, b] = split(ch[p][1], k - siz[ch[p][0]] - 1);
			ch[p][1] = a, pull(p);
			return {p, b};
		}
	}
	void getArray(int p, vector<Info> &a) {
		if (!p) return;
		push(p);
		getArray(ch[p][0], a);
		a.push_back(info[p]);
		getArray(ch[p][1], a);
	} /*
	int getPos(int rt, int p) { // get p's index in array
		int k = siz[ch[p][0]] + 1;
		for (; ; p = par[p]) {
			if (rev[p]) k = siz[p] + 1 - k;
			if (p == rt) return k;
			if (ch[par[p]][1] == p) k += siz[ch[par[p]][0]] + 1;
		}
	}
	template<class F> int findFirst(int p, F &&pred) {
		if (!p) return 0;
		push(p);
		if (!pred(info[p])) return 0;
		int idx = findFirst(ch[p][0], pred);
		if (!idx) idx = 1 + siz[ch[p][0]] + findFirst(ch[p][1], pred);
		return idx;
	} */
}; /*
struct Tag {
	int setv; ll add;
	void apply(const Tag &t) {
		if (t.setv) {
			setv = t.setv;
			add = t.add;
		} else {
			add += t.add;
		}
	}
}; */
struct Info { /*
	ll val, sum;
	void apply(int siz, const Tag &t) {
		if (t.setv) {
			val = t.setv;
			sum = 1LL * siz * t.setv;
		}
		val += t.add;
		sum += 1LL * siz * t.add;
	} */
	void pull(const Info &l, const Info &r) {
		// sum = val + l.sum + r.sum;
	}
};