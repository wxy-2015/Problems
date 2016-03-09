#include <cstdio>
#include <cstdlib>
#define MAXN 1010

static int T, N, ans;
static int A[MAXN], B[MAXN];

void merge(int l, int r)
{
	if (l >= r) return ;
	int m = (l + r) >> 1;
	merge(l, m); merge(m + 1, r);
	int i = l, j = m + 1, k = l;
	while (i <= m && j <= r)
		if (A[i] > A[j])
			B[k++] = A[j++], ans += m - i + 1;
		else
			B[k++] = A[i++];
	while (i <= m) B[k++] = A[i++];
	while (j <= r) B[k++] = A[j++];
	for (i = l; i <= r; i++) A[i] = B[i];
}

int main(int argc, char *argv[])
{
	scanf("%d", &T);
	for (int j = 1; j <= T; j++)
	{
		scanf("%d", &N);
		for (int i = 0; i < N; i++) scanf("%d", &A[i]);
		ans = 0;
		merge(0, N-1);
		printf("Scenario #%d:\n%d\n\n", j, ans);
	}
	return 0;
}
