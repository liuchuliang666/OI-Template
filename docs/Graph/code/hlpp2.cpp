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
constexpr int MAXN = 1.2e3 + 10, inf = 0x3f3f3f3f3f3f3f3f, MAXM = 1.2e5 + 10;
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
int h[MAXN], ex[MAXN], gap[MAXN], n, m, s, t;
priority_queue<pii> pq;
bool push(int u)
{
    bool init = u == s;
    go(u, i)
    {
        int v = e[i].v, w = e[i].w;
        if (!w || (!init && h[u] != h[v] + 1) || h[v] == inf) continue;
        int k = init ? w : min(w, ex[u]);
        if (v ^ s && v ^ t && !ex[v]) pq.ep(h[v], v);
        ex[u] -= k, ex[v] += k, e[i].w -= k, e[i ^ 1].w += k;
        if (!ex[u]) return 0;
    }
    return 1;
}
void relabel(int u)
{
    h[u] = inf;
    go(u, i) if (e[i].w) h[u] = min(h[u], h[e[i].v]);
    if (++h[u] < n)
    {
        pq.ep(h[u], u);
        ++gap[h[u]];
    }
}
bool bfs()
{
    queue<int> q;
    mst(h, 0x3f), q.ep(t), h[t] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        go(u, i)
        {
            int v = e[i].v;
            if (e[i ^ 1].v && h[v] > h[u] + 1) h[v] = h[u] + 1, q.ep(v);
        }
    }
    return h[s] ^ inf;
}
int select()
{
    while (!pq.empty() && pq.top().fi ^ h[pq.top().se]) pq.pop();
    return pq.empty() ? 0 : pq.top().se;
}
int HLPP()
{
    if (!bfs()) return 0;
    for (int i = 1; i <= n; i++)
        if (h[i] ^ inf) gap[h[i]]++;
    h[s] = n, push(s);
    int u;
    while (u = select())
    {
        pq.pop();
        if (push(u))
        {
            if (!--gap[h[u]])
                for (int i = 1; i <= n; i++)
                    if ((i ^ s) && h[i] > h[u] && h[i] < n + 1)
                        h[i] = n + 1;
            relabel(u);
        }
    }
    return ex[t];
}
signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m >> s >> t;
    for (int u, v, w, i = 1; i <= m; i++) cin >> u >> v >> w, addedge(u, v, w), addedge(v, u, 0);
    cout << HLPP();
    return 0;
}