#include <cstdio>
#include <cstdlib>
#include <cmath>

static long long N, S, SQRT;

long long phi(long long x)
{
	long long r = x;
	for (long long d = 2; d <= SQRT; d++)
		if (!(x % d))
		{
			r = r / d * (d - 1);
			while (!(x % d)) x /= d;
		}
	if (x != 1) r = r / x * (x - 1);
	return r;
}

int main(int argc, char *argv[])
{
	scanf("%lld", &N);
	SQRT = sqrt(N);
	for (long long d = 1; d <= SQRT; d++)
		if (!(N % d))
		{
			S += d * phi(N / d);
			if (d * d != N) S += N / d * phi(d);
		}
	printf("%lld\n", S);
}