auto dijkstra = [&](int s) -> vector<i64>
{
	vector<i64> dist(n + 1, inf);
	vector<bool> st(n + 1);
	priority_queue<pair<i64, int>, vector<pair<i64, int>>, greater<>> q;
	q.emplace(0, s); dist[s] = 0;
	while(q.size())
	{
		auto [d, u] = q.top(); q.pop();
		if(st[u]) continue;
		st[u] = 1;

		for(auto [v, w] : adj[u])
		{
			if(dist[v] > d + w)
			{
				dist[v] = d + w;
				q.emplace(dist[v], v);
			}
		}
	}
	return dist;
};