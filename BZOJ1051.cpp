#include <cstdio>
#include <cstdlib>
#define MAXN 10010
#define MAXM 50010
#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) > (y)) ? (x) : (y))
 
static struct
{
    int u, v, nxt, prv;
} Gr[MAXM];
static int hd[MAXN], vis[MAXN], out[MAXN];
static int cnt[MAXN], belong[MAXN], ftop = 0, btop = 1;
static int dfn[MAXN], low[MAXN], acs[MAXN];
static int stack[MAXN], inq[MAXN], stop = 0;
static int N, M, ans;
 
void tarjan(int x)
{
    dfn[x] = low[x] = ++ftop;
    inq[stack[stop++] = x] = 1;
    for (int i = hd[x]; i; i = Gr[i].nxt)
    {
        int v = Gr[i].v; // assert Gr[i].u == x
        if (acs[v]) continue;
        if (!dfn[v])
        {
            tarjan(v);
            low[x] = min(low[x], low[v]);
        }
        else if (inq[v])
        {
            low[x] = min(low[x], dfn[v]);
        }
    }
    if (dfn[x] == low[x])
    {
        int u;
        do
        {
            inq[u = stack[--stop]] = 0;
            cnt[btop]++;
            belong[u] = btop;
            acs[u] = 1;
        } while (u != x);
        btop++;
    }
}
 
int main(int argc, char *argv[])
{
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= M; i++)
    {
        scanf("%d %d", &Gr[i].u, &Gr[i].v);
        Gr[i].nxt = hd[Gr[i].u];
        Gr[hd[Gr[i].u]].prv = hd[Gr[i].u] = i;
    }
    tarjan(1);
    for (int i = 1; i <= N; i++)
    {
        for (int j = hd[i]; j; j = Gr[j].nxt)
            if (vis[Gr[j].v] != i && belong[Gr[j].v] != belong[i])
                vis[Gr[j].v] = i, out[belong[i]]++;
    }
    for (int i = 1; i < btop; i++)
        if (!out[i])
        {
            if (ans) { printf("0\n"); return 0; } else ans = i;
        }
    printf("%d\n", cnt[ans]);
    return 0;
}