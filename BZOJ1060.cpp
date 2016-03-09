#include <cstdio>
#include <cstdlib>
#define MAXN 1000010

static struct
{
	int u, v, t, nxt;
} Gr[MAXN];
static int head[MAXN], htop = 1;
static int N, S, F[MAXN];
static long long ans;

long long inline max(long long x, long long y) { return (x > y) ? x : y; }

void inline add_edge(int u, int v, int t)
{
	Gr[htop].u = u;
	Gr[htop].v = v;
	Gr[htop].t = t;
	Gr[htop].nxt = head[u];
	head[u] = htop++;
}

int dfs(int x, int fa)
{
	for (int i = head[x]; i; i = Gr[i].nxt)
		if (Gr[i].v != fa)
			F[x] = max(F[x], dfs(Gr[i].v, x) + Gr[i].t);
	for (int i = head[x]; i; i = Gr[i].nxt)
		if (Gr[i].v != fa)
			ans += F[x] - F[Gr[i].v] - Gr[i].t;
	return F[x];
}

int main(int argc, char *argv[])
{
	scanf("%d%d", &N, &S);
	for (int i = 1; i < N; i++)
	{
		int u, v, t;
		scanf("%d%d%d", &u, &v, &t);
		add_edge(u, v, t);
		add_edge(v, u, t);
	}
	dfs(S, 0);
	printf("%lld\n", ans);
	return 0;
}