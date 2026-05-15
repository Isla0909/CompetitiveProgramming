struct SparseTable
{
	int n, k;
	vector<int> a;
	vector<vector<int>> st;

	SparseTable() {}
	SparseTable(vector<int> &v)
	{
		initial(v);
	}

	void initial(vector<int> &v)
	{
		n = v.size() - 1;
		k = __lg(2 * n - 1) + 1;
		a.resize(n + 1);
		for(int i = 1; i <= n; i ++)
			a[i] = v[i];
		st.assign(n + 1, vector<int>(k));
	}

	void max_work()
	{
		for(int j = 0; j < k; j ++)
			for(int i = 1; i + (1 << j) - 1 <= n; i ++)
			{
				if(j == 0) st[i][j] = a[i];
				else st[i][j] = max(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);
			}
	}
	int max_query(int l, int r)
	{
		if(l > r) swap(l, r);
		int k = __lg(r - l + 1);
		return max(st[l][k], st[r - (1 << k) + 1][k]);
	}

	void min_work()
	{
		for(int j = 0; j < k; j ++)
			for(int i = 1; i + (1 << j) - 1 <= n; i ++)
			{
				if(j == 0) st[i][j] = a[i];
				else st[i][j] = min(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);
			}
	}
	int min_query(int l, int r)
	{
		if(l > r) swap(l, r);
		int k = __lg(r - l + 1);
		return min(st[l][k], st[r - (1 << k) + 1][k]);
	}

	void gcd_work()
	{
		for(int j = 0; j < k; j ++)
			for(int i = 1; i + (1 << j) - 1 <= n; i ++)
			{
				if(j == 0) st[i][j] = a[i];
				else st[i][j] = __gcd(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);
			}
	}
	int gcd_query(int l, int r)
	{
		if(l > r) swap(l, r);
		int k = __lg(r - l + 1);
		return __gcd(st[l][k], st[r - (1 << k) + 1][k]);
	}
};