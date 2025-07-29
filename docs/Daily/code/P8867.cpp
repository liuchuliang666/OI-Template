#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 5e5 + 10, MAXM = 1e6 + 10, mod = 1e9 + 7;
int n, m, bccidx;
int head[MAXN], head2[MAXN];
int idx, top, stk[MAXN], dfn[MAXN], low[MAXN], bcc[MAXN];
int deg[MAXN], V[MAXN], E[MAXN], s[MAXN];
bitset<MAXN> vis;
ll ans, f[MAXN][2];
struct edge
{
    int v, nxt;
} e[MAXM << 1], e2[MAXM << 1];
void addedge(int u, int v)
{
    static int edge_cnt = 0;
    e[++edge_cnt] = {v, head[u]};
    head[u] = edge_cnt;
}
void addedge2(int u, int v)
{
    static int edge_cnt = 0;
    e2[++edge_cnt] = {v, head2[u]};
    head2[u] = edge_cnt;
}
void tarjan(int u, int fa)
{
    dfn[u] = low[u] = ++idx, vis[stk[++top] = u] = 1;
    for (int i = head[u]; i; i = e[i].nxt)
    {
        int v = e[i].v;
        if (v == fa)
            continue;
        if (!dfn[v])
            tarjan(v, u), low[u] = min(low[u], low[v]);
        else if (vis[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u])
    {
        bccidx++;
        int x;
        do
        {
            vis[x = stk[top--]] = 0, bcc[x] = bccidx;
            V[bccidx]++;
        } while (x != u);
    }
}
ll qpow(ll a, ll b)
{
    ll res = 1;
    while (b)
    {
        if (b & 1)
            res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
void calc(int u, int fa)
{
    s[u] = E[u];
    for (int i = head2[u], v; i; i = e2[i].nxt)
    {
        v = e2[i].v;
        if (v == fa)
            continue;
        calc(v, u);
        s[u] += s[v] + 1;
    }
}
void dfs(int u, int fa)
{
    for (int i = head2[u]; i; i = e2[i].nxt)
    {
        int v = e2[i].v;
        if (v == fa)
            continue;
        dfs(v, u);
        f[u][1] = (f[u][1] * (((f[v][0] << 1) + f[v][1]) % mod) % mod + f[u][0] * f[v][1] % mod) % mod;
        f[u][0] = f[u][0] * ((f[v][0] << 1) % mod) % mod;
    }
    if (u == 1)
        ans = (ans + f[u][1]) % mod;
    else
        ans = (ans + f[u][1] * qpow(2, s[1] - s[u] - 1)) % mod;
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    while (m--)
    {
        int u, v;
        cin >> u >> v;
        addedge(u, v), addedge(v, u);
    }
    tarjan(1, 0);
    for (int u = 1; u <= n; u++)
        for (int i = head[u]; i; i = e[i].nxt)
        {
            int v = e[i].v;
            if (bcc[u] != bcc[v])
                addedge2(bcc[u], bcc[v]);
            else
                E[bcc[u]]++;
        }
    for (int i = 1; i <= bccidx; i++)
    {
        E[i] >>= 1; // 无向边，一条边会算两次，去重
        f[i][0] = qpow(2, E[i]);
        f[i][1] = qpow(2, V[i] + E[i]) - f[i][0];
    }
    calc(1, 0);
    dfs(1, 0);
    cout << ans;
    return 0;
}