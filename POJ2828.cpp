#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200010
#define lson (n << 1)
#define rson (lson | 1)
#define lm ((l + r) >> 1)
#define rm (lm + 1)

static int N, Tr[MAXN << 2], P[MAXN], V[MAXN], A[MAXN];

int modify(int n, int l, int r, int p)
{
	if (l == r)
	{
		Tr[n] = 1;
		return l;
	}
	int ret;
	if (rm - l - Tr[lson] > p)
		ret = modify(lson, l, lm, p);
	else
		ret = modify(rson, rm, r, p - rm + l + Tr[lson]);
	Tr[n] = Tr[lson] + Tr[rson];
	return ret;
}

int main()
{
	while (~scanf("%d", &N))
	{
		memset(Tr, 0, sizeof(Tr));
		for (int i = 0; i < N; i++) scanf("%d%d", &P[i], &V[i]);
		for (int i = N - 1; i >= 0; i--)
			A[modify(1, 0, N - 1, P[i])] = V[i];
		for (int i = 0; i < N; i++) printf("%d ", A[i]);
		putchar('\n');
	}
	return 0;
}

