#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
#define MAXN 50010
#define lson (n << 1)
#define rson (lson | 1)
#define lm ((l + r) >> 1)
#define rm (lm + 1)

static int N, M;
static int Tr[MAXN << 2];
static struct TPair
{
	int key, val;
} A[MAXN];

int inline _max(int x, int y) { return x > y ? x : y; }

bool cmp(TPair x, int y) { return x.key < y; }

int build(int n, int l, int r)
{
	if (l == r) return Tr[n] = A[l].val;
	return Tr[n] = _max(build(lson, l, lm), build(rson, rm, r));
}

int search(int n, int l, int r, int fl, int fr)
{
	if (fl > fr) return 0;
	if (fl <= l && r <= fr) return Tr[n];
	int ans = 0;
	if (fl <= lm) ans = _max(ans, search(lson, l, lm, fl, fr));
	if (fr >= rm) ans = _max(ans, search(rson, rm, r, fl, fr));
	return ans;
}

int main(int argc, char *argv[])
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++) scanf("%d%d", &A[i].key, &A[i].val);
	build(1, 0, N-1);
	scanf("%d", &M);
	while (M--)
	{
		int a, b, x, y, _x, _y, s;
		scanf("%d%d", &a, &b);
		if (a > b) { printf("false\n"); continue; }
		x = lower_bound(A, A+N, a, cmp) - A; _x = (A[x].key == a);
		y = lower_bound(A, A+N, b, cmp) - A; _y = (A[y].key == b);
		s = search(1, 0, N-1, x + _x, y - 1);
		if (!_x && !_y)
			{ printf("maybe\n"); }
		else if (_x && !_y)
			if (s < A[x].val) printf("maybe\n"); else printf("false\n");
		else if (!_x && _y)
			if (s < A[y].val) printf("maybe\n"); else printf("false\n");
		else if (_x && _y)
		{
			if (s < A[y].val && A[y].val <= A[x].val)
				{ if (y - x == b - a) printf("true\n"); else printf("maybe\n"); }
			else
				printf("false\n");
		}
	}
}
