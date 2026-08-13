// duval_algorithm
// 將字串分解成若干個非嚴格遞減的非嚴格遞增字串
template<class T> vector<T> duval(const T &s) {
	int i = 0, n = s.size();
	vector<T> res;
	while (i < n) {
		int k = i, j = i + 1;
		for (; j < n && s[k] <= s[j]; j++) {
			if (s[k] < s[j]) k = i;
			else k++;
		}
		while (i <= k) {
			res.emplace_back(s.begin() + i, s.begin() + i + j - k);
			i += j - k;
		}
	}
	return res;
}
// 最小旋轉字串
template<class T> T minRound(T s) {
	s.insert(s.end(), s.begin(), s.end());
	int i = 0, n = s.size(), start = i;
	while (i < n / 2) {
		start = i;
		int k = i, j = i + 1;
		for (; j < n && s[k] <= s[j]; j++) {
			if (s[k] < s[j]) k = i;
			else k++;
		}
		while (i <= k) i += j - k;
	}
	return {s.begin() + start, s.begin() + start + n / 2};
}