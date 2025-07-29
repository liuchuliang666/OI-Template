#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define eb emplace_back
#define ep emplace
#define fi first
#define se second
#define rep(i, l, r, ...) for (int i = (l), i##e = (r), ##__VA_ARGS__; i <= i##e; ++i)
#define per(i, r, l, ...) for (int i = (r), i##e = (l), ##__VA_ARGS__; i >= i##e; --i)
#define mst(x, val) memset(x, val, sizeof(x))
#define mcp(from, to) memcpy(to, from, sizeof(to))
#define mid (((l) + (r)) >> 1)
#define int ll
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
constexpr int MAXN = 250, MAXM = 5010, inf = 1e18;
int n, m, s, t, cur[MAXN], dep[MAXN];
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
inline void adde(int u, int v, int w) { addedge(u, v, w), addedge(v, u, 0); }
inline bool bfs()
{
    queue<int> q;
    q.ep(s), mst(dep, 0), dep[s] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        go(u, i)
        {
            int v = e[i].v, w = e[i].w;
            if (w && !dep[v]) dep[v] = dep[u] + 1, q.ep(v);
        }
    }
    return dep[t];
}
int dfs(int u, int flow)
{
    if (u == t) return flow;
    int now = 0;
    for (int &i = cur[u]; i && now ^ flow; i = e[i].nxt)
    {
        int v = e[i].v, w = e[i].w;
        if (!w || dep[v] != dep[u] + 1) continue;
        int res = dfs(v, min(w, flow - now));
        if (!res) dep[v] = inf;
        now += res, e[i].w -= res, e[i ^ 1].w += res;
    }
    return now;
}
int Dinic()
{
    int maxflow = 0, res = 0;
    while (bfs()) mcp(head, cur), maxflow += dfs(s, inf);
    return maxflow;
}
signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m >> s >> t;
    rep(i, 1, m, u, v, w) cin >> u >> v >> w, adde(u, v, w);
    cout << Dinic();
    return 0;
}