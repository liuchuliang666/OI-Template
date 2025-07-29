#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e4 + 10, MAXM = 1e5 + 10;
vector<int> e1[MAXN], e2[MAXN];
int n, m, sccno[MAXN], idx, low[MAXN], dfn[MAXN], ind[MAXN], w1[MAXN], w2[MAXN],
    sccidx;
bool inq[MAXN];
queue<int> q;
stack<int> sta;
int ans, dp[MAXN];
void dfs(int u)
{
    dfn[u] = low[u] = ++idx;
    inq[u] = 1;
    sta.push(u);
    for (int v : e1[u])
    {
        if (!dfn[v])
        {
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
        else if (inq[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u])
    {
        sccidx++;
        int tp;
        do
        {
            tp = sta.top();
            sta.pop();
            w2[sccidx] += w1[tp];
            sccno[tp] = sccidx;
            inq[tp] = false;
        } while (tp != u);
    }
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> w1[i];
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        e1[u].push_back(v);
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) dfs(i);
    for (int u = 1; u <= n; u++)
        for (int v : e1[u])
            if (sccno[u] != sccno[v])
                e2[sccno[u]].push_back(sccno[v]), ind[sccno[v]]++;
    for (int u = 1; u <= sccidx; u++)
        if (!ind[u]) q.push(u);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        dp[u] += w2[u];
        ans = max(ans, dp[u]);
        for (int v : e2[u])
        {
            ind[v]--;
            dp[v] = max(dp[v], dp[u]);
            if (!ind[v]) q.push(v);
        }
    }
    cout << ans;
    return 0;
}