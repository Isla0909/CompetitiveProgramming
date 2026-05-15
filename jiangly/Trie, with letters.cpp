int trie[N][26], cnt[N];
i64 val[N];
int tot;

int newNode()
{
	tot ++;
	fill(trie[tot], trie[tot] + 26, 0);
	val[tot] = inf;
	return tot;
}

void initial()
{
	tot = 0;
	newNode();
}

void add(const string &s, char offset = 'a')
{
	int p = 1;
	for(int i = 0; s[i]; i ++)
	{
		int x = s[i] - offset;
		if(!trie[p][x]) trie[p][x] = newNode();

		p = trie[p][x];
	}
	cnt[p] ++;
}

int query(const string &s, char offset = 'a')
{
	int p = 1;
	for(int i = 0; s[i]; i ++)
	{
		int x = s[i] - offset;
		p = trie[p][x];

		if(!p) return 0;
	}
	return cnt[p];
}
//注:函数开始时必须调用initial