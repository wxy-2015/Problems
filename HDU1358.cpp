#include <cstdio>
#include <cstdlib>
#define MAXN 1000010

static char str[MAXN];
static int next[MAXN] = {-1}, T, N;

int main(int argc, char *argv[])
{
	while (scanf("%d", &N), N)
	{
		scanf("%s", str);
		printf("Test case #%d\n", ++T);
		for (int i = 0, j = -1; i < N; )
			if (j < 0 || str[i] == str[j]) next[++i] = ++j; else j = next[j];
		for (int i = 2; i <= N; i++)
			if (!(i % (i - next[i])) && i / (i - next[i]) > 1)
				printf("%d %d\n", i, i / (i - next[i]));
		printf("\n");
	}
	return 0;
}