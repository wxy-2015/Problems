#include <cstdio>
#include <cstdlib>
#define MAXN 21

static int DP[1 << MAXN];
static int N, T, x, adr;

int dfs(int adr)
{
	if (DP[adr]) return DP[adr];
	if (((adr & (1 << 2)) > 0) != ((adr & (1 << 3)) > 0))
		return DP[adr] = (adr & (1 << 2)) ? (1 << 2) : (1 << 3);
	for (int i = 2; i < MAXN; i++) if (adr & (1 << i))
	{
		int next = adr & (~(1 << i));
		for (int j = 2; i + j < MAXN; j++)
			if (!(next & (1 << j))) next &= ~(1 << (i + j));
		if (dfs(next) == -1) DP[adr] |= 1 << i;
	}
	if (!DP[adr]) DP[adr] = -1;
	return DP[adr];
}

int main(int argc, char *argv[])
{
	while (scanf("%d", &N), N)
	{
		adr = 0;
		for (int i = 0; i < N; i++)
			scanf("%d", &x), adr |= (1 << x);
		printf("Test Case #%d\n", ++T);
		x = dfs(adr);
		if (x == -1)
			printf("There's no winning move.\n\n");
		else
		{
			printf("The winning moves are: ");
			for (int i = 2; i < MAXN; i++)
				if (x & (1 << i)) printf("%d ", i);
			printf("\n\n");
		}
	}
	return 0;
}
