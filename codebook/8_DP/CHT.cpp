// 應用: dp(x) = C(x) + min/max(A(i) * x + B(i)), for i < x
// 斜率遞減, 求 min, 上凸包, 自行轉化問題
// ex: m 遞增取 max => max(mx + b) = -min(-m x - b)
struct Line { // x 盡量從 1 開始
	ll m, b;
	Line(ll m = 0, ll b = 0) : m(m), b(b) {}
	ll eval(ll x) { return m * x + b; }
};
struct CHT { // 斜率單調
	deque<Line> hull;
	CHT() {}
	CHT(Line init) { addLine(init); }
	bool frontBad(Line &l1, Line &l2, ll x) {
		return l1.eval(x) >= l2.eval(x);
	}
	bool backBad(Line &l1, Line &l2, Line &l) {
		// 只要 l2 跟 l 的 x 交點 <= l1 跟 l 的 X 交點，l2 就用不到了
		return (l.b - l2.b) * (l1.m - l.m) <= (l.b - l1.b) * (l2.m - l.m);
	}
	void addLine(Line l) {
		if (hull.size() > 0 && hull.back().m == l.m) {
			if (hull.back().b <= l.b) return;
			else hull.pop_back();
		}
		while (hull.size() > 1 && backBad(hull[hull.size() - 2], hull.back(), l)) hull.pop_back();
		hull.push_back(l);
	}
	ll query(ll x) { // 查詢沒單調性需要二分搜
		while (hull.size() > 0 && frontBad(hull[0], hull[1], x)) hull.pop_front();
		return hull[0].eval(x);
	}
};