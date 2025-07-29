#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const int MAXN = 3e5 + 10;
int n, m, head[MAXN], k;
ll ans;
template <class T>
inline void chkmx(T &a, T b)
{
    a = a < b ? b : a;
}
struct node
{
    ll val;
    int now;
    friend bool operator<(node a, node b) { return a.val == b.val ? a.now > b.now : a.val < b.val; }
    friend node operator+(node a, node b) { return {a.val + b.val, a.now + b.now}; }
    friend node operator+(node a, ll b) { return {a.val + b, a.now}; }
} f[MAXN][3];
struct edge
{
    int v;
    ll w;
    int nxt;
} e[MAXN << 1];
void addedge(int u, int v, ll w)
{
    static int edgecnt = 0;
    e[++edgecnt] = {v, w, head[u]};
    head[u] = edgecnt;
}
void dfs(int u, int fa, node dta)
{
    f[u][0] = f[u][1] = f[u][2] = {};
    chkmx(f[u][2], dta);
    for (int i = head[u]; i; i = e[i].nxt)
    {
        auto [v, w, _] = e[i];
        if (v == fa) continue;
        dfs(v, u, dta);
        chkmx(f[u][2], max(f[u][2] + f[v][0], f[u][1] + f[v][1] + w + dta));
        chkmx(f[u][1], max(f[u][1] + f[v][0], f[u][0] + f[v][1] + w));
        chkmx(f[u][0], f[u][0] + f[v][0]);
    }
    chkmx(f[u][0], max(f[u][1] + dta, f[u][2]));
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> k, k++;
    for (int u, v, w, i = 1; i < n; i++) cin >> u >> v >> w, addedge(u, v, w), addedge(v, u, w);
    ll l = -1e12, r = 1e12, mid;
    while (l <= r)
    {
        dfs(1, 1, {mid = l + r >> 1, 1});
        if (f[1][0].now <= k)
            ans = f[1][0].val - k * mid, l = mid + 1;
        else
            r = mid - 1;
    }
    cout << ans;
    return 0;
}