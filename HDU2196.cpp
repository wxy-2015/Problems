#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 10010

static int H[MAXN], N, T = 1;
static struct
{
	int u, v, w, next;
} Gr[MAXN << 1];
static int DP[MAXN][3];

int inline max(int x, int y) { return x > y ? x : y; }

void inline add_edge(int u, int v, int w)
{
	Gr[T].u = u; Gr[T].v = v; Gr[T].w = w;
	Gr[T].next = H[u]; H[u] = T++;
}

int dfs1(int x, int fa)
{
	DP[x][0] = DP[x][1] = 0;
	for (int i = H[x]; i; i = Gr[i].next)
		if (Gr[i].v != fa)
		{
			int t = dfs1(Gr[i].v, x) + Gr[i].w;
			if (DP[x][0] < t)
				DP[x][1] = DP[x][0], DP[x][0] = t;
			else if(DP[x][1] < t)
				DP[x][1] = t;
		}
	return DP[x][0];
}

void dfs2(int x, int fa)
{
	for (int i = H[x]; i; i = Gr[i].next)
		if (Gr[i].v != fa)
		{
			if (DP[Gr[i].v][0] + Gr[i].w == DP[x][0])
				DP[Gr[i].v][2] = max(DP[x][1], DP[x][2]) + Gr[i].w;
			else
				DP[Gr[i].v][2] = max(DP[x][0], DP[x][2]) + Gr[i].w;
			dfs2(Gr[i].v, x);
		}
}

int main(int argc, char *argv[])
{
	while (~scanf("%d", &N))
	{
		T = 1;
		memset(H, 0, sizeof(H));
		for (int i = 2; i <= N; i++)
		{
			int v, w;
			scanf("%d%d", &v, &w);
			add_edge(i, v, w); add_edge(v, i, w);
		}
		dfs1(1, 0); dfs2(1, 0);
		for (int i = 1; i <= N; i++) printf("%d\n", max(DP[i][0], DP[i][2]));
	}
}
