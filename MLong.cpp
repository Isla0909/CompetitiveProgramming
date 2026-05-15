template <class T>
constexpr T power(T a, i64 b)
{
	assert(b >= 0);
	T res = 1;
	while(b)
	{
		if(b & 1) res *= a;
		a *= a;
		b >>= 1;
	}
	return res;
}

constexpr i64 mul(i64 a, i64 b, i64 p)
{
	i64 res = a * b - i64(1.L * a * b / p) * p;
	res %= p;

	if(res < 0) res += p;
	return res;
}

template <i64 P>
struct MLong
{
	i64 x; //x ≡ value (mod Mod)
	constexpr MLong() : x{} {}
	constexpr MLong(i64 x_) : x{norm(x_ % getMod())} {}

	static i64 Mod;
	constexpr static i64 getMod()
	{
		//P > 0为静态档, P <= 0为动态档, 模数是Mod
		return P > 0 ? P : Mod;
	}
	//动态修改Mod -> Z::setMod(p)
	constexpr static void setMod(i64 Mod_)
	{
		Mod = Mod_;
	}
	//归一化处理
	constexpr i64 norm(i64 x) const//const保证限制成员变量不被修改 
	{
		if(x < 0) x += getMod();
		if(x >= getMod()) x -= getMod();
		return x;
	}
	constexpr i64 val() const
	{
		return x;
	}
	explicit constexpr operator i64() const
	{
		return x;
	}
	constexpr MLong operator-() const
	{
		MLong res;
		res.x = norm(getMod() - x);
		return res;
	}
	constexpr MLong inv() const
	{
		assert(x != 0);
		return power(*this, getMod() - 2);
	}
	constexpr MLong &operator*=(MLong rhs) &//right-hand side右操作数
	{
		x = mul(x, rhs.x, getMod());
		return *this;
	}
	constexpr MLong &operator+=(MLong rhs) &
	{
		x = norm(x + rhs.x);
		return *this;
	}
	constexpr MLong &operator-=(MLong rhs) &
	{
		x = norm(x - rhs.x);
		return *this;
	}
	constexpr MLong &operator/=(MLong rhs) &
	{
		return *this *= rhs.inv();
	}
	friend constexpr MLong operator*(MLong lhs, MLong rhs)//虽然不是私有成员,加上friend便于以后的维护
	{
		MLong res = lhs;
		res *= rhs;
		return res;
	}
	friend constexpr MLong operator+(MLong lhs, MLong rhs)
	{
		MLong res = lhs;
		res += rhs;
		return res;
	}
	friend constexpr MLong operator-(MLong lhs, MLong rhs)
	{
		MLong res = lhs;
		res -= rhs;
		return res;
	}
	friend constexpr MLong operator/(MLong lhs, MLong rhs)
	{
		MLong res = lhs;
		res /= rhs;
		return res;
	}
	friend constexpr istream &operator>>(istream &is, MLong &a)
	{
		i64 v;
		is >>v;
		a = MLong(v);
		return is;
	}
	friend constexpr ostream &operator<<(ostream &os, const MLong &a)
	{
		return os<< a.val();
	}
	friend constexpr bool operator==(MLong lhs, MLong rhs)
	{
		return lhs.val() == rhs.val();
	}
	friend constexpr bool operator!=(MLong lhs, MLong rhs)
	{
		return lhs.val() != rhs.val();
	}
};

constexpr i64 M = i64(1e18) + 9;
using Z = MLong<M>;

Z fac[N], invfac[N];
void initial()
{
    fac[0] = invfac[0] = 1;
    for(int i = 1; i < N; i ++)
    {
        fac[i] = fac[i - 1] * i;
        invfac[i] = invfac[i - 1] * power(Z(i), mod - 2);
    }
}

Z binom(int n, int m)
{
    if(n < m || m < 0) return 0;
    return fac[n] * invfac[m] * invfac[n - m];
}
//注:若使用组合数学开头必须调用initial
