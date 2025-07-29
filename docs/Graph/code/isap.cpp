#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define eb emplace_back
#define ep emplace
#define fi first
#define se second
#define mst(x, val) memset(x, val, sizeof(x))
#define mcp(from, to) memcpy(to, from, sizeof(to))
#define mid (((l) + (r)) >> 1)
#define int ll
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
constexpr int MAXN = 200 + 10, MAXM = 5e3 + 10, inf = 1e18;
#define go(u, i) for (int i = head[u]; i; i = e[i].nxt)
struct edge
{
    int v, w, nxt;
} e[MAXM << 1];
int head[MAXN];
inline void addedge(int u, int v, int w)
{
    static int edgecnt = 1;
    e[++edgecnt] = {v, w, head[u]};
    head[u] = edgecnt;
}
int n, m, maxflow, s, t, dep[MAXN], gap[MAXN], cur[MAXN];
void bfs()
{
    queue<int> q;
    mst(dep, -1), gap[dep[t] = 0] = 1, q.ep(t);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        go(u, i)
        {
            int v = e[i].v;
            if (~dep[v]) continue;
            q.ep(v), gap[dep[v] = dep[u] + 1]++;
        }
    }
}
int dfs(int u, int flow)
{
    if (u == t) return flow;
    int now = 0;
    for (int &i = cur[u]; i; i = e[i].nxt)
    {
        int v = e[i].v, w = e[i].w;
        if (dep[u] == dep[v] + 1 && w)
        {
            int res = dfs(v, min(flow - now, w));
            if (res) now += res, e[i].w -= res, e[i ^ 1].w += res;
            if (now == flow) return flow;
        }
    }
    if (!--gap[dep[u]]) dep[s] = n + 1;
    return gap[++dep[u]]++, now;
}
int ISAP()
{
    bfs();
    while (dep[s] < n) mcp(head, cur), maxflow += dfs(s, inf);
    return maxflow;
}
signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m >> s >> t;
    for (int u, v, w, i = 1; i <= m; i++) cin >> u >> v >> w, addedge(u, v, w), addedge(v, u, 0);
    cout << ISAP();
    return 0;
}