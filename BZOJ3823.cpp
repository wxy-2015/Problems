#include <cstdio>
#include <cstdlib>
#define MAXN 20000010

static long long N, P, ans, tmp, x;
static int inv[MAXN];

long long inline pow(long long base, long long p)
{
	long long ans = 1;
	for (; p; p >>= 1, base = base * base % P)
		if (p & 1) ans = ans * base % P;
	return ans;
}

int main()
{
	scanf("%lld%lld", &N, &P);
	inv[0] = inv[1] = 1;
	for (int i = 2; i <= 2 * N; i++) inv[i] = (P - P / i) * inv[P % i] % P;
	ans = tmp = pow(2, N);
	for (int cnt = 0, i = 1; i <= N; i++)
	{
		x = N - i + 1;
		while (!(x % P)) x /= P, cnt++;
		tmp = tmp * x % P;
		x = 2 * i;
		while (!(x % P)) x /= P, cnt--;
		tmp = tmp * inv[x % P] % P;
		ans ^= cnt ? 0 : tmp;
	}
	printf("%lld\n", ans);
	return 0;
}

