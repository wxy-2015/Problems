#include <cstdio>
#include <cstdlib>
#include <cmath>
#define MAXN 100010

static int N, M, x, y, k;
static int A[MAXN], ST[MAXN][20];

int inline max(int x, int y) { return (x > y) ? x : y; }

int inline rmq(int l, int r)
{
	if (l > r) return 0;
	k = log((double)(r - l + 1)) / log(2.0);
	return max(ST[l][k], ST[r-(1<<k)+1][k]);
}

int main(int argc, char *argv[])
{
	while (scanf("%d", &N), N)
	{
		scanf("%d%d", &M, &A[1]);
		ST[1][0] = 1;
		for (int i = 2; i <= N; i++)
		{
			scanf("%d", &A[i]);
			if (A[i] == A[i-1])
				ST[i][0] = ST[i-1][0] + 1;
			else
				ST[i][0] = 1;
		}
		k = log((double)(N + 1)) / log(2.0);
		for (int j = 1; j <= k; j++)
			for (int i = 1; i + (1 << j) - 1 <= N; i++)
				ST[i][j] = max(ST[i][j-1], ST[i+(1<<(j-1))][j-1]);
		while (M--)
		{
			scanf("%d%d", &x, &y);
			for (k = x; k <= y && A[k] == A[k-1]; ) k++;
			printf("%d\n", max(rmq(k, y), k - x));
		}
	}
	return 0;
}
