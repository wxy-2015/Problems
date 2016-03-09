#include <cstdio>
#include <cstdlib>
#define MAXN 1000010

static int G, N, M, A;
static char P[MAXN], T[MAXN];
static int Nxt[MAXN] = {-1};

int main(int argc, char *argv[])
{
	scanf("%d", &G);
	while (G--)
	{
		scanf("%s%s", P, T);
		N = strlen(T); M = strlen(P);
		for (int i = 0, j = -1; i < M; )
			if (j < 0 || P[i] == P[j]) Nxt[++i] = ++j; else j = Nxt[j];
		A = 0;
		for (int i = 0, j = 0; i < N; )
		{
			if (j < 0 || T[i] == P[j]) i++, j++; else j = Nxt[j];
			if (j == M) A++, j = Nxt[j-1], i--;
		}
		printf("%d\n", A);
	}
	return 0;
}