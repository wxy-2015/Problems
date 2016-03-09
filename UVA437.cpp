#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
#define MAXN 1000

static struct tagT
{
	int x, y, z;
	void set(int a, int b, int c)
	{
		x = a; y = b; z = c;
	}
} C[MAXN];
static int N, T, A, DP[MAXN << 3];

bool cmp(tagT a, tagT b)
{
	return a.x * a.y < b.x * b.y;
}

int main(int argc, char *argv[])
{
	for (int k = 1; scanf("%d", &N), N; k++)
	{
		T = A = 0;
		for (int i = 0; i < N; i++)
		{
			int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			C[T++].set(x, y, z); C[T++].set(x, z, y);
			C[T++].set(y, x, z); C[T++].set(y, z, x);
			C[T++].set(z, y, x); C[T++].set(z, x, y);
		}
		sort(C, C + T, cmp);
		for (int i = 0; i < T; i++)
		{
			DP[i] = C[i].z;
			for (int j = 0; j < i; j++)
				if (C[i].x > C[j].x && C[i].y > C[j].y)
					DP[i] = max(DP[i], DP[j] + C[i].z);
			A = max(A, DP[i]);
		}
		printf("Case %d: maximum height = %d\n", k, A);
	}
}
