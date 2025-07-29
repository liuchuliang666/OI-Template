#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e4 + 10;
vector<int> e[MAXN];
int n, m, dfn[MAXN], low[MAXN], dfnidx, rt, cnt;
bool flg[MAXN];
void tarjan(int u, int f)
{
    dfn[u] = low[u] = ++dfnidx;
    int chcnt = 0;
    for (int v : e[u])
    {
        if (!dfn[v])
        {
            chcnt++;
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (dfn[u] <= low[v] && u != rt) cnt += !flg[u], flg[u] = 1;
            if (u == rt && chcnt > 1) cnt += !flg[u], flg[u] = 1;
        }
        else if (v ^ f)
            low[u] = min(low[u], dfn[v]);
    }
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    for (rt = 1; rt <= n; rt++)
        if (!dfn[rt]) tarjan(rt, 0);
    cout << cnt << endl;
    for (int i = 1; i <= n; i++)
        if (flg[i]) cout << i << " ";
    return 0;
}