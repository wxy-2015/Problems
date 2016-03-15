#include <cstdio>
#include <cstdlib>
#define MAXN 11

static int F[MAXN], G[MAXN], H[MAXN];
static int L, R;
static int bit[MAXN];

int inline work(int x)
{
	int len, ans, flag = 0;
	for (len = 1; x; x /= 10, len++) bit[len] = x % 10;
	bit[len--] = 0;
	for (ans = 0; len; len--)
	{
		ans += bit[len] * H[len-1];
		if (flag)
			ans += bit[len] * F[len-1];
		else
		{
			if (bit[len] > 4) ans += F[len-1];
			if (bit[len] > 6) ans += G[len-1];
			if (bit[len+1] == 6 && bit[len] > 2) ans += G[len];
		}
		if ((bit[len+1] == 6 && bit[len] == 2) || bit[len] == 4)
			flag = 1;
	}
	return ans;
}

int main()
{
	F[0] = 1;
	for (int i = 1; i < MAXN; i++)
	{
		F[i] = 9 * F[i-1] - G[i-1];
		G[i] = F[i-1];
		H[i] = 10 * H[i-1] + F[i-1] + G[i-1];
	}
	while (scanf("%d%d", &L, &R), L || R)
		printf("%d\n", R - L + work(L) - work(R+1) + 1);
	return 0;
}
