#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010

static int lf[MAXN], ch[MAXN][10];
static int T, N, ltop, x;
static char buf[MAXN][20];

int main(int argc, char *argv[])
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &N);
		ltop = 0;
		memset(lf, 0, sizeof(lf));
		memset(ch, 0, sizeof(ch));
		for (int i = 0; i < N; i++) scanf("%s", buf[i]);
		bool succ = true;
		for (int i = 0; i < N && succ; i++)
		{
			x = 0;
			for (int j = 0; buf[i][j] && succ; j++)
			{
				if (!ch[x][buf[i][j]-'0'])
					ch[x][buf[i][j]-'0'] = ++ltop;
				if (lf[x]) succ = false;
				x = ch[x][buf[i][j]-'0'];
			}
			for (int j = 0; j < 10 && succ; j++)
				if (ch[x][j]) succ = false;
			lf[x] = 1;
		}
		printf("%s\n", succ ? "YES" : "NO");
	}
	return 0;
}
