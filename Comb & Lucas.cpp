int quick_pow(int a, ll b, int p)
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

int inv(int x, int p)
{
	return quick_pow(x, p - 2, p);
}

int C(int a, int b, int p)
{
	if(a < 0 || b < 0 || a < b) return 0;

	int res = 1;
	for(int i = 1, j = a; i <= b; i ++, j --)
	{
		res = 1LL * res * j % p;
		res = 1LL * res * inv(i, p) % p;
	}
	return res;
}

int Lucas(ll a, ll b, int p)
{
	if(a < p && b < p) return C(a, b, p);
	return 1LL * C(a % p, b % p, p) * Lucas(a / p, b / p, p) % p;
}