#include <cstdio>
#include <cstdlib>
#define MAXN 100010
#define lson (n << 1)
#define rson (lson | 1)
#define lm ((l + r) >> 1)
#define rm (lm + 1)

static int Tr[MAXN << 2], tag[MAXN << 2];
static int N, M, T;

void build(int n, int l, int r)
{
	tag[n] = 0;
	if (l == r)
		Tr[n] = 1;
	else
		build(lson, l, lm), build(rson, rm, r),
		Tr[n] = Tr[lson] + Tr[rson];
}

void modify(int n, int l, int r, int fl, int fr, int x)
{
	if (fl <= l && r <= fr)
	{
		Tr[n] = (tag[n] = x) * (r - l + 1);
		return ;
	}
	if (tag[n])
	{
		tag[lson] = tag[rson] = tag[n];
		Tr[lson] = (rm - l) * tag[n];
		Tr[rson] = (r - lm) * tag[n];
		tag[n] = 0;
	}
	if (fl <= lm) modify(lson, l, lm, fl, fr, x);
	if (fr >= rm) modify(rson, rm, r, fl, fr, x);
	Tr[n] = Tr[lson] + Tr[rson];
}

int main()
{
	scanf("%d", &T);
	for (int i = 1; i <= T; i++)
	{
		scanf("%d%d", &N, &M);
		build(1, 1, N);
		while (M--)
		{
			int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			modify(1, 1, N, x, y, z);
		}
		printf("Case %d: The total value of the hook is %d.\n", i, Tr[1]);
	}
	return 0;
}

