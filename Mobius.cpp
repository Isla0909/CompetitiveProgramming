vector<int> minp, primes;
vector<int> Mu, preMu;
void sieve(int n)
{
	minp.assign(n + 1, 0);
	Mu.assign(n + 1, 0);
	preMu.assign(n + 1, 0);
	primes.clear();

	Mu[1] = 1;

	for(int i = 2; i <= n; i ++)
	{
		if(!minp[i])
		{
			minp[i] = i;
			Mu[i] = -1;
			primes.push_back(i);
		}
		for(auto p : primes)
		{
			if(i * p > n) break;

			minp[i * p] = p;
			if(p == minp[i]) break;
			Mu[i * p] = -Mu[i];
		}
	}
	for(int i = 1; i <= n; i ++)
		preMu[i] = preMu[i - 1] + Mu[i];
}