#include <cstdio>
#include <cstdlib>
#define MAXN 100010
#define lson (n << 1)
#define rson (lson | 1)
#define ml ((l + r) >> 1)
#define mr (ml + 1)

static struct
{
	int v, n;
} Gr[MAXN];
static int fa[MAXN], sz[MAXN], son[MAXN];
static int top[MAXN], end[MAXN], adr[MAXN];
static int head[MAXN], STr[4 * MAXN], tag[4 * MAXN];
static int N, M, atop = 0, x, ans;
static char op[20];

int inline max(int x, int y) { return (x > y) ? x : y; }

int dfs1(int x)
{
	sz[x] = 1;
	for (int i = head[x]; i; i = Gr[i].n)
	{
		sz[x] += dfs1(Gr[i].v);
		if (!son[x] || sz[son[x]] < sz[Gr[i].v])
			son[x] = Gr[i].v;
	}
	return sz[x];
}

int dfs2(int x, int t)
{
	top[x] = t;
	adr[x] = atop++;
	end[x] = son[x] ? dfs2(son[x], t) : adr[x];
	for (int i = head[x]; i; i = Gr[i].n)
		if (Gr[i].v != son[x]) end[x] = dfs2(Gr[i].v, Gr[i].v);
	return end[x];
}

int modify(int n, int l, int r, int fl, int fr, int x)
{
	int ans = 0;
	if (fl <= l && r <= fr)
	{
		ans = x ? r - l + 1 - STr[n] : STr[n];
		tag[n] = x ? 1 : -1;
		STr[n] = (r - l + 1) * x;
		return ans;
	}
	if (tag[n])
	{
		tag[lson] = tag[rson] = tag[n];
		STr[lson] = (ml - l + 1) * (tag[n] > 0);
		STr[rson] = (r - mr + 1) * (tag[n] > 0);
		tag[n] = 0;
	}
	if (fl <= ml) ans += modify(lson, l, ml, fl, fr, x);
	if (fr >= mr) ans += modify(rson, mr, r, fl, fr, x);
	STr[n] = STr[lson] + STr[rson];
	return ans;
}

int main(int argc, char *argv[])
{
	scanf("%d", &N);
	for (int i = 1; i < N; i++)
	{
		scanf("%d", &fa[i]);
		Gr[i].n = head[fa[i]];
		head[fa[i]] = Gr[i].v = i;
	}
	dfs1(0);
	dfs2(0, 0);
	scanf("%d", &M);
	while (M--)
	{
		scanf("%s%d", op, &x);
		if (op[0] == 'i')
			for (ans = 0; ; x = fa[top[x]])
			{
				ans += modify(1, 0, N-1, adr[top[x]], adr[x], 1);
				if (!x) break;
			}
		else
			ans = modify(1, 0, N-1, adr[x], end[x], 0);
		printf("%d\n", ans);
	}
	return 0;
}