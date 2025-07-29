#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
constexpr int MAXN = 3e5 + 10, MAXV = MAXN << 1;
int n, m, fa[MAXN], deg[MAXN], rt[MAXN], tot, ls[MAXV], rs[MAXV], dep[MAXV];
ll ans, val[MAXV], w[MAXN];
inline int newnode(const ll v) { return val[++tot] = v, tot; }
int merge(int x, int y)
{
    if (!x || !y) return x | y;
    if (val[x] < val[y]) swap(x, y);
    rs[x] = merge(rs[x], y);
    if (dep[ls[x]] < dep[rs[x]]) swap(ls[x], rs[x]);
    return dep[x] = dep[rs[x]] + 1, x;
}
void pop(int &x) { x = merge(ls[x], rs[x]); }
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 2; i <= n + m; i++) cin >> fa[i] >> w[i], ans += w[i], deg[fa[i]]++;
    for (int u = n + m; u >= 2; u--)
    {
        if (u <= n)
            while (deg[u]-- > 1) pop(rt[u]);
        ll lv = val[rt[u]];
        pop(rt[u]);
        ll rv = val[rt[u]];
        pop(rt[u]);
        rt[u] = merge(rt[u], merge(newnode(lv + w[u]), newnode(rv + w[u])));
        rt[fa[u]] = merge(rt[fa[u]], rt[u]);
    }
    while (deg[1]--) pop(rt[1]);
    while (rt[1]) ans -= val[rt[1]], pop(rt[1]);
    cout << ans;
    return 0;
}