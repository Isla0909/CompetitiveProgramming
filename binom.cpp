int fac[N], invfac[N];

int quick_pow(int a, i64 b, int p)
{
	int res = 1;
	while(b)
	{
		if(b & 1) res = 1LL * res * a % p;

		a = 1LL * a * a % p;
		b >>= 1;
	}
	return res % p;
}

void initial()
{
	fac[0] = invfac[0] = 1;
	for(int i = 1; i < N; i ++)
	{
		fac[i] = 1LL * fac[i - 1] * i % mod;
		invfac[i] = 1LL * invfac[i - 1] * quick_pow(i, mod - 2, mod) % mod;
	}
}

int binom(int n, int m)
{
	if(n < m || m < 0) return 0;
	return 1LL * fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}
//注:函数开始时必须调用initial