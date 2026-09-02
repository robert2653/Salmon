const double eps = 1E-9;
int sign(double x)
{ return fabs(x) <= eps ? 0 : (x > 0 ? 1 : -1); }
template<class T> struct Pt {
	T x, y;
	Pt(T x = 0, T y = 0) : x(x), y(y) {}
	Pt operator-() const { return Pt(-x, -y); }
	Pt operator+(Pt p) const { return Pt(x + p.x, y + p.y); }
	Pt operator-(Pt p) const { return Pt(x - p.x, y - p.y); }
	Pt operator*(T k) const { return Pt(x * k, y * k); }
	Pt operator/(T k) const { return Pt(x / k, y / k); }
	bool operator<(Pt p) const { return sign(x - p.x) == 0 ? y < p.y : x < p.x; }
	bool operator==(Pt p) const { return x == p.x && y == p.y; }
	bool operator!=(Pt p) const { return x != p.x || y != p.y; }
	friend istream &operator>>(istream &is, Pt &p)
	{ return is >> p.x >> p.y; }
	friend ostream &operator<<(ostream &os, const Pt &p)
	{ return os << "(" << p.x << ", " << p.y << ")"; }
};
using P = Pt<double>; // 085f5a

struct Line { P a, b; };
template<class T> T dot(Pt<T> a, Pt<T> b) { return a.x * b.x + a.y * b.y; }
template<class T> T cross(Pt<T> a, Pt<T> b) { return a.x * b.y - a.y * b.x; }
template<class T> T abs2(Pt<T> p) { return dot(p, p); }
double abs(P p) { return sqrt(abs2(p)); }
double abs(Line l) { return abs(l.a - l.b); }
int dir(P p, Line l) // left -1, right 1, on 0
{ return -sign(cross(l.b - l.a, p - l.a)); }
bool btw(P p, Line l) // c on segment ab?
{ return dir(p, l) == 0 && sign(dot(p - l.a, p - l.b)) <= 0; }
P norm(P p) { return p / abs(p); }
P rot(P p) { return { -p.y, p.x }; } // 90 degree CCW
P rot(P p, double d) { // CCW, d = degree * PI / 180
	double c = cos(d), s = sin(d);
	return P(p.x * c - p.y * s, p.x * s + p.y * c);
} // 48cbe0

bool parallel(Line l1, Line l2)
{ return sign(cross(l1.b - l1.a, l2.b - l2.a)) == 0; }
P lineIntersection(Line l1, Line l2)
{ return l1.a + (l1.b - l1.a) * (cross(l2.b - l2.a, l1.a - l2.a) / cross(l2.b - l2.a, l1.a - l1.b)); }
P projvec(P p, Line l) {
	P v = l.b - l.a;
	return l.a + v * (dot(p - l.a, v) / abs2(v));
} // 554901