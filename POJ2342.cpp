#include <cstdio>
#include <cstdlib>
#define MAXN 6010

static int A[MAXN], H[MAXN], N, T = 1, R;
static int Fa[MAXN], DP[MAXN][2];
static struct
{
	int u, v, next;
} Gr[MAXN << 1];

int inline max(int x, int y) { return x > y ? x : y; }

void inline add_edge(int u, int v)
{
	Gr[T].u = u;
	Gr[T].v = v;
	Gr[T].next = H[u];
	H[u] = T++;
}

int dp(int x)
{
	DP[x][1] = A[x];
	for (int i = H[x]; i; i = Gr[i].next)
		if (Gr[i].v != Fa[x])
			DP[x][0] += dp(Gr[i].v),
			DP[x][1] += DP[Gr[i].v][0];
	return max(DP[x][0], DP[x][1]);
}

int main(int argc, char *argv[])
{
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", &A[i]);
	for (int i = 1; i < N; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add_edge(u, v);
		add_edge(v, u);
		Fa[u] = v;
	}
	for (int i = 1; i <= N; i++)
		if (!Fa[i]) R = i;
	printf("%d\n", dp(R));
	return 0;
}
