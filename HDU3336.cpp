#include <cstdio>
#include <cstdlib>
#define MAXN 200010
#define MOD 10007

static char str[MAXN];
static int next[MAXN] = {-1}, dp[MAXN];
static int ans, T, L;

int main(int argc, char *argv[])
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%s", &L, str);
		for (int i = 0, j = -1; i < L; )
			if (j < 0 || str[i] == str[j]) next[++i] = ++j; else j = next[j];
		ans = 0;
		for (int i = 1; i <= L; i++)
			dp[i] = dp[next[i]] + 1,
			ans = (ans + dp[i]) % MOD;
		printf("%d\n", ans);
	}
	return 0;
}