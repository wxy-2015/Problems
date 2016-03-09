#include <cstdio>
#include <cstdlib>
#define MAXN 50010

static int phi[MAXN] = {0, 1}, N;
static unsigned long long ans = 0;

int main(int argc, char *argv[])
{
	for (int i = 2; i <= MAXN; i++)
	{
		if (phi[i]) continue;
		for (int j = i; j <= MAXN; j += i)
			phi[j] = (phi[j] ? phi[j] : j) / i * (i - 1);
	}
	while (scanf("%d", &N) == 1)
	{
		ans = 0;
		for (int i = 1; i < N; i++) ans += phi[i];
		printf("%llu\n", ans * 2 + 1);
	}
}