vector<int> minp, primes, mu, phi, dnum, pnum;
vector<ll> dsum;
void sieve(int n) {
	minp.assign(n + 1, 0);
	phi.assign(n + 1, 0), mu.assign(n + 1, 0);
	phi[1] = mu[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!minp[i]) {
			minp[i] = i;
			primes.push_back(i);
			phi[i] = i - 1;
			mu[i] = -1;
		}
		for (int p : primes) {
			if (i * p > n) break;
			minp[i * p] = p;
			if (p == minp[i]) {
				phi[i * p] = phi[i] * p;
				mu[i * p] = 0;
				break;
			} else {
				phi[i * p] = phi[i] * (p - 1);
				mu[i * p] = -mu[i];
			}
		}
	}
	dnum.assign(n + 1, 0), dsum.assign(n + 1, 0);
	for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j += i) dnum[j]++, dsum[j] += i;
	pnum.assign(n + 1, 0);
	for (int p : primes) for (int j = p; j <= n; j += p) pnum[j]++;
}