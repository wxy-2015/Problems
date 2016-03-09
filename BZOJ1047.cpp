#include <cstdio>
#include <cstdlib>
#include <climits>
#define MAXN 1010

static int A, B, N, ans = INT_MAX;
static int X[MAXN][MAXN];
static int MAX1[MAXN][MAXN], MIN1[MAXN][MAXN];
static int MAX2[MAXN][MAXN], MIN2[MAXN][MAXN];
static int Q[MAXN], qf, qr;

int inline min(int x, int y) { return x > y ? y : x; }

void inline queue_up(int i, int x)
{
	while (qr >= qf && X[i][Q[qr]] > X[i][x]) qr--;
	Q[++qr] = x;
	while (qr >= qf && Q[qf] <= x - N) qf++;
}

void inline queue_down(int i, int x)
{
	while (qr >= qf && X[i][Q[qr]] < X[i][x]) qr--;
	Q[++qr] = x;
	while (qr >= qf && Q[qf] <= x - N) qf++;
}

void inline queue_up2(int x, int j)
{
	while (qr >= qf && MIN1[Q[qr]][j] > MIN1[x][j]) qr--;
	Q[++qr] = x;
	while (qr >= qf && Q[qf] <= x - N) qf++;
}

void inline queue_down2(int x, int j)
{
	while (qr >= qf && MAX1[Q[qr]][j] < MAX1[x][j]) qr--;
	Q[++qr] = x;
	while (qr >= qf && Q[qf] <= x - N) qf++;
}

int main(int argc, char *argv[])
{
	scanf("%d%d%d", &A, &B, &N);
	for (int i = 0; i < A; i++)
		for (int j = 0; j < B; j++)
			scanf("%d", &X[i][j]);
	for (int i = 0; i < A; i++)
	{
		qf = 0; qr = -1;
		for (int j = 0; j < N - 1; j++) queue_up(i, j);
		for (int j = N - 1; j < B; j++) queue_up(i, j), MIN1[i][j] = X[i][Q[qf]];
		qf = 0; qr = -1;
		for (int j = 0; j < N - 1; j++) queue_down(i, j);
		for (int j = N - 1; j < B; j++) queue_down(i, j), MAX1[i][j] = X[i][Q[qf]];
	}
	for (int j = N - 1; j < B; j++)
	{
		qf = 0; qr = -1;
		for (int i = 0; i < N - 1; i++) queue_up2(i, j);
		for (int i = N - 1; i < A; i++) queue_up2(i, j), MIN2[i][j] = MIN1[Q[qf]][j];
		qf = 0; qr = -1;
		for (int i = 0; i < N - 1; i++) queue_down2(i, j);
		for (int i = N - 1; i < A; i++) queue_down2(i, j), MAX2[i][j] = MAX1[Q[qf]][j];
	}
	for (int i = N - 1; i < A; i++)
		for (int j = N - 1; j < B; j++)
			ans = min(ans, MAX2[i][j] - MIN2[i][j]);
	printf("%d\n", ans);
}
