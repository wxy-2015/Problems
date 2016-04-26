#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

#define EPS 1e-6
#define MAXN 1010

struct Point
{
	double x, y;
	
	Point(void)
	{
		x = y = 0;
	}
	
	Point(double _x, double _y)
	{
		x = _x; y = _y;
	}
	
	Point operator + (const Point& p) const
	{
		return Point(x + p.x, y + p.y);
	}
	
	Point operator - (const Point& p) const
	{
		return Point(x - p.x, y - p.y);
	}
};

static Point A[MAXN];
static int N, L, top = -1, St[MAXN];


int inline dabs(double x)
{
	return (fabs(x) < EPS) ? 0 : (x > 0 ? 1 : -1);
}

double inline dot(Point a, Point b)
{
	return a.x * b.x + a.y * b.y;
}

double inline cross(Point a, Point b)
{
	return a.x * b.y - b.x * a.y;
}

double inline dist(Point a, Point b)
{
	return sqrt(dot(a - b, a - b));
}

bool compare(Point a, Point b)
{
	return (!dabs(a.x - b.x)) ? a.y < b.y : a.x < b.x;
}

int main()
{
	scanf("%d %d", &N, &L);
	for (int i = 0; i < N; i++)
		scanf("%lf %lf", &A[i].x, &A[i].y);
	sort(A, A + N, compare);
	for (int i = 0; i < N; i++)
	{
		while (top > 0 && cross(A[St[top]] - A[St[top-1]], A[i] - A[St[top-1]]) < 0)
			top--;
		St[++top] = i;
	}
	int dm = top;
	for (int i = N - 2; i >= 0; i--)
	{
		while (top > dm && cross(A[St[top]] - A[St[top-1]], A[i] - A[St[top-1]]) < 0)
			top--;
		St[++top] = i;
	}
	double ans = 2.0 * acos(-1.0) * (double)L;
	for (int i = 0; i < top; i++) ans += dist(A[St[i]], A[St[i+1]]);
	printf("%d\n", (int)(ans + 0.5));
	return 0;
}

