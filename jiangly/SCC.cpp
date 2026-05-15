struct SCC
{
	int n;
	vector<vector<int>> adj;
	vector<int> stk;
	vector<int> dfn, low, bel, siz;
	int cur, cnt;

	void initial(int n)
	{
		this->n = n;
		adj.assign(n + 1, {});
		dfn.assign(n + 1, -1);
		low.assign(n + 1, -1);
		bel.assign(n + 1, -1);
		siz.assign(n + 1, 0);
		stk.clear();
		cur = cnt = 0;
	}


	SCC() {}
	SCC(int n)
	{
		initial(n);
	}

	void addEdge(int u, int v)
	{
		adj[u].push_back(v);
	}

	void tarjan(int u)
	{
		dfn[u] = low[u] = cur ++;
		stk.push_back(u);

		for(auto v : adj[u])
		{
			if(dfn[v] == -1)
			{
				tarjan(v);
				low[u] = min(low[u], low[v]);
			}
			else if(bel[v] == -1) low[u] = min(low[u], dfn[v]);
		}

		if(dfn[u] == low[u])
		{
			int pre; cnt ++;
			do
			{
				pre = stk.back();
				bel[pre] = cnt;
				siz[cnt] ++;
				stk.pop_back();
			}while(pre != u);
		}
	}
	auto work()
	{
		for(int i = 1; i <= n; i ++)
			if(dfn[i] == -1)
				tarjan(i);
		vector<vector<int>> dag(cnt + 1);
		for(int i = 1; i <= n; i ++)
		{
			for(auto j : adj[i])
			{
				int a = bel[i], b = bel[j];
				if(a != b) dag[a].push_back(b);
			}
		}
		return dag;
	}

	int get_cnt()
	{
		return cnt;
	}
	auto get_bel()
	{
		return bel;
	}
	auto get_siz()
	{
		return siz;
	}

};
//性质:缩点后的图拥有拓扑序,可以不需再另跑一遍topsort,缩点后的图是DAG