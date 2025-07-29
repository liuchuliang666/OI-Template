#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1e5 + 10;
vector<int> e[MAXN], t[MAXN << 1];
int n, m, cnt, idx, low[MAXN], dfn[MAXN], stk[MAXN], top;
ll w[MAXN << 1], ans, tsiz, siz[MAXN << 1];
void tarjan(int u)
{
    low[u] = dfn[u] = ++idx;
    tsiz++;
    stk[++top] = u;
    for (int v : e[u])
        if (!dfn[v])
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
            if (low[v] == dfn[u])
            {
                cnt++;
                for (int tp = 0; tp != v; top--)
                {
                    tp = stk[top];
                    t[cnt].push_back(tp);
                    t[tp].push_back(cnt);
                    w[cnt]++;
                }
                t[cnt].push_back(u);
                t[u].push_back(cnt);
                w[cnt]++;
            }
        }
        else
            low[u] = min(low[u], dfn[v]);
}
void dfs(int u, int f)
{
    siz[u] = u <= n;
    for (int v : t[u])
        if (v ^ f)
        {
            dfs(v, u);
            ans += 2 * w[u] * siz[u] * siz[v];
            siz[u] += siz[v];
        }
    ans += 2 * w[u] * siz[u] * (tsiz - siz[u]);
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) w[i] = -1;
    cnt = n;
    for (int u, v, i = 1; i <= m; i++)
    {
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
        {
            tsiz = 0;
            tarjan(i);
            top = 0;
            dfs(i, 0);
        }
    cout << ans;
    return 0;
}