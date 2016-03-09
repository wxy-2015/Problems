#include <cstdio>
#include <cstdlib>
#define MAXN 400010

static struct
{
	int v, n;
} Gr[2 * MAXN];
static int head[MAXN], htop = 1;
static int fa[MAXN];
static int tK[MAXN], N, M, K;

int find(int x) { return (fa[x] == x) ? x : find(fa[x]); }

void inline add_edge(int u, int v)
{
	Gr[htop].v = v;
	Gr[htop].n = head[u];
	head[u] = htop++;
}

int main(int argc, char *argv[])
{
	scanf("%d%d", &N, &M);
	for (int i = 0; i < M; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add_edge(u, v);
		add_edge(v, u);
	}
	scanf("%d", &K);
	for (int i = 0; i < K; i++) scanf("%d", &tK[i]);
	
	return 0;
}
