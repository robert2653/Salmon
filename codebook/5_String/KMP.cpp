template<class T> struct KMP {
	int n;
	T pat;
	vector<int> f;
	// f 存匹配失敗時，移去哪
	// 也就是 pat[0, i] 的最長共同前後綴長度
	// ex : a   b  c a b c
	//      -1 -1 -1 0 1 2
	KMP(const T &pat) : n(pat.size()), pat(pat), f(n, -1) {
		for (int i = 1; i < n; i++) {
			int j = f[i - 1];
			while (j != -1 && pat[j + 1] != pat[i]) j = f[j];
			if (pat[j + 1] == pat[i]) f[i] = j + 1;
		}
	}
	vector<int> work(const T &s) {
		vector<int> pos;
		for (int i = 0, j = -1; i < s.size(); i++) {
			while (j != -1 && pat[j + 1] != s[i]) j = f[j];
			if (pat[j + 1] == s[i]) j++;
			if (j + 1 == n) {
				pos.push_back(i - j);
				j = f[j];
			}
		}
		return pos;
	}
};