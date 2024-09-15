template<class T>
struct Fraction {
    T n, d;
    void reduce() {
        T g = gcd(abs(n), abs(d));
        n /= g, d /= g;
        if (d < 0) n = -n, d = -d;
    }
    Fraction(T n_ = 0, T d_ = 1) : n(n_), d(d_) {
        assert(d != 0);
        reduce();
    }
    Fraction(const string &str) {
        istringstream ss(str);
        char slash;
        if (str.find('/') != -1) {
            ss >> n >> slash >> d;
        } else {
            ss >> n;
            d = 1;
        }
        Fraction(n, d);
    }
    Fraction operator+=(Fraction rhs) & {
        n = n * rhs.d + rhs.n * d;
        d *= rhs.d;
        reduce();
        return *this;
    }
    Fraction operator-=(Fraction rhs) & {
        n = n * rhs.d - rhs.n * d;
        d *= rhs.d;
        reduce();
        return *this;
    }
    Fraction operator*=(Fraction rhs) & {
        n *= rhs.n;
        d *= rhs.d;
        reduce();
        return *this;
    }
    Fraction operator/=(Fraction rhs) & {
        assert(rhs.n != 0);
        n *= rhs.d;
        d *= rhs.n;
        reduce();
        return *this;
    }
    friend Fraction operator+(Fraction lhs, Fraction rhs) {
        return lhs += rhs;
    }
    friend Fraction operator-(Fraction lhs, Fraction rhs) {
        return lhs -= rhs;
    }
    friend Fraction operator*(Fraction lhs, Fraction rhs) {
        return lhs *= rhs;
    }
    friend Fraction operator/(Fraction lhs, Fraction rhs) {
        return lhs /= rhs;
    }
    friend istream &operator>>(istream &is, Fraction &f) {
        string s;
        is >> s;
        f = Fraction(s);
        return is;
    }
    friend ostream &operator<<(ostream &os, const Fraction &f) {
        if (f.d == 1) {
            os << f.n;
        } else {
            os << f.n << "/" << f.d;
        }
        return os;
    }
    friend bool operator==(Fraction lhs, Fraction rhs) {
        return lhs.n * rhs.d == rhs.n * lhs.d;
    }
    friend bool operator!=(Fraction lhs, Fraction rhs) {
        return lhs.n * rhs.d != rhs.n * lhs.d;
    }
    friend bool operator<(Fraction lhs, Fraction rhs) {
        return lhs.n * rhs.d < rhs.n * lhs.d;
    }
};