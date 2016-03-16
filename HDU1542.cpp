#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
#define MAXN 200
#define lson (n << 1)
#define rson (lson | 1)
#define mid ((l + r) >> 1)

struct line
{
	double y1, y2, x, f;
	bool operator < (const line& l) const { return x < l.x; }
} Line[MAXN];
static int Ct[MAXN << 2], N = 1, T, L;
static double SRT[MAXN << 1], ans, Tr[MAXN << 2];

void build(int n, int l, int r)
{
	Tr[n] = -1;
	Ct[n] = 0;
	if (l + 1 < r) build(lson, l, mid), build(rson, mid, r);
}

double insert(int n, int l, int r, double x, double y1, double y2, int f)
{
	if (y2 <= SRT[l] || SRT[r] <= y1) return 0;
	double ans = 0;
	if (l + 1 == r)
	{
		if (Ct[n] > 0)
			ans = (x - Tr[n]) * (SRT[r] - SRT[l]);
		Tr[n] = x;
		Ct[n] += f;
		return ans;
	}
	ans += insert(lson, l, mid, x, y1, y2, f);
	ans += insert(rson, mid, r, x, y1, y2, f);
	return ans;
}

int main()
{
	while (N)
	{
		scanf("%d", &N);
		if (!N) break;
		ans = L = 0;
		for (int i = 0; i < N; i++)
		{
			double x1, y1, x2, y2;
			scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
			Line[L].x = x1; Line[L].y1 = y1; Line[L].y2 = y2; Line[L].f = 1;  SRT[L++] = y1;
			Line[L].x = x2; Line[L].y1 = y1; Line[L].y2 = y2; Line[L].f = -1; SRT[L++] = y2;
		}
		sort(SRT, SRT + 2*N);
		sort(Line, Line + L);
		build(1, 0, L-1);
		for (int i = 0; i < L; i++)
			ans += insert(1, 0, L-1, Line[i].x, Line[i].y1, Line[i].y2, Line[i].f);
		printf("Test case #%d\nTotal explored area: %.2lf\n\n", ++T, ans);
	}
	return 0;
}

