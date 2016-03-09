#include <cstdio>
#include <cstdlib>
#define MAXN 1010

static double dp[MAXN][MAXN];
static double pC[MAXN][MAXN], pR[MAXN][MAXN], pD[MAXN][MAXN];
static int R, C;

int main(int argc, char *argv[])
{
	while (scanf("%d%d", &R, &C) == 2)
	{
		for (int i = 1; i <= R; i++)
			for (int j = 1; j <= C; j++)
				scanf("%lf%lf%lf", &pC[i][j], &pR[i][j], &pD[i][j]), dp[i][j] = 0;
		for (int i = R; i; i--)
			for (int j = C; j; j--)
				if ((i != R || j != C) && pC[i][j] != 1)
					dp[i][j] = (pR[i][j] * dp[i][j+1] + pD[i][j] * dp[i+1][j] + 2) / (1 - pC[i][j]);
		printf("%0.3lf\n", dp[1][1]);
	}
	return 0;
}