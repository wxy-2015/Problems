#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
#define MAXN 10010

static int Q, N, T;
static int F[MAXN], V[MAXN], W[MAXN];

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &N, &Q);
		for (int i = 0; i < N; i++) scanf("%d", &V[i]);
		for (int i = 0; i < N; i++) scanf("%d", &W[i]);
		memset(F, 0, sizeof(F));
		for (int i = 0; i < N; i++)
			for (int j = Q; j >= 0; j--)
				if (j >= W[i]) F[j] = max(F[j], F[j - W[i]] + V[i]);
		printf("%d\n", F[Q]);
	}
	return 0;
}
