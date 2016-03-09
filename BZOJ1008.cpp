#include <cstdio>
#include <cstdlib>
#define P 100003

typedef unsigned long long _uint;

_uint power(_uint base, _uint pw)
{
	_uint ans = 1;
	for (; pw; pw >>= 1)
	{
		if (pw & 1) ans = ans * base % P;
		base = base * base % P;
	}
	return ans;
}

int main(int argc, char *argv[])
{
	long long N, M;
	scanf("%lld %lld", &N, &M);
	printf("%llu\n", (power(N, M) + P - (N * power(N - 1, M - 1) % P)) % P);
	return 0;
}