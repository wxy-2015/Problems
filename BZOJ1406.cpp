#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#define MAXN 200010

static int N, M, T = 1, top;
static int A[MAXN] = {1}, St[MAXN];

int main(int argc, char *argv[])
{
	scanf("%d", &N);
	if (N == 1)
	{
		printf("None\n");
		return 0;
	}
	M = sqrt(N);
	for (int d = 1; d <= M; d++)
		if (!(N % d))
			St[++top] = N / d;
	for (; top; top--)
	{
		int d = St[top], _d = N / d;
		for (int x = d; x <= N; x += d)
		{
			if ((x - 1) > 0 && !((x - 2) % _d)) A[T++] = x - 1;
			if ((x + 1) < N && !((x + 2) % _d)) A[T++] = x + 1;
		}
	}
	std::sort(A, A+T);
	for (int i = 0; i < T; i++)
		if (!i || A[i] != A[i-1]) printf("%d\n", A[i]);
	return 0;
}