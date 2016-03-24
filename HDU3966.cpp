#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
#define MAXN 50010
#define lson (n << 1)
#define rson (lson | 1)
#define lm ((l + r) >> 1)
#define rm (lm + 1)

static struct
{
	int v, next;
} Gr[MAXN << 1];
static int H[MAXN], A[MAXN], X[MAXN], F[MAXN], N, M, Q, atop;
static int dep[MAXN], siz[MAXN], son[MAXN], top[MAXN], adr[MAXN], fin[MAXN];
static int Tr[MAXN << 2];

void inline add_edge(int u, int v)
{
	Gr[Q].v = v; Gr[Q].next = H[u]; H[u] = Q++;
}

int dfs1(int x, int fa, int dp)
{
	siz[x] = 1;
	dep[x] = dp;
	F[x] = fa;
	for (int i = H[x]; ~i; i = Gr[i].next)
		if (Gr[i].v != fa)
		{
			siz[x] += dfs1(Gr[i].v, x, dp + 1);
			if (!son[x] || siz[son[x]] < siz[Gr[i].v])
				son[x] = Gr[i].v;
		}
	return siz[x];
}

int dfs2(int x, int t)
{
	top[x] = t;
	adr[x] = atop++;
	fin[x] = son[x] ? dfs2(son[x], t) : adr[x];
	for (int i = H[x]; ~i; i = Gr[i].next)
		if (Gr[i].v != F[x] && Gr[i].v != son[x]) fin[x] = dfs2(Gr[i].v, Gr[i].v);
	return fin[x];
}

void inline pushdown(int n, int l, int r)
{
	if (Tr[n])
	{
		Tr[lson] += Tr[n];
		Tr[rson] += Tr[n];
		Tr[n] = 0;
	}
}

void build(int n, int l, int r)
{
	Tr[n] = 0;
	if (l != r)
		build(lson, l, lm), build(rson, rm, r);
}

void modify(int n, int l, int r, int fl, int fr, int x)
{
	if (fl <= l && r <= fr)
	{
		Tr[n] += x;
		return ;
	}
	pushdown(n, l, r);
	if (fl <= lm) modify(lson, l, lm, fl, fr, x);
	if (fr >= rm) modify(rson, rm, r, fl, fr, x);
}

int query(int n, int l, int r, int p)
{
	if (l == r) return A[l] + Tr[n];
	pushdown(n, l, r);
	if (p <= lm) return query(lson, l, lm, p); else return query(rson, rm, r, p);
}

int main()
{
	while (~scanf("%d%*d%d", &N, &M))
	{
		Q = atop = 0;
		memset(H, -1, sizeof(H));
		memset(son, 0, sizeof(son));
		for (int i = 1; i <= N; i++) scanf("%d", &X[i]);
		for (int i = 1; i < N; i++)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			add_edge(u, v);
			add_edge(v, u);
		}
		dfs1(1, 0, 0);
		dfs2(1, 1);
		for (int i = 1; i <= N; i++) A[adr[i]] = X[i];
		build(1, 0, N-1);
		while (M--)
		{
			char op[2];
			int x, y, z;
			scanf("%s", op);
			if (op[0] == 'I' || op[0] == 'D')
			{
				scanf("%d%d%d", &x, &y, &z);
				if (op[0] == 'D') z = -z;
				for (; top[x] != top[y]; x = F[top[x]])
				{
					if (dep[top[x]] < dep[top[y]]) swap(x, y);
					modify(1, 0, N-1, adr[top[x]], adr[x], z);
				}
				if (dep[x] > dep[y]) swap(x, y);
				modify(1, 0, N-1, adr[x], adr[y], z);
			}
			else
			{
				int p;
				scanf("%d", &p);
				printf("%d\n", query(1, 0, N-1, adr[p]));
			}
		}
	}
	return 0;
}

