#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010

static struct Tr
{
	int word;
	Tr *ptr[26];
} *root;
static char buff[MAXN];

void release(Tr *cur)
{
	for (int i = 0; i < 26; i++) if (cur -> ptr[i]) release(cur -> ptr[i]);
	delete cur;
}

int main(int argc, char *argv[])
{
	root = new Tr;
	memset(root, 0, sizeof(Tr));
	do
	{
		fgets(buff, MAXN, stdin);
		Tr *cur = root;
		for (char *c = buff; 'a' <= *c && *c <= 'z'; c++)
		{
			if (!(cur -> ptr[*c-'a']))
			{
				cur -> ptr[*c-'a'] = new Tr;
				memset(cur -> ptr[*c-'a'], 0, sizeof(Tr));
			}
			cur = cur -> ptr[*c-'a'];
			cur -> word++;
		}
	} while ('a' <= buff[0] && buff[0] <= 'z');
	while (~scanf("%s", buff))
	{
		Tr* cur = root;
		for (char *c = buff; 'a' <= *c && *c <= 'z' && cur; c++)
			cur = cur -> ptr[*c-'a'];
		printf("%d\n", cur ? cur -> word : 0);
	}
	release(root);
	return 0;
}
