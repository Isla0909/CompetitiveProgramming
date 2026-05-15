struct SegmentTree
{
	struct node
	{
		int l, r;
		i64 sum, val1, val2, lazy;//val1, val2分别是区间的最大最小值
		bool f;
		i64 set_lazy;
	};
	vector<int> w;
	vector<node> tree;

	void pushup(int u)
	{
		auto pushup = [&](node &p, node &l, node &r) -> void
		{
			p.sum = l.sum + r.sum;
			p.val1 = max(l.val1, r.val1);
			p.val2 = min(l.val2, r.val2);
		};
		pushup(tree[u], tree[u << 1], tree[u << 1 | 1]);
	}

	void initial(int n)
	{
		w.resize(n + 1);
		tree.resize(4 * n + 1);

		auto build = [this](auto &&self, int u, int l, int r) -> void
		{
			if(l == r)
			{
				tree[u] = {l, r, w[l], w[l], w[l], 0, false, -inf};
				return ;
			}
			tree[u] = {l, r, 0, 0, 0, 0, false, -inf};
			int mid = l + r >> 1;
			self(self, u << 1, l, mid), self(self, u << 1 | 1, mid + 1, r);
			pushup(u);
		};
		build(build, 1, 1, n);
	}

	SegmentTree() {}
	SegmentTree(int n)
	{
		initial(n);
	}
	SegmentTree(vector<int> &a)
	{
		int n = a.size() - 1;
		w.resize(n + 1);
		for(int i = 1; i <= n; i ++)
			w[i] = a[i];
		initial(n);
	}

	void apply_set(node &u, i64 set_lazy)
	{
		u.sum = 1LL * (u.r - u.l + 1) * set_lazy;
		u.val1 = u.val2 = u.set_lazy = set_lazy;
		u.f = true;
		u.lazy = 0;
	}

	void apply_add(node &u, i64 lazy)
	{
		if(u.f)
		{
			u.set_lazy += lazy;
			u.sum += 1LL * (u.r - u.l + 1) * lazy;
			u.val1 += lazy, u.val2 += lazy;
		}
		else
		{
			u.sum += 1LL * (u.r - u.l + 1) * lazy;
			u.val1 += lazy, u.val2 += lazy;
			u.lazy += lazy;
		}
	}

	void pushdown(int u)
	{
		if(tree[u].f)//优先处理赋值操作
		{
			apply_set(tree[u << 1], tree[u].set_lazy);
			apply_set(tree[u << 1 | 1], tree[u].set_lazy);
			tree[u].f = false;
		}
		if(tree[u].lazy == 0) return ;
		apply_add(tree[u << 1], tree[u].lazy);
		apply_add(tree[u << 1 | 1], tree[u].lazy);
		tree[u].lazy = 0;
	}

	void rangeSet(int u, int l, int r, int x)
	{
		if(tree[u].l >= l && tree[u].r <= r)
		{
			apply_set(tree[u], x);
			return ;
		}

		pushdown(u);
		int mid = tree[u].l + tree[u].r >> 1;
		if(l <= mid) rangeSet(u << 1, l, r, x);
		if(r >= mid + 1) rangeSet(u << 1 | 1, l, r, x);
		pushup(u);
	}

	void rangeAdd(int u, int l, int r, int x)
	{
		if(tree[u].l >= l && tree[u].r <= r)
		{
			apply_add(tree[u], x);
			return ;
		}

		pushdown(u);

		int mid = tree[u].l + tree[u].r >> 1;
		if(l <= mid) rangeAdd(u << 1, l, r, x);
		if(r >= mid + 1) rangeAdd(u << 1 | 1, l, r, x);
		pushup(u);
	}

	i64 max_query(int u, int l, int r)
	{
		if(tree[u].l >= l && tree[u].r <= r) return tree[u].val1;

		pushdown(u);
		int mid = tree[u].l + tree[u].r >> 1;

		i64 res = -inf;
		if(l <= mid) res = max(res, max_query(u << 1, l, r));
		if(r >= mid + 1) res = max(res, max_query(u << 1 | 1, l, r));
		return res;
	}

	i64 min_query(int u, int l, int r)
	{
		if(tree[u].l >= l && tree[u].r <= r) return tree[u].val2;

		pushdown(u);
		int mid = tree[u].l + tree[u].r >> 1;

		i64 res = inf;
		if(l <= mid) res = min(res, min_query(u << 1, l, r));
		if(r >= mid + 1) res = min(res, min_query(u << 1 | 1, l, r));
		return res;
	}

	i64 rangeSum(int u, int l, int r)
	{
		if(tree[u].l >= l && tree[u].r <= r) return tree[u].sum;

		pushdown(u);
		int mid = tree[u].l + tree[u].r >> 1;

		i64 res = 0;
		if(l <= mid) res += rangeSum(u << 1, l, r);
		if(r >= mid + 1) res += rangeSum(u << 1 | 1, l, r);
		return res;
	}

	int find_first(int u, int ql, int qr, i64 x)//查询区间第一个大于x的数的下标
	{
		//无交集返回-1
		if(tree[u].l > qr || tree[u].r < ql) return -1;

		//完美包含但不满足返回-1
		if(tree[u].l >= ql && tree[u].r <= qr && tree[u].val1 <= x) return -1;

		if(tree[u].l == tree[u].r) return tree[u].l;

		pushdown(u);

		int c = find_first(u << 1, ql, qr, x);
		if(c != -1) return c;
		return find_first(u << 1 | 1, ql, qr, x);
	}

	int find_last(int u, int ql, int qr, i64 x)//查询区间最后一个小于等于x的数的下标
	{
		//无交集返回-1
		if(tree[u].l > qr || tree[u].r < ql) return -1;

		//完美包含但不满足返回-1
		if(tree[u].l >= ql && tree[u].r <= qr && tree[u].val2 > x) return -1;

		if(tree[u].l == tree[u].r) return tree[u].l;

		pushdown(u);

		int c = find_last(u << 1 | 1, ql, qr, x);
		if(c != -1) return c;
		return find_last(u << 1, ql, qr, x);
	}
};
//注:find_first/last中不满足条件就是对条件取反, 并注意对val1, val2进行修改