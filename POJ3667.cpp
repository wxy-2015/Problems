#include <cstdio>
#include <cstdlib>
#define MAXN 50010
#define lson (n << 1)
#define rson (lson | 1)
#define lm ((l + r) >> 1)
#define rm (lm + 1)

static int N, M;
static int Tr[MAXN << 2], lMax[MAXN << 2], rMax[MAXN << 2];
static int tag[MAXN << 2];

int inline max(int x, int y) { return x > y ? x : y; }

void build(int n, int l, int r)
{
	if (l != r) build(lson, l, lm), build(rson, rm, r);
	Tr[n] = lMax[n] = rMax[n] = r - l + 1;
}

void inline pushdown(int n, int l, int r)
{
	if (tag[n])
	{
		tag[lson] = tag[rson] = tag[n];
		Tr[lson] = lMax[lson] = rMax[lson] = (tag[n] > 0) * (rm - l);
		Tr[rson] = lMax[rson] = rMax[rson] = (tag[n] > 0) * (r - lm);
		tag[n] = 0;
	}
}

void modify(int n, int l, int r, int fl, int fr, int x)
{
	if (fl <= l && r <= fr)
	{
		tag[n] = x ? 1 : -1;
		Tr[n] = lMax[n] = rMax[n] = x * (r - l + 1);
		return ;
	}
	pushdown(n, l, r);
	if (fl <= lm) modify(lson, l, lm, fl, fr, x);
	if (fr >= rm) modify(rson, rm, r, fl, fr, x);
	Tr[n] = max(rMax[lson] + lMax[rson], max(Tr[lson], Tr[rson]));
	lMax[n] = (lMax[lson] == rm - l) ? Tr[lson] + lMax[rson] : lMax[lson];
	rMax[n] = (rMax[rson] == r - lm) ? Tr[rson] + rMax[lson] : rMax[rson];
}

int query(int n, int l, int r, int x)
{
	if (l == r) return 1;
	pushdown(n, l, r);
	if (Tr[lson] >= x) return query(lson, l, lm, x);
	if (rMax[lson] + lMax[rson] >= x) return lm - rMax[lson] + 1;
	return query(rson, rm, r, x);
}

int main()
{
	scanf("%d%d", &N, &M);
	build(1, 1, N);
	while (M--)
	{
		int op, x, y, q;
		scanf("%d%d", &op, &x);
		if (op == 1)
		{
			if (Tr[1] < x)
				printf("0\n");
			else
				printf("%d\n", q = query(1, 1, N, x)), modify(1, 1, N, q, q + x - 1, 0);
		}
		else
		{
			scanf("%d", &y);
			modify(1, 1, N, x, x + y - 1, 1);
		}
	}
	return 0;
}

