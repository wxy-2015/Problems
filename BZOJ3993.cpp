#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
#define MAXN 1000
#define EPS 1e-5
#define INF 1e9

static int N, M, S, T;
static int A[MAXN], B[MAXN], MAP[MAXN][MAXN];
static double Gr[MAXN][MAXN];
static int D[MAXN], Q[MAXN << 2];

bool inline bfs(void)
{
	memset(D, 0, sizeof(D));
	int qr = 0, qf = 0;
	D[Q[qr++] = 0] = 1;
	while (qf < qr)
	{
		int x = Q[qf++];
		if (x == 1) return true;
		for (int v = 0; v < T; v++)
			if (Gr[x][v] > 0 && !D[v])
				D[Q[qr++] = v] = D[x] + 1;
	}
	return false;
}

double dfs(int x, double f)
{
	if (x == 1) return f;
	double r = 0;
	for (int v = 0; v < T && r < f; v++)
		if (Gr[x][v] > 0 && D[v] == D[x] + 1)
		{
			double delta = dfs(v, min(f - r, Gr[x][v]));
			r += delta;
			Gr[x][v] -= delta;
			Gr[v][x] += delta;
		}
	if (r < EPS) D[x] = 0;
	return r;
}

int main()
{
	scanf("%d%d", &N, &M);
	T = N + M + 2;
	for (int i = 0; i < N; i++) scanf("%d", &A[i]), S += A[i];
	for (int i = 0; i < M; i++) scanf("%d", &B[i]);
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &MAP[i][j]);
	double L = 0, R = (double)S;
	while (L + EPS < R)
	{
		double mid = (L + R) / 2.0;
		memset(Gr, 0, sizeof(Gr));
		for (int i = 0; i < N; i++) Gr[i+2][1] = A[i];
		for (int i = 0; i < M; i++) Gr[0][i+N+2] = mid * B[i];
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				if (MAP[i][j]) Gr[i+N+2][j+2] = INF;
		double ans = 0, delta;
		while (bfs()) while ((delta = dfs(0, INF)) > EPS) ans += delta;
		if (fabs(ans - (double)S) < EPS) R = mid; else L = mid;
	}
	printf("%.4lf", L);
	return 0;
}

