#include <cstdio>
#include <cstdlib>
#define MAXN 1000010
#define max(x, y) (((x) > (y)) ? (x) : (y))
 
static int Q[2*MAXN];
static long long S[MAXN], F[MAXN];
static int N, a, b, c, qf, qr, A;
 
#define G(x) (a * (x) * (x) + b * (x) + c)
#define X(i) (F[(i)-1] + a * S[(i)-1] * S[(i)-1] - b * S[(i)-1])
#define Y(i) (S[(i)-1])
 
inline double sl(int i, int j)
{
    return (X(i) - X(j)) / (double)(Y(i) - Y(j));
}
 
int main(int argc, char *argv[])
{
    scanf("%d%d%d%d", &N, &a, &b, &c);
    for (int i = 1; i <= N; i++)
    {
        scanf("%d", &A);
        S[i] = S[i-1] + A;
        while(qr>qf+1 && sl(i, Q[qr-1]) > sl(Q[qr-1], Q[qr-2]))
            qr--;
        Q[qr++] = i;
        while(qf+1<qr && sl(Q[qf+1], Q[qf]) > 2*a*S[i]) qf++;
        F[i] = F[Q[qf]-1] + G(S[i] - S[Q[qf]-1]);
    }
    printf("%lld\n", F[N]);
    return 0;
}