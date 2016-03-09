#include <cstdio>
#include <cstdlib>

static int N, K;
static int A[1000010];
static int Q[2000010], qf = 0, qr = -1;

inline void row(int i, bool up)
{
	while (qr >= qf && (up ? (A[Q[qr]] >= A[i]) : (A[Q[qr]] <= A[i])))
		qr--;
	Q[++qr] = i;
	while (qr >= qf && Q[qf] <= (i - K)) qf++;
}

int main(int argc, char *argv[])
{
	scanf("%d%d", &N, &K);
	for (int i = 0; i < N; i++) scanf("%d", &A[i]);
	for (int i = 0; i < K-1; i++) row(i, true);
	for (int i = K-1; i < N; i++)
		row(i, true), printf("%d ", A[Q[qf]]);
	printf("\n");
	qf = 0; qr = -1;
	for (int i = 0; i < K-1; i++) row(i, false);
	for (int i = K-1; i < N; i++)
		row(i, false), printf("%d ", A[Q[qf]]);
	printf("\n");
	return 0;
}