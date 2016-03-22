#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 2000

static int N, Q, ans;
static int Lk[MAXN], D[MAXN];
static struct
{
	int v, next;
} Gr[MAXN << 2];
static int H[MAXN];

bool dfs(int x)
{
	for (int i = H[x]; ~i; i = Gr[i].next)
		if (!D[Gr[i].v])
		{
			D[Gr[i].v] = 1;
			int tmp = Lk[Gr[i].v]; Lk[Gr[i].v] = x;
			if (!~tmp || dfs(tmp)) return true;
			Lk[Gr[i].v] = tmp;
		}
	return false;
}

void inline add_edge(int u, int v)
{
	Gr[Q].v = v; Gr[Q].next = H[u];
	H[u] = Q++;
}

int main()
{
	while (~scanf("%d", &N))
	{
		ans = Q = 0;
		memset(H, -1, sizeof(H));
		memset(Gr, 0, sizeof(Gr));
		memset(Lk, -1, sizeof(Lk));
		for (int i = 0; i < N; i++)
		{
			int x, v, s;
			scanf("%d:(%d)", &x, &s);
			for (int j = 0; j < s; j++)
			{
				scanf("%d", &v);
				add_edge(x, v);
				add_edge(v, x);
			}
		}
		for (int i = 0; i < N; i++)
		{
			memset(D, 0, sizeof(D));
			if (dfs(i)) ans++;
		}
		printf("%d\n", ans / 2);
	}
	return 0;
}

