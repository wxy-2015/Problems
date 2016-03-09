#include <cstdio>
#include <cstdlib>
#define MAXN 1000010

static int N, ans, time, x;

int main(int argc, char *argv[])
{
	while (scanf("%d", &N) == 1)
	{
		ans = time = 0;
		while (N--)
		{
			scanf("%d", &x);
			if (!time) ans = x;
			time += (ans == x) ? 1 : -1;
		}
		printf("%d\n", ans);
	}
	return 0;
}
