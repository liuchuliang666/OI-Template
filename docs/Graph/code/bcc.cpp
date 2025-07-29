#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5e5 + 10, MAXM = 2e6 + 10;
int n, m, bccidx, bcc[MAXN], head[MAXN], idx, low[MAXN], dfn[MAXN];
vector<vector<int>> ans;
bitset<MAXN> inq;
stack<int> stk;
struct edge
{
    int v, nxt;
} e[MAXM << 1];
inline void addedge(int u, int v)
{
    static int edge_cnt = 1;
    e[++edge_cnt] = {v, head[u]};
    head[u] = edge_cnt;
}
void dfs(int u, int f)
{
    dfn[u] = low[u] = ++idx;
    stk.push(u), inq[u] = 1;
    for (int i = head[u]; i; i = e[i].nxt)
        if (f != i && (f ^ 1) != i)
        {
            int v = e[i].v;
            if (!dfn[v])
            {
                dfs(v, i);
                low[u] = min(low[v], low[u]);
            }
            else if (inq[v])
                low[u] = min(low[u], dfn[v]);
        }
    if (low[u] == dfn[u])
    {
        int tp;
        bccidx++;
        vector<int> tmp;
        do
        {
            tp = stk.top();
            stk.pop();
            inq[tp] = 0;
            bcc[tp] = bccidx;
            tmp.push_back(tp);
        } while (tp != u);
        ans.push_back(tmp);
    }
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int u, v, i = 1; i <= m; i++)
        cin >> u >> v, addedge(u, v), addedge(v, u);
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) dfs(i, 0);
    cout << ans.size() << endl;
    for (auto tbcc : ans)
    {
        cout << tbcc.size() << " ";
        for (auto x : tbcc) cout << x << " ";
        cout << endl;
    }
    return 0;
}