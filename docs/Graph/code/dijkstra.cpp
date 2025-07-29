#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define eb emplace_back
#define ep emplace
#define fi first
#define se second
#define mst(x, val) memset(x, val, sizeof(x))
#define mcp(from, to) memcpy(to, from, sizeof(to))
#define int ll
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
constexpr int MAXN = 2e5 + 10;
priority_queue<pii, vector<pii>, greater<>> pq; // (dis, u)
bitset<MAXN> vis;
vector<pii> e[MAXN];
int dis[MAXN];
void dijkstra(int s)
{
    mst(dis, 0x3f), pq.ep(dis[s] = 0, s);
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
}
signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    return 0;
}