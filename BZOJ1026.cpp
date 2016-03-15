#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
#define MAXN 20

static long long F[MAXN][MAXN];
static int bit[MAXN], L, R;

long long inline work(int x)
{
	int len;
	for (len = 1; x; x /= 10, len++) bit[len] = x % 10;
	bit[len--] = 0;
	long long ans = 0;
	for (int i = 1; i < len; i++)
		for (int j = 1; j < 10; j++)
			ans += F[i][j];
	for (int i = 1; i < bit[len]; i++) ans += F[len][i]; 
	for (int i = len - 1; i; i--)
	{
		for (int j = 0; j < bit[i]; j++)
			if (abs(bit[i+1] - j) >= 2) ans += F[i][j];
		if (abs(bit[i+1] - bit[i]) < 2) break;
	}
	return ans;
}

int main()
{
	for (int i = 0; i < 10; i++) F[1][i] = 1;
	for (int i = 2; i < MAXN; i++)
		for (int j = 0; j < 10; j++)
			for (int k = 0; k < 10; k++)
				if (abs(k - j) >= 2) F[i][j] += F[i-1][k];
	scanf("%d%d", &L, &R);
	printf("%lld\n", work(R + 1) - work(L));
	return 0;
}

