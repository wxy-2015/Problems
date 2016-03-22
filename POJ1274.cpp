#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1000

static int N, M, ans;
static int Lk[MAXN], D[MAXN];
static int Gr[MAXN][MAXN];

bool dfs(int x)
{
	for (int v = 0; v < M; v++)
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
	while (~scanf("%d%d", &N, &M))
	{
		ans = 0;
		memset(Gr, 0, sizeof(Gr));
		memset(Lk, -1, sizeof(Lk));
		for (int i = 0; i < N; i++)
		{
			int S, x;
			scanf("%d", &S);
			for (int j = 0; j < S; j++)
			{
				scanf("%d", &x);
				Gr[i][x-1] = 1;
			}
		}
		for (int i = 0; i < N; i++)
		{
			memset(D, 0, sizeof(D));
			if (dfs(i)) ans++;
		}
		printf("%d\n", ans);
	}
	return 0;
}

