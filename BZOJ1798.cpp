#include <cstdio>
#include <cstdlib>
#define MAXN 100010
#define lson (n << 1)
#define rson (lson | 1)
#define lm ((l + r) >> 1)
#define rm (lm + 1)

static int N, M, P;
static int A[MAXN];
static long long Tr[MAXN << 2], tagM[MAXN << 2], tagA[MAXN << 2];

int build(int n, int l, int r)
{
	tagM[n] = 1; tagA[n] = 0;
	if (l == r) return Tr[n] = A[l];
	return Tr[n] = build(lson, l, lm) + build(rson, rm, r);	
}

void dfs(int n, int l, int r)
{
	printf("%3d: [%3d, %3d] = %3lld (%3lld, %3lld);\n", n, l, r, Tr[n], tagM[n], tagA[n]);
	if (l != r) dfs(lson, l, lm), dfs(rson, rm, r);
}

void inline pushdown(int n, int l, int r)
{
	if (tagM[n] != 1 || tagA[n])
	{
		tagA[lson] = (tagA[lson] * tagM[n] + tagA[n]) % P;
		tagA[rson] = (tagA[rson] * tagM[n] + tagA[n]) % P;
		tagM[lson] = tagM[lson] * tagM[n] % P;
		tagM[rson] = tagM[rson] * tagM[n] % P;
		Tr[lson] = (Tr[lson] * tagM[n] + tagA[n] * (rm - l)) % P;
		Tr[rson] = (Tr[rson] * tagM[n] + tagA[n] * (r - lm)) % P;
		tagM[n] = 1; tagA[n] = 0;
	}
}

void modifyM(int n, int l, int r, int fl, int fr, int x)
{
	if (fl <= l && r <= fr)
	{
		tagM[n] = tagM[n] * x % P;
		tagA[n] = tagA[n] * x % P;
		Tr[n] = Tr[n] * x % P;
		return ;
	}
	pushdown(n, l, r);
	if (fl <= lm) modifyM(lson, l, lm, fl, fr, x);
	if (fr >= rm) modifyM(rson, rm, r, fl, fr, x);
	Tr[n] = (Tr[lson] + Tr[rson]) % P;
}

void modifyA(int n, int l, int r, int fl, int fr, int x)
{
	if (fl <= l && r <= fr)
	{
		tagA[n] = (tagA[n] + x) % P;
		Tr[n] = (Tr[n] + (long long)(r - l + 1) * x) % P;
		return ;
	}
	pushdown(n, l, r);
	if (fl <= lm) modifyA(lson, l, lm, fl, fr, x);
	if (fr >= rm) modifyA(rson, rm, r, fl, fr, x);
	Tr[n] = (Tr[lson] + Tr[rson]) % P;
}

long long query(int n, int l, int r, int fl, int fr)
{
	if (fl <= l && r <= fr) return Tr[n] % P;
	pushdown(n, l, r);
	long long ans = 0;
	if (fl <= lm) ans = (ans + query(lson, l, lm, fl, fr)) % P;
	if (fr >= rm) ans = (ans + query(rson, rm, r, fl, fr)) % P;
	return ans;
}

int main()
{
	scanf("%d%d", &N, &P);
	for (int i = 1; i <= N; i++) scanf("%d", &A[i]);
	build(1, 1, N);
	scanf("%d", &M);
	while (M--)
	{
		int op, x, y, z;
		scanf("%d%d%d", &op, &x, &y);
		if (op == 1)
			scanf("%d", &z), modifyM(1, 1, N, x, y, z);
		else if (op == 2)
			scanf("%d", &z), modifyA(1, 1, N, x, y, z);
		else
			printf("%lld\n", query(1, 1, N, x, y));
	}
	return 0;
}

