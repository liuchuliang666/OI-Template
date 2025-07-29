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
constexpr int MAXN = 3e3 + 10, inf = 1e18;
int n, m, h[MAXN], dis[MAXN], ans, t[MAXN];
bitset<MAXN> vis;
vector<pii> e[MAXN];
void spfa(int s)
{
    queue<int> q;
    fill(h, h + n + 1, inf), h[s] = 0, vis[s] = 1;
    q.ep(s);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for (auto [v, w] : e[u])
            if (h[v] > h[u] + w)
            {
                h[v] = h[u] + w;
                if (!vis[v])
                {
                    vis[v] = 1, q.ep(v);
                    if (++t[v] > n) cout << -1, exit(0);
                }
            }
    }
}
void build()
{
    for (int i = 1; i <= n; i++) e[0].eb(i, 0);
    spfa(0);
    for (int u = 1; u <= n; u++)
        for (auto &[v, w] : e[u]) w += h[u] - h[v];
}
void dijkstra(int s)
{
    priority_queue<pii, vector<pii>, greater<>> pq;
    fill(dis + 1, dis + n + 1, inf), pq.ep(dis[s] = 0, s), vis = 0;
    while (!pq.empty())
    {
        int u = pq.top().se;
        pq.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto [v, w] : e[u])
            if (dis[v] > dis[u] + w)
                pq.ep(dis[v] = dis[u] + w, v);
    }
    ans = 0;
    for (int t = 1; t <= n; t++) ans += t * (dis[t] == inf ? 1e9 : (dis[t] + h[t] - h[s]));
    cout << ans << endl;
}
signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int u, v, w, i = 1; i <= m; i++) cin >> u >> v >> w, e[u].eb(v, w);
    build();
    for (int i = 1; i <= n; i++) dijkstra(i);
    return 0;
}