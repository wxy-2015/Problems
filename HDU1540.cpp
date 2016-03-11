#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
#define MAXN 50010
#define lson (n << 1)
#define rson (lson | 1)
#define lm ((l + r) >> 1)
#define rm (lm + 1)

static int Tr[MAXN << 2], lMax[MAXN << 2], rMax[MAXN << 2], St[MAXN];
static int N, M, T = 0, x;
static char op[2];

void build(int n, int l, int r)
{
	Tr[n] = lMax[n] = rMax[n] = r - l + 1;
	if (l != r) build(lson, l, lm), build(rson, rm, r);
}

void modify(int n, int l, int r, int p, int x)
{
	if (l == r)
	{
		Tr[n] = lMax[n] = rMax[n] = x;
		return ;
	}
	if (p <= lm) modify(lson, l, lm, p, x); else modify(rson, rm, r, p, x);
	lMax[n] = lMax[lson] + ((lMax[lson] == (rm - l)) ? lMax[rson] : 0);
	rMax[n] = rMax[rson] + ((rMax[rson] == (r - lm)) ? rMax[lson] : 0);
	Tr[n] = max(max(Tr[lson], Tr[rson]), lMax[rson] + rMax[lson]);
}

int query(int n, int l, int r, int p)
{
	if (l == r || Tr[n] == 0 || Tr[n] == (r - l + 1))
		return Tr[n];
	if (p <= lm)
	{
		if (p > (lm - rMax[lson]))
			return query(lson, l, lm, p) + query(rson, rm, r, rm);
		else
			return query(lson, l, lm, p);
	}
	else
	{
		if (p < (rm + lMax[rson]))
			return query(rson, rm, r, p) + query(lson, l, lm, lm);
		else
			return query(rson, rm, r, p);
	}
}

int main()
{
	while (~scanf("%d%d", &N, &M))
	{
		T = 0;
		build(1, 1, N);
		while (M--)
		{
			scanf("%s", op);
			if (op[0] == 'D')
				scanf("%d", &x),
				modify(1, 1, N, St[T++] = x, 0);
			else if (op[0] == 'Q')
				scanf("%d", &x),
				printf("%d\n", query(1, 1, N, x));
			else
				modify(1, 1, N, St[--T], 1);
		}
	}
	return 0;
}

