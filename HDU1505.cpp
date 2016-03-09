#include <cstdio>
#include <cstdlib>
#define MAXN 1010

static int T, N, M, ans, top;
static int A[MAXN][MAXN], H[MAXN][MAXN];
static int L[MAXN], R[MAXN], S[MAXN];
static char buff[2];

int inline max(int x, int y) { return x > y ? x : y; }

int main(int argc, char *argv[])
{
	scanf("%d", &T);
	while (T--)
	{
		ans = 0;
		scanf("%d%d", &N, &M);
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= M; j++)
				scanf("%s", buff), A[i][j] = buff[0] == 'F';
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= M; j++)
				H[i][j] = A[i][j] ? H[i][j-1] + 1 : 0;
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
				ans = max(ans, (L[i] + R[i] - 1) * H[i][j]);
		}
		printf("%d\n", 3 * ans);
	}
	return 0;
}
