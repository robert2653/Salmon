int gcd(int a, int b)
{
	return b == 0 ? a : gcd(b, a % b);
}

int lcm(int a, int b)
{
	return a * b / gcd(a, b);
}

pair<int, int> ext_gcd(int a, int b) //擴展歐幾里德 ax+by = gcd(a,b)
{
	if (b == 0)
		return {1, 0};
	if (a == 0)
		return {0, 1};
	int x, y;
	tie(x, y) = ext_gcd(b % a, a);
	return make_pair(y - b * x / a, x);
}