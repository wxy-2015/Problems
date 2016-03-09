#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN ((1 << 7) + 10)

static int N, M, mID;
static float mVal;
static float P[MAXN][MAXN];
static float DP[20][MAXN];

int main(int argc, char *argv[])
{
	while (scanf("%d", &N), ~N)
	{
		M = 1 << N;
		for (int i = 0; i < M; i++)
			for (int j = 0; j < M; j++)
				scanf("%f", &P[i][j]);
		memset(DP, 0, sizeof(DP));
		for (int i = 0; i < M; i++) DP[0][i] = 1;
		for (int i = 1; i <= N; i++)
			for (int j = 0; j < M; j++)
				for (int k = 0; k < M; k++)
					if (((j >> (i - 1)) ^ 1) == (k >> (i - 1)))
						DP[i][j] += DP[i-1][j] * DP[i-1][k] * P[j][k];
		mVal = mID = -1;
		for (int i = 0; i < M; i++)
			if (mVal < DP[N][i]) mVal = DP[N][i], mID = i + 1;
		printf("%d\n", mID);
	}
	return 0;
}
