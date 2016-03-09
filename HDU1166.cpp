#include <cstdio>
#include <cstdlib>
#define MAXN 50010
#define lson (n << 1)
#define rson (n << 1 | 1)
#define ml ((l + r) >> 1)
#define mr (ml + 1)

static int Tr[MAXN << 2];
static int T, N, a, b;

int inline max(int x, int y) { return (x > y) ? x : y; }

void build(int n, int l, int r)
{
	if (l == r)
	{
		scanf("%d", &Tr[n]);
		return ;
	}
	build(lson, l, ml);
	build(rson, mr, r);
	Tr[n] = Tr[lson] + Tr[rson];
}

int modify(int n, int l, int r, int p, int x)
{
	if (l == r) return Tr[n] += x;
	if (p < mr) modify(lson, l, ml, p, x); else modify(rson, mr, r, p, x);
	return Tr[n] = Tr[lson] + Tr[rson];
}

int query(int n, int l, int r, int fl, int fr)
{
	if (fl <= l && r <= fr)
		return Tr[n];
	int ans = 0;
	if (fl <= ml) ans += query(lson, l, ml, fl, fr);
	if (fr >= mr) ans += query(rson, mr, r, fl, fr);
	return ans;
}

int main(int argc, char *argv[])
{
	static char op[20];
	scanf("%d", &T);
	for (int i = 1; i <= T; i++)
	{
		scanf("%d", &N);
		printf("Case %d:\n", i);
		build(1, 1, N);
		while (true)
		{
			scanf("%s", op);
			if (op[0] == 'E') break;
			scanf("%d%d", &a, &b);
			if (op[0] == 'Q')
				printf("%d\n", query(1, 1, N, a, b));
			else if (op[0] == 'A')
				modify(1, 1, N, a, b);
			else
				modify(1, 1, N, a,-b);
		}
	}
	return 0;
}
