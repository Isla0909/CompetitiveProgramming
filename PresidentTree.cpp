#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <unordered_map>
#include <set>
#include <bitset>
#include <cmath>
#include <ctime>
#include <random>
#include <chrono>
#include <functional>
#include <cassert>
#include <iomanip>
#define ff first
#define se second
#define endl '\n'
using namespace std;
using i32 = signed;
using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using u128 = unsigned __int128;
constexpr long long inf = 1e18;

typedef long long ll;
typedef pair<int, int> pii;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

constexpr int N = 2e5 + 10, INF = 0x3f3f3f3f, mod = 1e9 + 7;

struct PresidentTree
{
	int idx = 0;
	int root[N];

	struct node
	{
		int l, r;
		int cnt;
	}tr[4 * N + 17 * N];

	void modify(int &u, int v, int l, int r, int x)
	{
		u = ++idx;
		tr[u] = tr[v];
		tr[u].cnt ++;

		if(l == r) return ;

		int mid = l + r >> 1;
		if(x <= mid) modify(tr[u].l, tr[v].l, l, mid, x);
		else modify(tr[u].r, tr[v].r, mid + 1, r, x);
	}

	int kth(int u, int v, int l, int r, int k)
	{
		if(l == r) return l;

		int c = tr[tr[u].l].cnt - tr[tr[v].l].cnt;
		int mid = l + r >> 1;
		if(k <= c) return kth(tr[u].l, tr[v].l, l, mid, k);
		else return kth(tr[u].r, tr[v].r, mid + 1, r, k - c);
	}
};

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, q; cin >>n >>q;
	vector<int> a(n + 1);
	for(int i = 1; i <= n; i ++) cin >>a[i];
	
	auto b = a;
	sort(b.begin() + 1, b.end());
	b.erase(unique(b.begin() + 1, b.end()), b.end());
	
	auto find = [&](int x) -> int
	{
	    return lower_bound(b.begin() + 1, b.end(), x) - b.begin();  
	};
	int len = b.size() - 1;
	
	PresidentTree tree;
	for(int i = 1; i <= n; i ++)
	{
	    int x = find(a[i]);
	    tree.modify(tree.root[i], tree.root[i - 1], 1, len, x);
	}
	
	while(q --)
	{
	    int l, r, k; cin >>l >>r >>k;
	    int pos = tree.kth(tree.root[r], tree.root[l - 1], 1, len, k);
	    cout <<b[pos] <<endl;
	}
	
	return 0;
}