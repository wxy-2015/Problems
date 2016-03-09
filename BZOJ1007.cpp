#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#define MAXN 50010
#define EPS 1e-6
using namespace std;

static struct _struct
{
	double A, B;
	int adr;
	const bool operator < (const _struct& x) const
	{
		return (fabs(A - x.A) < EPS) ? B < x.B : A < x.A;
	}
} Line[MAXN];
static int St[MAXN], Mp[MAXN], top = 0, N;

double inline G(int i, int j) { return (Line[j].B - Line[i].B) / (Line[i].A - Line[j].A); }

int main(int argc, char *argv[])
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%lf%lf", &Line[i].A, &Line[i].B), Line[i].adr = i + 1;
	sort(Line, Line + N);
	for (int i = 0; i < N; i++)
	{
		while (top)
			if (fabs(Line[St[top]].A - Line[i].A) < EPS)
				top--;
			else if (top > 1 && G(i, St[top-1]) <= G(St[top], St[top-1]))
				top--;
			else break;
		St[++top] = i;
	}
	for (int i = 1; i <= top; i++) Mp[Line[St[i]].adr] = 1;
	for (int i = 1; i <= N; i++) if (Mp[i]) printf("%d ", i);
	printf("\n");
}