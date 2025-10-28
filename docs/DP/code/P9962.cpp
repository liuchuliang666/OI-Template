#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
const int MAXN = 5e5 + 10;
int n, m, dep[MAXN], ls[MAXN], rs[MAXN], siz[MAXN], f[MAXN], g[MAXN], tag[MAXN], val[MAXN];
vector<int> e[MAXN];
void addtag(int x, int v) { val[x] += v, tag[x] += v; }
void pd(int x)
{
    if (tag[x]) addtag(ls[x], tag[x]), addtag(rs[x], tag[x]), tag[x] = 0;
}
void pu(int x) { siz[x] = siz[ls[x]] + siz[rs[x]] + 1, dep[x] = dep[rs[x]] + 1; }
int merge(int x, int y)
{
    if (!x || !y) return x | y;
    if (val[x] < val[y]) swap(x, y);
    pd(x), pd(y), rs[x] = merge(rs[x], y);
    if (dep[ls[x]] < dep[rs[x]]) swap(ls[x], rs[x]);
    return pu(x), x;
}
int pop(int &x)
{
    int p = x;
    return pd(x), x = merge(ls[x], rs[x]), ls[p] = rs[p] = dep[p] = 0, siz[p] = 1, p;
}
void dfs(int u, int fa)
{
    for (int v : e[u])
        if (v ^ fa)
        {
            dfs(v, u), addtag(f[v], -2);
            if (m & 1 && g[v])
            {
                int rt = pop(g[v]);
                addtag(g[v], -2), g[v] = merge(g[v], rt);
            }
            else
                addtag(g[v], -2);
            f[u] = merge(f[u], f[v]), g[u] = merge(g[u], g[v]);
        }
    while (siz[f[u]] > (m >> 1))
    {
        int x = pop(f[u]);
        val[x] *= -1;
        g[u] = merge(g[u], pop(x));
    }
}
main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int u, v, i = 1; i < n; i++) cin >> u >> v, e[u].emplace_back(v), e[v].emplace_back(u);
    for (int i = 1; i <= n; i++) siz[i] = 1, f[i] = i;
    dfs(1, 0);
    int ans = (n - 1) * m;
    for (int i = 1; i <= m; i++)
        if (f[1])
            ans += val[pop(f[1])];
        else
            ans -= val[pop(g[1])];
    cout << ans;
    return 0;
}