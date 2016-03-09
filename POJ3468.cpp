#include <cstdio>
#include <cstdlib>
#define MAXN 100010
#define lson (n << 1)
#define rson (lson | 1)
#define lm ((l + r) >> 1)
#define rm (lm + 1)

static long long Tr[4 * MAXN], Tag[4 * MAXN];
static int N, Q, x, y, z;
static char op[2];

void inline pushdown(int n, int l, int r)
{
	if (Tag[n])
	{
		Tag[lson] += Tag[n]; Tr[lson] += Tag[n] * (rm - l);
		Tag[rson] += Tag[n]; Tr[rson] += Tag[n] * (r - lm);
		Tag[n] = 0;
	}
}

void build(int n, int l, int r)
{
	if (l == r)
	{
		scanf("%lld", &Tr[n]);
		return;
	}
	build(lson, l, lm);
	build(rson, rm, r);
	Tr[n] = Tr[lson] + Tr[rson];
}

void modify(int n, int l, int r, int fl, int fr, int x)
{
	if (fl <= l && r <= fr)
	{
		Tag[n] += (long long)
		x;
		Tr[n] += (long long)x * (r - l + 1);
		return;
	}
	pushdown(n, l, r);
	if (fl <= lm) modify(lson, l, lm, fl, fr, x);
	if (fr >= rm) modify(rson, rm, r, fl, fr, x);
	Tr[n] = Tr[lson] + Tr[rson];
}

long long find(int n, int l, int r, int fl, int fr)
{
	if (fl <= l && r <= fr)
		return Tr[n];
	pushdown(n, l, r);
	long long ans = 0;
	if (fl <= lm) ans += find(lson, l, lm, fl, fr);
	if (fr >= rm) ans += find(rson, rm, r, fl, fr);
	return ans;
}

int main(int argc, char *argv[])
{
	scanf("%d%d", &N, &Q);
	build(1, 1, N);
	while (Q--)
	{
		scanf("%s", op);
		if (op[0] == 'C')
			scanf("%d%d%d", &x, &y, &z),
			modify(1, 1, N, x, y, z);
		else
			scanf("%d%d", &x, &y),
			printf("%lld\n", find(1, 1, N, x, y));
	}
	return 0;
}
