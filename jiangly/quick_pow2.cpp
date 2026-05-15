ll mul(ll a, ll b, ll p)
{
	ll c = a * b - ll(1.0L * a * b / p) * p;

	c %= p;
	if(c < 0) c += p;

	return c;
}

ll quick_pow(ll a, ll b, ll p)
{
	ll res = 1;
	while(b)
	{
		if(b & 1) res = mul(res, a, p);

		a = mul(a, a, p);
		b >>= 1;
	}
	return res % p;
}