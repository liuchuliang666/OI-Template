#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int MAXN = 1e5 + 10, MAXM = 2e5 + 10;
int n, m, head[MAXN], oud[MAXN];
double f[MAXN];
struct edge
{
    int v, w, nxt;
} e[MAXM];
inline void addedge(int u, int v, int w)
{
    static int edge_cnt = 0;
    e[++edge_cnt] = {v, w, head[u]};
    head[u] = edge_cnt;
    oud[u]++;
}
double dfs(int u)
{
    if (f[u] != -1)
        return f[u];
    f[u] = 0;
    for (int i = head[u]; i; i = e[i].nxt)
    {
        int v = e[i].v, w = e[i].w;
        f[u] += dfs(v) + w;
    }
    return f[u] /= oud[u];
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1, u, v, w; i <= m; i++)
        cin >> u >> v >> w, addedge(u, v, w);
    fill(f + 1, f + 1 + n, -1);
    f[n] = 0;
    cout << fixed << setprecision(2) << dfs(1);
    return 0;
}