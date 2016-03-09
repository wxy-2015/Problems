#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#define min(x, y) (((x) < (y)) ? (x) : (y))

static long long Gr[210][210];
static int vis[100010], N, M;

int bfs(void)
{
	static int Q[100010], f, r;
	memset(vis, 0, sizeof(vis));
	Q[f = r = 0] = 1;
	vis[1] = 1;
	while (f <= r)
	{
		int x = Q[f++];
		for (int i = 1; i <= M; i++)
			if (!vis[i] && Gr[x][i] > 0)
				vis[i] = vis[x] + 1, Q[++r] = i;
	}
	return vis[M];
}

long long dfs(int x, long long f)
{
	long long ans = 0;
	if (x == M) return f;
	for (int i = 1; i <= M; i++)
	{
		if (vis[i] == vis[x]+1 && Gr[x][i] > 0)
		{
			long long r = dfs(i, min(f - ans, Gr[x][i]));
			ans += r;
			Gr[x][i] -= r;
			Gr[i][x] += r;
		}
		if (f == ans) break;
	}
	if (!ans) vis[x] = 0;
	return ans;
}

int main(int argc, char *argv[])
{
	while (scanf("%d%d", &N, &M) == 2)
	{
		memset(Gr, 0, sizeof(Gr));
		for (int i = 0; i < N; i++)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			Gr[u][v] += w;
		}
		long long tot = 0, tmp;
		while (bfs()) while ((tmp = dfs(1, INT_MAX)) != 0) tot += tmp;
		printf("%lld\n", tot);
	}
	return 0;
}