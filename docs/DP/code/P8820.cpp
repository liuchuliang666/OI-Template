#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Matrix
{
    ll a[3][3];
    Matrix(ll val = 1e18)
    {
        memset(a, 0x3f, sizeof(a));
        for (int i = 0; i < 3; i++)
            a[i][i] = val;
    }
    ll *operator[](int i) { return a[i]; }
};
Matrix operator*(Matrix a, Matrix b)
{
    Matrix c = 1e18;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                c[i][k] = min(c[i][k], a[i][j] + b[j][k]);
    return c;
};
const int MAXN = 200010;
struct edge
{
    int v, nxt;
} e[MAXN << 1];
int head[MAXN];
void addedge(int u, int v)
{
    static int edge_cnt = 0;
    e[++edge_cnt] = {v, head[u]};
    head[u] = edge_cnt;
}
ll a[MAXN], b[MAXN];
int n, m, k, fa[19][MAXN], dep[MAXN];
Matrix down[19][MAXN], up[19][MAXN];
Matrix f0;
Matrix gettrans(int i, ll del = 1e18)
{
    Matrix c = 1e18;
    switch (k)
    {
    case 1:
        c[0][0] = a[i];
        break;
    case 2:
        c[0][1] = 0, c[0][0] = c[1][0] = a[i];
        break;
    case 3:
        c[0][0] = c[1][0] = c[2][0] = a[i], c[0][1] = c[1][2] = 0, c[1][1] = min(b[i], del);
        break;
    }
    return c;
}
void dfs(int u, int f)
{
    dep[u] = dep[fa[0][u] = f] + 1, b[u] = 1e18;
    for (int i = head[u]; i; i = e[i].nxt)
    {
        int v = e[i].v;
        if (v == f)
            continue;
        dfs(v, u), b[u] = min(b[u], a[v]);
    }
    down[0][u] = up[0][u] = gettrans(u);
}
int lca(int u, int v)
{
    if (dep[u] < dep[v])
        swap(u, v);
    int d = dep[u] - dep[v];
    for (int j = 18; j >= 0; j--)
        if (d >> j & 1)
            u = fa[j][u];
    if (u == v)
        return u;
    for (int j = 18; j >= 0; j--)
        if (fa[j][u] != fa[j][v])
            u = fa[j][u], v = fa[j][v];
    return fa[0][u];
}
Matrix qdown(int u, int k)
{
    Matrix res = 0;
    for (int j = 18; j >= 0; j--)
        if (k >> j & 1)
            res = down[j][u] * res, u = fa[j][u];
    return res;
}
Matrix qup(int u, int k)
{
    Matrix res = 0;
    for (int j = 18; j >= 0; j--)
        if (k >> j & 1)
            res = res * up[j][u], u = fa[j][u];
    return res;
}
ll solve(int u, int v)
{
    int k = lca(u, v);
    Matrix res = f0 * qup(u, dep[u] - dep[k]) * gettrans(k, a[fa[0][k]]) * qdown(v, dep[v] - dep[k]);
    return min({res[0][0] - a[v], res[0][1], res[0][2]}) + a[v];
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m >> k;
    f0[0][k - 1] = 0, a[0] = 1e18;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1, u, v; i < n; i++)
        cin >> u >> v, addedge(u, v), addedge(v, u);
    dfs(1, 0);
    for (int j = 1; j <= 18; j++)
    {
        for (int i = 1; i <= n; i++)
            fa[j][i] = fa[j - 1][fa[j - 1][i]];
        for (int i = 1; i <= n; i++)
            down[j][i] = down[j - 1][fa[j - 1][i]] * down[j - 1][i];
        for (int i = 1; i <= n; i++)
            up[j][i] = up[j - 1][i] * up[j - 1][fa[j - 1][i]];
    }
    for (int u, v; m--;)
        cin >> u >> v, cout << solve(u, v) << endl;
    return 0;
}
