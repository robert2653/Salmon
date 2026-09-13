template<class T> T floor(T a, T b)
{ return a / b - (a % b != 0 && ((a < 0) != (b < 0))); }
template<class T> T ceil(T a, T b)
{ return a / b + (a % b != 0 && ((a < 0) == (b < 0))); }
// a / b <  x -> floor(a, b) + 1 <= x
// a / b <= x -> ceil(a, b) <= x
// x <  a / b -> x <= ceil(a, b) - 1
// x <= a / b -> x <= floor(a, b)