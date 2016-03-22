#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1010

static int K, N, M, ans;
static int Lk[MAXN], D[MAXN];
static int Gr[MAXN][MAXN];

bool dfs(int x)
{
	for (int v = 1; v <= M; v++)
		if (Gr[x][v] && !D[v])
		{
			D[v] = 1;
			int tmp = Lk[v]; Lk[v] = x;
			if (!~tmp || dfs(tmp)) return true;
			Lk[v] = tmp;
		}
	return false;
}

int main()
{
	while (~scanf("%d", &K) && K)
	{
		scanf("%d%d", &N, &M);
		memset(Gr, 0, sizeof(Gr));
		for (int i = 0; i < K; i++)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			Gr[x][y] = 1;
		}
		ans = 0;
		memset(Lk, -1, sizeof(Lk));
		for (int i = 1; i <= N; i++)
		{
			memset(D, 0, sizeof(D));
			if (dfs(i)) ans++;
		}
		printf("%d\n", ans);
	}
	return 0;
}
