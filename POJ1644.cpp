#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cstring>
#define MAXN 60

static int T, M, K;
static double DP[MAXN][MAXN], ans;
static int A[MAXN];

int main(int argc, char *argv[])
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &M, &K);
		memset(DP, 0, sizeof(DP));
		memset(A, 0, sizeof(A));
		A[M + 2] = -1;
		for (int i = 1; i <= M; i++)
		{
			char buff[10]; scanf("%s", buff);
			if (buff[0] == 'L') A[i] = INT_MAX; else sscanf(buff, "%d", &A[i]);
		}
		DP[0][0] = 1.0;
		for (int i = 0; i < K; i++)
			for (int j = 0; j <= M; j++)
			{
				if (A[j + 1] == INT_MAX)
					DP[j + 1][i + 2] += DP[j][i] * 0.5;
				else
					DP[j + A[j + 1] + 1][i + 1] += DP[j][i] * 0.5;
				if (A[j + 2] == INT_MAX)
					DP[j + 2][i + 2] += DP[j][i] * 0.5;
				else
					DP[j + A[j + 2] + 2][i + 1] += DP[j][i] * 0.5;
			}
		ans = 0;
		for (int i = 0; i <= K; i++) ans += DP[M + 1][i];
		if (ans == 0.5)
			printf("Push. 0.5000\n");
		else
			printf("Bet %s. %.4f\n", ((ans > 0.5) ? "for" : "against"), ans);
	}
	return 0;
}
