#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;
#define MAXN 2000

static int N, M, T, maxE, minS, sumP, ans, delta;
static int Gr[MAXN][MAXN], D[MAXN], Q[MAXN << 2];
static int P[MAXN], S[MAXN], E[MAXN];

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

int dfs(int x, int f)
{
	if (x == 1) return f;
	int r = 0;
	for (int v = 0; v < T && r < f; v++)
		if (Gr[x][v] > 0 && D[v] == D[x] + 1)
		{
			int delta = dfs(v, min(f - r, Gr[x][v]));
			r += delta;
			Gr[x][v] -= delta;
			Gr[v][x] += delta;
		}
	if (!r) D[x] = 0;
	return r;
}

int main()
{
	scanf("%*d");
	for (int t = 1; ~scanf("%d%d", &N, &M); t++)
	{
		maxE = sumP = 0; minS = INT_MAX;
		for (int i = 0; i < N; i++)
		{
			scanf("%d%d%d", &P[i], &S[i], &E[i]);
			sumP += P[i];
			maxE = max(maxE, E[i]);
			minS = min(minS, S[i]);
		}
		T = maxE + N + 3;
		memset(Gr, 0, sizeof(Gr));
		for (int i = 0; i < N; i++)
		{
			Gr[0][i+2] = P[i];
			for (int j = S[i]; j <= E[i]; j++) Gr[i+2][j+N+2] = 1;
		}
		for (int i = minS; i < maxE; i++) Gr[i+N+2][1] = M;
		for (ans = 0; bfs(); ) while ((delta = dfs(0, INT_MAX)) > 0) ans += delta;
		printf("Case %d: %s\n\n", t, (ans == sumP) ? "Yes" : "No");
	}
	return 0;
}

