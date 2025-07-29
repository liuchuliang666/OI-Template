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
queue<int> q;
bitset<MAXN> inq;
vector<pii> e[MAXN];
int dis[MAXN];
void spfa(int s)
{
    mst(dis, 0x3f), dis[s] = 0, inq[s] = 1, q.ep(s);
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), inq[u] = 1;
        for (auto [v, w] : e[u])
            if(dis[v] > dis[u] + w)
            {
                dis[v] = dis[u] + w;
                if (!inq[v]) inq[v] = 1, q.ep(v);
            }
    }
}
signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    return 0;
}