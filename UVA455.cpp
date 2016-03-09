#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 256

static char str[MAXN];
static int N, i, l, len;

int main(int argc, char *argv[])
{
	scanf("%d", &N);
	while(N--)
	{
		scanf("%s", str);
		len = strlen(str);
		for (l = 1; l <= len; l++)
			if (!(len % l))
			{
				for (i = l; i < len; i++)
					if (str[i] != str[i % l]) break;
				if (!str[i])
				{
					printf("%d\n", l);
					break;
				}
			}
		if (N) printf("\n");
	}
}

