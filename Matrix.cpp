struct Matrix
{
	int n, m;
	vector<vector<int>> f;

	Matrix(int n = 1, int m = 1) : n(n), m(m)
	{
		f.assign(n + 1, vector<int>(m + 1, 0));
	}

	Matrix(const vector<vector<int>> &g)
	{
		n = g.size() - 1;
		m = g[0].size() - 1;
		f = g;
	}

	void clear()
	{
		for(int i = 1; i <= n; i ++)
			fill(f[i].begin(), f[i].end(), 0);
	}

	void initial(int c = -1)
	{
		if(c == -1) c = n;
		m = n = c;
		f.assign(c + 1, vector<int>(c + 1, 0));
		for(int i = 1; i <= c; i ++)
			f[i][i] = 1;
	}

	void display()
	{
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= m; j ++)
				cout <<f[i][j] <<" \n"[j == m];
	}

	//加法
	Matrix& operator+=(const Matrix &rhs)
	{
		assert(n == rhs.n && m == rhs.m);
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= m; j ++)
				f[i][j] += rhs.f[i][j];
		return *this;
	}

	friend Matrix operator+(const Matrix &lhs, const Matrix &rhs)
    {
        Matrix res = lhs;
        res += rhs;
        return res;
    }


    //乘法
	friend Matrix operator*(const Matrix &a, const Matrix &b)
	{
		assert(a.m == b.n);
		Matrix ans(a.n, b.m);
		for(int i = 1; i <= a.n; i ++)
			for(int j = 1; j <= b.m; j ++)
				for(int k = 1; k <= a.m; k ++)
					ans.f[i][j] = (ans.f[i][j] + a.f[i][k] * b.f[k][j]);
		return ans;	
	}

	Matrix& operator*=(const Matrix &rhs)
	{
		*this = *this * rhs;
		return *this;
	}

	//快速幂
	friend Matrix operator^(Matrix x, int y)
	{
		assert(x.n == x.m);
		int c = x.n;
		Matrix ans(c, c);
		ans.initial();
		while(y)
		{
			if(y & 1) ans = ans * x;

			x = x * x;
			y >>= 1; 
		}
		return ans;
	}
};