struct Tree
{
	int n, len;
	vector<vector<pii>> adj;
	vector<vector<int>> f;
	vector<int> dep;
	vector<i64> dist;

	Tree(int n)
	{
		this->n = n;
		len = __lg(2 * n - 1);
		adj.resize(n + 1);
		f.resize(n + 1, vector<int>(len));
		dep.resize(n + 1);
		dist.resize(n + 1);
	}

	void add(int a, int b, int w)
	{
		adj[a].emplace_back(b, w);
	}

	void dfs(int u, int fa)
	{
		f[u][0] = fa;
		dep[u] = dep[fa] + 1;

		for(int i = 1; i < len; i ++)
			f[u][i] = f[f[u][i - 1]][i - 1];

		for(auto [v, w] : adj[u])
		{
			if(v == fa) continue;

			dist[v] = dist[u] + w;
			dfs(v, u);
		}
	}

	int lca(int a, int b)
	{
		if(dep[a] < dep[b]) swap(a, b);

		for(int k = len - 1; k >= 0; k --)
		{
			if(dep[f[a][k]] >= dep[b])
				a = f[a][k];
		}

		if(a == b) return b;
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

	i64 dis(int a, int b)
	{
		return dist[a] + dist[b] - 2 * dist[lca(a, b)];
	}

	void work(int root = 1)
	{
		dfs(root, 0);
	}
};