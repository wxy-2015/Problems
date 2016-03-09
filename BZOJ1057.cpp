#include <cstdio>
#include <cstdlib>
#define MAXN 2010

static int N, M, top, ans1 = 0, ans2 = 0;
static int A[MAXN][MAXN], H[MAXN][MAXN];
static int L[MAXN], R[MAXN], S[MAXN];

int inline min(int x, int y) { return x > y ? y : x; }
int inline max(int x, int y) { return x > y ? x : y; }

void inline search(int x)
{
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			H[i][j] = A[i][j] == x ? H[i][j-1] + 1 : 0;
	for (int j = 1; j <= M; j++)
	{
		S[top = 0] = 0;
		for (int i = 1; i <= N; i++)
		{
			while (top && H[S[top]][j] >= H[i][j]) top--;
			L[i] = i - S[top];
			S[++top] = i;
		}
		S[top = 0] = N + 1;
		for (int i = N; i; i--)
		{
			while (top && H[S[top]][j] >= H[i][j]) top--;
			R[i] = S[top] - i;
			S[++top] = i;
		}
		for (int i = 1; i <= N; i++)
		{
			int l = L[i] + R[i] - 1;
			ans1 = max(ans1, min(H[i][j], l) * min(H[i][j], l));
			ans2 = max(ans2, H[i][j] * l);
		}
	}
}

int main(int argc, char *argv[])
{
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			scanf("%d", &A[i][j]), A[i][j] ^= (i ^ j) & 1;
	search(0); search(1);
	printf("%d\n%d\n", ans1, ans2);
	return 0;
}