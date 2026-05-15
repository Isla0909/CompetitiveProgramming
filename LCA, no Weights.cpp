struct Tree
{
	int n, len;
	vector<vector<int>> adj, f;
	vector<int> dep;

	Tree(int n)
	{
		this->n = n; 
		len = __lg(2 * n - 1);

		adj.resize(n + 1);
		f.resize(n + 1, vector<int>(len));
		dep.resize(n + 1);
	}

	void add(int a, int b)
	{
		adj[a].push_back(b);
	}

	void dfs(int u, int fa)
	{
		f[u][0] = fa;
		dep[u] = dep[fa] + 1;

		for(int i = 1; i < len; i ++)
			f[u][i] = f[f[u][i - 1]][i - 1];

		for(auto v : adj[u])
		{
			if(v == fa) continue;

			dfs(v, u);
		}
	}

	int lca(int a, int b)
	{
		if(dep[a] < dep[b]) swap(a, b);

		for(int k = len - 1; k >= 0; k --)
			if(dep[f[a][k]] >= dep[b])
				a = f[a][k];

		if(a == b) return a;

		for(int k = len - 1; k >= 0; k --)
		{
			if(f[a][k] != f[b][k])
			{
				a = f[a][k];
				b = f[b][k];
			}
		}
		return f[a][0];
	}

	int dist(int a, int b)
	{
		return dep[a] + dep[b] - 2 * dep[lca(a, b)];
	}

	void work(int root = 1)
	{
		dfs(root, 0);
	}

	bool intersection(int a, int b, int c, int d)//a - b, c - d 路径上是否存在交点 
	{
		vector<int> v = {lca(a, c), lca(a, d), lca(b, c), lca(b, d)};
		sort(v.begin(), v.end(), [&](int i, int j) { return dep[i] > dep[j]; });

		int p1 = lca(a, b), p2 = lca(c, d);

		if(dep[v[0]] >= max(dep[p1], dep[p2])) return true;
		return false;
	}
};
//注: 记得调用work函数!!!