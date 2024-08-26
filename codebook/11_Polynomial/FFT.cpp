const double PI = acos(-1.0);
struct Complex {
    double x, y;
    Complex(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
    Complex operator+(const Complex &b) const {
        return Complex(x + b.x, y + b.y);
    }
    Complex operator-(const Complex &b) const {
        return Complex(x - b.x, y - b.y);
    }
    Complex operator*(const Complex &b) const {
        return Complex(x * b.x - y * b.y, x * b.y + y * b.x);
    }
};
vector<int> rev;
void fft(vector<Complex> &a, bool inv) {
    int n = a.size();
    if (int(rev.size()) != n) {
        int k = __builtin_ctz(n) - 1;
        rev.resize(n);
        for (int i = 0; i < n; i++) {
            rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
        }
    }
    for (int i = 0; i < n; i++) {
        if (rev[i] < i) {
            swap(a[i], a[rev[i]]);
        }
    }
    for (int k = 1; k < n; k *= 2) {
        double ang = (inv ? -1 : 1) * PI / k;
        Complex wn(cos(ang), sin(ang));
        for (int i = 0; i < n; i += 2 * k) {
            Complex w(1);
            for (int j = 0; j < k; j++, w = w * wn) {
                Complex u = a[i + j];
                Complex v = a[i + j + k] * w;
                a[i + j] = u + v;
                a[i + j + k] = u - v;
            }
        }
    }
    if (inv) {
        for (auto &x : a) {
            x.x /= n;
            x.y /= n;
        }
    }
}
template<class T>
vector<T> mulT(const vector<T> &a, const vector<T> &b) {
    vector<Complex> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 2 << __lg(a.size() + b.size());
    fa.resize(n), fb.resize(n);
    fft(fa, false), fft(fb, false);
    for (int i = 0; i < n; i++) {
        fa[i] = fa[i] * fb[i];
    }
    fft(fa, true);
    vector<T> res(n);
    for (int i = 0; i < n; i++) {
        if constexpr (!is_same_v<T, double>) {
            res[i] = round(fa[i].x);
        } else {
            res[i] = fa[i].x;
        }
    }
    return res;
}