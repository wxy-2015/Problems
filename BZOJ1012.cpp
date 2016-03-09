// SEGMENT TREE VERSION ARRAY
#include <cstdio>
#include <cstdlib>
#include <climits>
#define MAXN 200010
#define m ((l + r) >> 1)
#define lson (n << 1)
#define rson (lson | 1)

static int Tr[4*MAXN];
static int N, D, T, L, x;

int inline max(int x, int y)
{
	return (x > y) ? x : y;
}

void modify(int n, int l, int r, int p, int x)
{
// printf("[M]Access [%3d, %3d] of %3d.\n", l, r, n);
	if (l == r) { Tr[n] = x; return ; }
	if (p <= m)
		modify(lson, l,   m, p, x);
	else
		modify(rson, m+1, r, p, x);
	Tr[n] = max(Tr[lson], Tr[rson]);
}

int search(int n, int l, int r, int fl, int fr)
{
// printf("[S]Access [%3d, %3d] of %3d.\n", l, r, n);
	if (l >= fl && r <= fr) return Tr[n];
	int ans = INT_MIN;
	if (fl <= m) ans = max(ans, search(lson, l  , m, fl, fr));
	if (fr >  m) ans = max(ans, search(rson, m+1, r, fl, fr));
	return ans;
}

int main(int argc, char *argv[])
{
	scanf("%d%d", &N, &D);
	for (int i = 0; i < N; i++)
	{
		char op[2];
		scanf("%s%d", op, &x);
		if (op[0] == 'A')
			modify(1, 1, N, ++L, (x + T) % D);
		else
			printf("%d\n", T = search(1, 1, N, L-x+1, L));
	}
	return 0;
}