#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
#define MAXN 100010
#define lson (n << 1)
#define rson (lson | 1)
#define lm ((l + r) >> 1)
#define rm (lm + 1)

static int T, N, K, M, A;
static int Tr[MAXN << 2], tag[MAXN << 2];
static int NUM[MAXN << 2], TMP[MAXN << 2], L[MAXN], R[MAXN];
static bool vis[MAXN << 2];

void inline pushdown(int n)
{
	if (tag[n])
	{
		Tr[lson] = Tr[rson] = tag[lson] = tag[rson] = tag[n];
		tag[n] = 0;
	}
}

void modify(int n, int l, int r, int fl, int fr, int x)
{
	if (fl <= l && r <= fr)
	{
		Tr[n] = tag[n] = x;
		return ;
	}
	pushdown(n);
	if (fl <= lm) modify(lson, l, lm, fl, fr, x);
	if (fr >= rm) modify(rson, rm, r, fl, fr, x);
}

void query(int n, int l, int r)
{
	if (l == r)
	{
		if (Tr[n])
		{
			if (!vis[Tr[n]]) A++, vis[Tr[n]] = true;
		}
		return ;
	}
	pushdown(n);
	query(lson, l, lm); query(rson, rm, r);
}

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &N);
		K = M = A = 0;
		for (int i = 0; i < N; i++) scanf("%d%d", &L[i], &R[i]), TMP[K++] = L[i], TMP[K++] = R[i];
		sort(TMP, TMP + K);
		NUM[M++] = TMP[0];
		for (int i = 1; i < K; i++)
			if (TMP[i] != TMP[i-1])
			{
				if (TMP[i] > (TMP[i-1] + 1)) NUM[M++] = TMP[i] - 1;
				NUM[M++] = TMP[i];
			}
		memset(Tr, 0, sizeof(Tr));
		memset(tag, 0, sizeof(tag));
		memset(vis, 0, sizeof(vis));
		for (int i = 0; i < N; i++)
		{
			int l = lower_bound(NUM, NUM + M, L[i]) - NUM, r = lower_bound(NUM, NUM + M, R[i]) - NUM;
			modify(1, 0, M - 1, l, r, i + 1);
		}
		query(1, 0, M - 1);
		printf("%d\n", A);
	}
	return 0;
}

