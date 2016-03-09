#include <cstdio>
#include <cstdlib>

static long long M, X0, N, G;

long long inline mult(long long x, long long y)
{
	long long r = 0;
	for (; y; y >>= 1, x = (x + x) % M)
		if (y & 1) r = (r + x) % M;
	return r;
}

struct mtx
{
	long long a, c;
	const mtx operator * (const mtx& x) const
	{
		mtx r = {0, 0};
		r.a = mult(x.a, a);
		r.c = (mult(a, x.c) + c) % M;
		return r;
	}
} X;

mtx inline power(mtx x, long long y)
{
	mtx r = x;
	for (y--; y; y >>= 1, x = x * x)
		if (y & 1) r = r * x;
	return r;
}

int main(int argc, char *argv[])
{
	scanf("%lld%lld%lld%lld%lld%lld", &M, &X.a, &X.c, &X0, &N, &G);
	X = power(X, N);
	printf("%lld\n", (mult(X.a, X0) + X.c) % M % G);
	return 0;
}