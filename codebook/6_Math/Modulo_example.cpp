int main() {
    i64 x, y;
    cin >> x >> y;

    Z::setMod(3);
    Comb c1;
    cout << c1.binom(x, y) << "\n";

    Z::setMod(5);
    Comb c2;
    cout << c2.binom(x, y) << "\n";

    Z::setMod(7);
    Comb c3;
    cout << c3.binom(x, y) << "\n";
}