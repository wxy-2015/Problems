#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
#define lson (n << 1)
#define rson (lson | 1)
#define lm ((l + r) >> 1)
#define rm (lm + 1)

static int Tr[MAXN << 2], tag[MAXN << 2];
static int N, T, M, x, y, z;
static char op[2];

void build(int n, int l, int r)
{
	Tr[n] = 1; tag[n] = 0;
	if (l != r) build(lson, l, lm), build(rson, rm, r);
}

void inline pushdown(int n)
{
	if (tag[n])
	{
		Tr[lson] = Tr[rson] = tag[lson] = tag[rson] = tag[n];
		tag[n] = 0;
	}
}

void modify(int n, int l, int r, int fl, int fr, int p)
{
	if (fl <= l && r <= fr)
	{
		Tr[n] = tag[n] = (1 << p);
		return ;
	}
	pushdown(n);
	if (fl <= lm) modify(lson, l, lm, fl, fr, p);
	if (fr >= rm) modify(rson, rm, r, fl, fr, p);
	Tr[n] = Tr[lson] | Tr[rson];
}

int query(int n, int l, int r, int fl, int fr)
{
	if (fl <= l && r <= fr)	return Tr[n];
	pushdown(n);
	int ans = 0;
	if (fl <= lm) ans |= query(lson, l, lm, fl, fr);
	if (fr >= rm) ans |= query(rson, rm, r, fl, fr);
	return ans;
}

int inline translate(int x)
{
	int ans = 0;
	for (; x; x >>= 1) ans += x & 1;
	return ans;
}

int main()
{
	scanf("%d%d%d", &N, &T, &M);
	build(1, 1, N);
	while (M--)
	{
		scanf("%s%d%d", op, &x, &y);
		if (x > y)
		{
			int t = x; x = y; y = t;
		}
		if (op[0] == 'C')
			scanf("%d", &z), modify(1, 1, N, x, y, z - 1);
		else
			printf("%d\n", translate(query(1, 1, N, x, y)));
	}
	return 0;
}

