int lowbit(int x)
{
	return x & -x;
}

bool is_perfect(int x)
{
	return x == lowbit(x);
}

int ceilLog(int x)
{
	return __lg(2 * x - 1);
}

int lev(int x)//求一个数的二进制有多少位
{
	return __lg(x);
}

int len(int x)
{
	return __lg(x) + 1;
}

int hbit(int x)
{
	return __lg(x);
}

int getbit(int x, int c)
{
	return (x >> c & 1);
}

int count1(int x)
{
	return __builtin_popcount(x);
}

int count0(int x)
{
	return len(x) - count1(x);
}

int remove_bit(int mask, int x)//删除二进制的某一位并自动右移
{
	return (mask & ((1 << x) - 1)) | ((mask >> (x + 1)) << x);
}