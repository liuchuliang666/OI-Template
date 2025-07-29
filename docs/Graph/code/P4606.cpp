#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 10, MAXNN = MAXN << 1;
vector<int> e[MAXN], t[MAXNN];
int n, m, q, idx, low[MAXN], s[MAXNN], ss, dfn[MAXNN], tp, stk[MAXN], cnt, fa[MAXNN][20], deep[MAXNN], dis[MAXNN];
void tarjan(int u)
{
    stk[++tp] = u;
    low[u] = dfn[u] = ++idx;
    for (int v : e[u])
        if (!dfn[v])
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
            if (low[v] == dfn[u])
            {
                cnt++;
                for (int x = 0; x != v; tp--)
                {
                    x = stk[tp];
                    t[x].push_back(cnt);
                    t[cnt].push_back(x);
                }
                t[cnt].push_back(u);
                t[u].push_back(cnt);
            }
        }
        else
            low[u] = min(low[u], dfn[v]);
}
void dfs(int u, int f)
{
    deep[u] = deep[fa[u][0] = f] + 1;
    dfn[u] = ++idx;
    dis[u] = dis[f] + (u <= n);
    for (int i = 1; i <= log2(deep[u]); i++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (int v : t[u])
        if (v ^ f) dfs(v, u);
}
inline int getlca(int x, int y)
{
    if (deep[x] < deep[y]) swap(x, y);
    int d = deep[x] - deep[y];
    for (int i = 0; i <= log2(d); i++)
        if (d & (1ll << i)) x = fa[x][i];
    if (x == y) return x;
    for (int i = log2(deep[x]); i + 1; i--)
        if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}
inline int solve()
{
    int ans = -2 * ss;
    sort(s + 1, s + 1 + ss, [&](int x, int y)
         { return dfn[x] < dfn[y]; });
    for (int i = 1; i <= ss; i++)
    {
        int u = s[i], v = s[i % ss + 1];
        ans += dis[u] + dis[v] - 2 * dis[getlca(u, v)];
    }
    if (getlca(s[1], s[ss]) <= n) ans += 2;
    return ans / 2;
}
void mainsolve()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        e[i].clear();
        t[i].clear();
        t[i + n].clear();
        dfn[i] = low[i] = 0;
    }
    for (int u, v, i = 1; i <= m; i++)
    {
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    idx = 0, cnt = n;
    tarjan(1), tp--;
    idx = 0, dfs(1, 0);
    cin >> q;
    while (q--)
    {
        cin >> ss;
        for (int i = 1; i <= ss; i++) cin >> s[i];
        cout << solve() << "\n";
    }
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) mainsolve();
    return 0;
}