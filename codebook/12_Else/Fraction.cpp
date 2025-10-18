template<class T>
struct Fraction {
    T n, d;
    void reduce() {
        T g = gcd(abs(n), abs(d));
        n /= g, d /= g;
        if (d < 0) n = -n, d = -d;
    }
    Fraction(T n = 0, T d = 1) : n(n), d(d)
    { assert(d != 0); reduce(); }
    Fraction(const string &str) {
        char slash;
        if (str.find('/') != -1) {
            string x = str.substr(0, str.find('/'));
            string y = str.substr(str.find('/') + 1);
            n = stoBigint(x), d = stoBigint(y);
        } else {
            n = stoBigint(str), d = 1;
        }
        Fraction(n, d);
    }
    Fraction operator+(Fraction rhs) const
    { return Fraction(n * rhs.d + rhs.n * d, d * rhs.d); }
    Fraction operator-(Fraction rhs) const
    { return Fraction(n * rhs.d - rhs.n * d, d * rhs.d); }
    Fraction operator*(Fraction rhs) const
    { return Fraction(n * rhs.n, d * rhs.d); }
    Fraction operator/(Fraction rhs) const {
        assert(rhs.n != 0);
        return Fraction(n * rhs.d, d * rhs.n);
    }
    friend istream &operator>>(istream &is, Fraction &f) {
        string s; is >> s;
        f = Fraction(s);
        return is;
    }
    friend ostream &operator<<(ostream &os, const Fraction &f) {
        if (f.d == 1) os << f.n;
        else os << f.n << "/" << f.d;
        return os;
    }
    bool operator==(Fraction b) const
    { return n * b.d == b.n * d; }
    bool operator!=(Fraction b) const
    { return n * b.d != b.n * d; }
    bool operator<(Fraction b) const
    { return n * b.d < b.n * d; }
};