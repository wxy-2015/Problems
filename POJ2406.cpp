#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 10000010

static char str[MAXN];
static int nxt[MAXN] = {-1}, L;

int main(int argc, char *argv[])
{
	while (~scanf("%s", str))
	{
		if (str[0] == '.') break;
		L = strlen(str);
		for (int i = 0, j = -1; i < L; )
			if (j < 0 || str[i] == str[j]) nxt[++i] = ++j; else j = nxt[j];
		if (!(L % (L - nxt[L])))
			printf("%d\n", L / (L - nxt[L]));
		else
			printf("1\n");
	}
	return 0;
<<<<<<< HEAD
}
=======
}

>>>>>>> branch 'master' of https://code.csdn.net/wxy_2015/problems.git