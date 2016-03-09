#include <cstdio>
#include <cstdlib>
#define MAXN 5010

static int N, T, tot, ans;
static struct
{
	int x, p;
} A[MAXN], C[MAXN];
static int B[MAXN];

int inline min(int x, int y) { return (x < y) ? x : y; }

void merge(int l, int r)
{
	if (l >= r) return ;
	int m = (l + r) >> 1;
	merge(l, m); merge(m + 1, r);
	int i = l, j = m + 1, k = l;
	while (i <= m && j <= r)
		if (A[i].x > A[j].x)
			C[k++] = A[j++], tot += m - i + 1;
		else
			C[k++] = A[i++];
	while (i <= m) C[k++] = A[i++];
	while (j <= r) C[k++] = A[j++];
	for (i = l; i <= r; i++) A[i] = C[i];
}

int main(int argc, char *argv[])
{
	while (~scanf("%d", &N))
	{
		tot = T = 0;
		for (int i = 0; i < N; i++)
			scanf("%d", &A[i].x), A[i].p = i;
		merge(0, N-1);
		B[A[0].p] = T;
		for (int i = 1; i < N; i++)
			B[A[i].p] = (A[i].x == A[i-1].x) ? T : ++T;
		ans = tot;
		for (int i = 0; i < N; i++)
			ans = min(ans, tot += T - 2 * B[i]);
		printf("%d\n", ans);
	}
	return 0;
}
