#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 40010

static int N, M, T, G;
static int Fa[MAXN], H[MAXN], Q[MAXN];
static struct
{
	int u, v, w, next;
} Gr[MAXN << 2];
static int Dis[MAXN], LCA[MAXN];

int find(int x) { return Fa[x] == x ? x : find(Fa[x]); }

void inline add_edge(int u, int v, int w, int H[])
{
	Gr[G].u = u; Gr[G].v = v; Gr[G].w = w;
	Gr[G].next = H[u]; H[u] = G++;
}

void tarjan(int x, int fa, int dis)
{
	Dis[x] = dis;
	for (int i = H[x]; i; i = Gr[i].next)
		if (Gr[i].v != fa)
			tarjan(Gr[i].v, x, dis + Gr[i].w),
			Fa[Gr[i].v] = x;
	for (int i = Q[x]; i; i = Gr[i].next)
		if (Dis[Gr[i].v] != -1)
			LCA[Gr[i].w] = Dis[x] + Dis[Gr[i].v] - 2 * Dis[find(Gr[i].v)];
}

int main(int argc, char *argv[])
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &N, &M);
		G = 1;
		memset(H, 0, sizeof(H));
		memset(Q, 0, sizeof(Q));
		memset(Dis, -1, sizeof(Dis));
		for (int i = 0; i <= N; i++) Fa[i] = i;
		for (int i = 1; i < N; i++)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			add_edge(u, v, w, H);
			add_edge(v, u, w, H);
		}
		for (int i = 0; i < M; i++)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			add_edge(u, v, i, Q);
			add_edge(v, u, i, Q);
		}
		tarjan(1, 0, 0);
		for (int i = 0; i < M; i++) printf("%d\n", LCA[i]);
	}
}
