#include <cstdio>
#include <cstdlib>
#define MAXN 1000010
#define MOD 1000000007

static long long F[MAXN], J[MAXN], dJ[MAXN];
static int T, N, M, K, U = 2, Q = 1;

long long inline power(long long base)
{
	long long p = MOD - 2, ans = 1;
	while (p)
	{
		if (p & 1) ans = ans * base % MOD;
		base = base * base % MOD;
		p = p >> 1;
	}
	return ans;
}

int main()
{
	F[0] = J[0] = dJ[0] = 1;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &N, &M);
		K = N - M;
		if (K == 0) { printf("1\n"); continue; }
		if (K <  0) { printf("0\n"); continue; }
		if (K == 1) { printf("0\n"); continue; }
		for (; U <= K; U++) F[U] = (F[U-1] + F[U-2]) % MOD * (U-1) % MOD;
		for (; Q <= N; Q++) J[Q] = J[Q-1] * Q % MOD, dJ[Q] = power(J[Q]);
		printf("%lld\n", J[N] * dJ[K] % MOD * dJ[M] % MOD * F[K] % MOD);
	}
	return 0;
}

