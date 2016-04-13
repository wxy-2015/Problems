#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
#define MAXN 10001
#define INF ((int)1e9)
#define T (MAXN + 1)
#define S (0)

static int N, M, G = 0;
static struct
{
	int u, v, w, next;
} Gr[100010];
static int H[MAXN + 10], D[MAXN + 10];
static int A[105][105], Q[MAXN << 2];

const int X[] = {-1, 1, 0, 0}, Y[] = {0, 0, -1, 1};

void inline add_edge(int u, int v, int w)
{
	Gr[G].u = u; Gr[G].v = v; Gr[G].w = w;
	Gr[G].next = H[u]; H[u] = G++;
	Gr[G].u = v; Gr[G].v = u; Gr[G].w = 0;
	Gr[G].next = H[v]; H[v] = G++;
}

int inline encode(int x, int y)
{
	return (x - 1) * M + (y);
}

bool inline bfs(void)
{
	int qf = 0, qr = 0;
	memset(D, 0, sizeof(D));
	D[Q[qr++] = S] = 1;
	while (qf < qr)
	{
		int x = Q[qf++];
		for (int i = H[x]; ~i; i = Gr[i].next)
			if (Gr[i].w && !D[Gr[i].v])
				D[Q[qr++] = Gr[i].v] = D[x] + 1; 
	}
	return D[T];
}

int dfs(int x, int f)
{
	if (x == T) return f;
	int r = 0;
	for (int i = H[x]; ~i && r < f; i = Gr[i].next)
		if (Gr[i].w && D[Gr[i].v] == D[x] + 1)
			{
				int delta = dfs(Gr[i].v, min(Gr[i].w, f - r));
				r += delta;
				Gr[i  ].w -= delta;
				Gr[i^1].w += delta;
			}
	if (!r) D[x] = 0;
	return r;
}

int main()
{
	scanf("%d%d", &N, &M);
	memset(H, -1, sizeof(H));
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
		{
			scanf("%d", &A[i][j]);
			if (A[i][j] == 1) add_edge(S, encode(i, j), INF);
			if (A[i][j] == 2) add_edge(encode(i, j), T, INF);
		}
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			for (int k = 0; k < 4; k++)
			{
				int _i = i + X[k], _j = j + Y[k];
				if (_i < 1 || _j < 1 || _i > N || _j > M || A[i][j] == 2) continue;
				if (A[i][j] != 1 || A[_i][_j] != 1)
						add_edge(encode(i, j), encode(_i, _j), 1);
			}
	int delta, ans = 0;
	while (bfs()) while (delta = dfs(S, INF)) ans += delta;
	printf("%d\n", ans);
	return 0;
}

