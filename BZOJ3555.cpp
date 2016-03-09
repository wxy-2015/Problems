#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define MAXN 30010
#define MAXL 210
using namespace std;

static unsigned long long h1[MAXN][MAXL], h2[MAXN][MAXL], cnt[MAXN];

int main(int argc, char *argv[])
{
	static char buf[MAXL];
	static int N, L, S, ans = 0;
	scanf("%d %d %d", &N, &L, &S);
	for (int i = 0; i < N; i++)
	{
		scanf("%s", buf + 1);
		for (int j = 1; j <= L; j++) h1[i][j] = h1[i][j-1] * 149 + buf[j];
		for (int j = L; j >= 1; j--) h2[i][j] = h2[i][j+1] * 137 + buf[j];
	}
	for (int i = 1; i <= L; i++)
	{
		S = 1;
		for (int j = 0; j < N; j++)
			cnt[j] = h1[j][i-1] * 233 + h2[j][i+1] * 213;
		sort(cnt, cnt + N);
		for (int j = 1; j < N; j++)
			if (cnt[j] == cnt[j-1]) ans += S++; else S = 1;
	}
	printf("%d\n", ans);
	return 0;
}