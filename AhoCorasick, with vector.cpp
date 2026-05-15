struct AhoCorasick
{
	static constexpr int ALPHABET = 26;
	struct Node
	{
		int len;
		int fail;//失配指针
		int link;//后缀链接
		array<int, ALPHABET> next;
		int cnt;
		int siz;

		Node() : fail{}, link{}, next{}, cnt{}, siz{} {}
	};

	vector<Node> t;

	void initial()
	{
		t.assign(2, Node());
		t[0].next.fill(1);//0作为哨兵,保证指向根节点1
		t[0].len = -1, t[0].link = 1;
		t[1].len = 0;	
	}

	AhoCorasick()
	{
		initial();
	}

	int newNode()
	{
		t.emplace_back();
		return t.size() - 1;
	}

	int add(const vector<int> &a)
	{
		int p = 1;
		for(auto x : a)
		{
			if(t[p].next[x] == 0)
			{
				t[p].next[x] = newNode();
				t[t[p].next[x]].len = t[p].len + 1;
			}
			p = t[p].next[x];
		}
		t[p].cnt ++;
		return p;
	}
	int add(const string &s, char offset = 'a')
	{
		vector<int> a(s.size());
		for(int i = 0; s[i]; i ++)
			a[i] = s[i] - offset;
		return add(a);
	}

	void work()
	{
		queue<int> q;
		q.push(1);

		while(q.size())
		{
			auto x = q.front(); q.pop();

			for(int i = 0; i < ALPHABET; i ++)
			{
				if(t[x].next[i] == 0)//son不存在,看fail的son
					t[x].next[i] = t[t[x].fail].next[i];
				else//son存在
				{
					//son的fail指向fail的son
					t[t[x].next[i]].fail = t[t[x].fail].next[i];
					//son的fail有意义吗? 有 -> fail : 无 -> fail的link
					t[t[x].next[i]].link = t[t[t[x].next[i]].fail].cnt > 0 ? t[t[x].next[i]].fail : t[t[t[x].next[i]].fail].link;
					q.push(t[x].next[i]);
				}
			}
		}
	}

	int next(int p, int x)
	{
		return t[p].next[x];
	}
	int next(int p, char c, char offset = 'a')
	{
		return next(p, c - offset);
	}
	int fail(int p)
	{
		return t[p].fail;
	}
	int link(int p)
	{
		return t[p].link;
	}
	int len(int p)
	{
		return t[p].len;
	}
	int size()
	{
		return t.size();
	}
	
	void calc(const string &s, char offset = 'a')
	{
	    int p = 1;
	    for(auto c : s)
	    {
	        p = next(p, c);
	        t[p].siz ++;
	    }
	}
	
	void FailTree()
	{
	    vector<int> node;
	    for(int i = 2; i < t.size(); i ++)
	        node.push_back(i);
	    sort(node.begin(), node.end(), [&](int a, int b){ return t[a].len > t[b].len; });
	    for(auto u : node)
	    {
	        int f = t[u].link;
	        if(f > 1) t[f].siz += t[u].siz;
	    }
	}
};