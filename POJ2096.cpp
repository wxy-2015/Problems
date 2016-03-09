#include <cstdio>
#include <cstdlib>
#define MAXN 1010

static int N, S;
static double DP[MAXN][MAXN];

int main(int argc, char *argv[])
{
	scanf("%d%d", &N, &S);
	for (int i = N; i >= 0; i--)
		for (int j = S; j >= 0; j--)
			if (i != N || j != S)
				DP[i][j] =\
					(double)(DP[i][j+1] * i * (S - j) +\
					DP[i+1][j] * (N - i) * j +\
					DP[i+1][j+1] * (N - i) * (S - j) +\
					N * S) / (N * S - i * j);
	printf("%.4lf\n", DP[0][0]);
	return 0;
}