#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
const int MAXN = 2e4 + 10, MAXM = MAXN * 3;
int n, m, q;
struct edge
{
    int v, w, nxt;
} e[MAXM];
int h1[MAXN], h2[MAXN], idx = 1;
int dfn[MAXN], low[MAXN], tim;
int s[MAXN], sc[MAXN], fa[MAXN], fw[MAXN], fe[MAXN], cn;
int f[MAXN][14], dep[MAXN], d[MAXN];
int A, B;
void add(int h[], int a, int b, int c)
{
    e[++idx] = {b, c, h[a]};
    h[a] = idx;
}
void build_tree(int u, int v, int w)
{
    int sum = w;
    for (int k = v; k != u; k = fa[k])
    {
        s[k] = sum;
        sum += fw[k];
    }
    add(h2, u, ++cn, 0);
    for (int k = v; k != u; k = fa[k])
    {
        sc[k] = sum;
        add(h2, cn, k, min(s[k], sum - s[k]));
    }
}
void tarjan(int u, int frm)
{
    dfn[u] = low[u] = ++tim;
    for (int i = h1[u]; i; i = e[i].nxt)
    {
        int v = e[i].v, w = e[i].w;
        if (!dfn[v])
        {
            fa[v] = u, fw[v] = w, fe[v] = i;
            tarjan(v, i);
            low[u] = min(low[u], low[v]);
            if (dfn[u] < low[v])
                add(h2, u, v, w);
        }
        else if (i != (frm ^ 1))
            low[u] = min(low[u], dfn[v]);
    }
    for (int i = h1[u]; i; i = e[i].nxt)
    {
        int v = e[i].v, w = e[i].w;
        if (dfn[u] < dfn[v] && fe[v] != i)
            build_tree(u, v, w);
    }
}
void dfs(int u, int fth)
{
    dep[u] = dep[fth] + 1;
    f[u][0] = fth;
    for (int k = 1; k <= 13; k++)
        f[u][k] = f[f[u][k - 1]][k - 1];
    for (int i = h2[u]; i; i = e[i].nxt)
    {
        int v = e[i].v, w = e[i].w;
        d[v] = d[u] + w;
        dfs(v, u);
    }
}
int lca(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    int d = dep[x] - dep[y];
    for (int i = 0; i <= log2(d); i++)
        if (d & (1 << i))
            x = f[x][i];
    if (x == y)
        return x;
    for (int i = log2(dep[x]); i + 1; i--)
        if (f[x][i] != f[y][i])
        {
            x = f[x][i];
            y = f[y][i];
        }
    A = x, B = y;
    return f[x][0];
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m >> q;
    cn = n;
    while (m--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        add(h1, a, b, c), add(h1, b, a, c);
    }
    tarjan(1, -1);
    dfs(1, 0);
    while (q--)
    {
        int u, v;
        cin >> u >> v;
        int p = lca(u, v);
        if (p <= n)
            cout << d[u] + d[v] - d[p] * 2 << endl;
        else
        {
            int len = abs(s[A] - s[B]);
            int dAB = min(len, sc[A] - len);
            int dis = dAB + d[u] - d[A] + d[v] - d[B];
            cout << dis << endl;
        }
    }
    return 0;
}