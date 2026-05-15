auto kmp = [&](string &s, string &t, vector<int> &nex)
{
	int n = s.size(), m = t.size();
	nex.assign(m + 1, 0);
	s = " " + s, t = " " + t;
	for(int i = 2, j = 0; i <= m; i ++)
	{
		while(j && t[i] != t[j + 1])
			j = nex[j];
		if(t[i] == t[j + 1]) j ++;
		nex[i] = j;
	}

	vector<int> pos;
	for(int i = 1, j = 0; i <= n; i ++)
	{
		while(j && s[i] != t[j + 1])
			j = nex[j];
		if(s[i] == t[j + 1]) j ++;
		if(j == m)
		{
			pos.push_back(i - m + 1);
			j = nex[j];
		}
	}
	return pos;
};
//注意 s 和 t 传入的时候是引用, 现在已经是 1-based