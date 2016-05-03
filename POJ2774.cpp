#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
#define MAXN 200010
#define SIZE 130

static char S[MAXN];
static int N, N0, ans;
static int SA[MAXN], RANK[MAXN], HGT[MAXN];

bool inline cmp(int *s, int a, int b, int k)
{
	return s[a] == s[b] && s[a+k] == s[b+k];
}

void inline getSA(char *s)
{
	static int Srt[MAXN], Ma[MAXN], Mb[MAXN], tmp[MAXN];
	int *x = Ma, *y = Mb, p = 1, M = SIZE, k = 0;
	memset(Srt, 0, sizeof(Srt));
	for (int i = 0; i < N; i++) Srt[x[i] = s[i]]++;
	for (int i = 1; i < M; i++) Srt[i] += Srt[i-1];
	for (int i = N-1; i >= 0; i--) SA[--Srt[x[i]]] = i;
	for (int j = 1; p < N; j <<= 1, M = p)
	{
		p = 0;
		for (int i = N - j; i < N; i++) y[p++] = i;
		for (int i = 0; i < N; i++) if (SA[i] >= j) y[p++] = SA[i] - j;
		memset(Srt, 0, sizeof(Srt));
		for (int i = 0; i < N; i++) Srt[tmp[i] = x[y[i]]]++;
		for (int i = 1; i < M; i++) Srt[i] += Srt[i-1];
		for (int i = N-1; i >= 0; i--) SA[--Srt[tmp[i]]] = y[i];
		swap(x, y);
		x[SA[0]] = 0;
		p = 1;
		for (int i = 1; i < N; i++)
			x[SA[i]] = cmp(y, SA[i-1], SA[i], j) ? p-1 : p++;
	}
	for (int i = 1; i < N; i++) RANK[SA[i]] = i;
	for (int i = 0; i < N; i++)
	{
		if (k) k--;
		for (int j = SA[RANK[i] - 1]; s[i+k] == s[j+k]; ) k++;
		HGT[RANK[i]] = k;
	}
}

int main()
{
	while (~scanf("%s", S))
	{
		S[N0 = strlen(S)] = '#';
		scanf("%s", S + N0 + 1); N = strlen(S);
		getSA(S);
		ans = 0;
		for (int i = 1; i < N; i++)
			if (HGT[i] > ans)
			{
				 if (SA[i-1] < N0 && N0 < SA[i]) ans = HGT[i];
				 if (SA[i] < N0 && N0 < SA[i-1]) ans = HGT[i];
			}
		printf("%d\n", ans);
	}
	return 0;
}

