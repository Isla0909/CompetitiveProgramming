i64 mul(i64 a, i64 b, i64 p)
{
	i64 c = a * b - i64(1.0L * a * b / p) * p;

	c %= p;
	if(c < 0) c += p;

	return c;
}

i64 pow(i64 a, i64 b, i64 p)
{
	i64 res = 1;
	while(b)
	{
		if(b & 1) res = mul(res, a, p);

		a = mul(a, a, p);
		b >>= 1;
	}
	return res % p;
}

bool isprime(i64 n)
{
	if(n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;

	i64 s = __builtin_ctzll(n - 1), d = n >> s;

	for(i64 a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022})
	{
		i64 p = pow(a % n, d, n), i = s;
		while(p != 1 && p != n - 1 && a % n && i --) p = mul(p, p, n);
		if(p != n - 1 && i != s) return false;
	}
	return true;
}