#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;
#define MAXN 300

static int N, M, ans, delta;
static int Gr[MAXN][MAXN];
static int D[MAXN], Q[MAXN << 2];

bool bfs(void)
{
	memset(D, 0, sizeof(D));
	int qf = 0, qr = 0;
	Q[qr++] = 1; D[1] = 1;
	while (qf < qr)
	{
		int x = Q[qf++];
		for (int v = 1; v <= M; v++)
			if (!D[v] && Gr[x][v] > 0)
				D[Q[qr++] = v] = D[x] + 1;
	}
	return D[M];
}

int dfs(int x, int f)
{
	if (x == M) return f;
	int r = 0;
	for (int v = 1; v <= M && r < f; v++)
		if (Gr[x][v] > 0 && D[v] == D[x] + 1)
		{
			int delta = dfs(v, min(Gr[x][v], f - r));
			r += delta;
			Gr[x][v] -= delta;
			Gr[v][x] += delta;
		}
	if (!r) D[x] = 0;
	return r;
}

int main()
{
	while (~scanf("%d%d", &N, &M))
	{
		ans = 0;
		memset(Gr, 0, sizeof(Gr));
		for (int i = 0; i < N; i++)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			Gr[u][v] += w;
		}
		while (bfs()) while (delta = dfs(1, INT_MAX)) ans += delta;
		printf("%d\n", ans);
	}
	return 0;
}

