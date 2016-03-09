#include <cstdio>
#include <cstdlib>
#include <cmath>
#define MAXN 1000010

static struct
{
	double x, y;
} Gr2[MAXN];

static struct
{
	int _x, _y;
} Gr3[MAXN]

static struct
{
	int u, v, w, nxt;
} Gr[2 * MAXN];
static int head[MAXN], size[MAXN], fa[MAXN], N, M = 1;
static int Q[2 * MAXN], ord[MAXN], qf = 0, qr = 1;
static long long ans = 0;

void inline add_edge(int u, int v, int w)
{
	Gr[M].u = u;
	Gr[M].v = v;
	Gr[M].w = w;
	Gr[M].nxt = head[u];
	head[u] = M++;
}

int main(int argc, char *argv[])
{
	scanf("%d", &N);
	for (int i = 1; i < N; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		add_edge(u, v, w);
		add_edge(v, u, w);
	}
	Q[0] = 1; ord[M = 0] = 1;
	while (qf < qr)
	{
		int x = Q[qf++];
		for (int i = head[x]; i; i = Gr[i].nxt)
			if (Gr[i].v != fa[x])
				Q[qr++] = Gr[i].v, fa[Gr[i].v] = x, ord[++M] = Gr[i].v;
	}
	for (int i = M; i >= 0; i--)
	{
		int x = ord[i];
		size[x] = 1;
		for (int j = head[x]; j; j = Gr[j].nxt)
			if (Gr[j].v != fa[x])
				size[x] += size[Gr[j].v],
				ans += Gr[j].w * (long long)abs(2 * size[Gr[j].v] - N);
	}
	printf("%lld\n", ans);
	return 0;
}