#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const int MAXN = 1e5 + 10, MAXM = 2e5 + 10, MAXV = 4e5 + 10;
const ll inf = 1e9;
int n, m, dfn[MAXN], top[MAXN], ed[MAXN], fa[MAXN], siz[MAXN], idx, son[MAXN], idfn[MAXN];
ll a[MAXN], f[MAXN][2];
vector<int> e[MAXN];
struct Matrix
{
    ll val[2][2];
    ll *operator[](const int x) { return val[x]; }
    Matrix() { val[1][1] = val[1][0] = val[0][1] = val[0][0] = -inf; }
} g[MAXN], bef, aft, ans;
inline void chkmx(ll &a, ll b) { a = a < b ? b : a; }
Matrix operator*(Matrix a, Matrix b)
{
    Matrix c;
    for (int i = 0; i <= 1; i++)
        for (int j = 0; j <= 1; j++)
            for (int k = 0; k <= 1; k++) chkmx(c[i][j], a[i][k] + b[k][j]);
    return c;
}
namespace sgt
{
#define mid ((l + r) >> 1)
#define ls ((x) << 1)
#define rs ((x) << 1 | 1)
    Matrix tr[MAXV];
    void pu(int x) { tr[x] = tr[ls] * tr[rs]; }
    void build(int x, int l, int r)
    {
        if (l == r)
        {
            tr[x] = g[idfn[l]];
            return;
        }
        build(ls, l, mid);
        build(rs, mid + 1, r);
        pu(x);
    }
    void update(int x, int l, int r, int p)
    {
        if (l == p && p == r)
        {
            tr[x] = g[idfn[p]];
            return;
        }
        if (p <= mid)
            update(ls, l, mid, p);
        else
            update(rs, mid + 1, r, p);
        pu(x);
    }
    Matrix query(int x, int l, int r, int pl, int pr)
    {
        if (pl <= l && r <= pr) return tr[x];
        if (pr <= mid) return query(ls, l, mid, pl, pr);
        if (mid < pl) return query(rs, mid + 1, r, pl, pr);
        return query(ls, l, mid, pl, pr) * query(rs, mid + 1, r, pl, pr);
    }
} // namespace sgt
void dfs1(int u, int f)
{
    fa[u] = f;
    siz[u] = 1;
    for (int v : e[u])
        if (v ^ f)
        {
            dfs1(v, u);
            siz[u] += siz[v];
            if (siz[son[u]] < siz[v]) son[u] = v;
        }
}
void dfs2(int u, int tp)
{
    dfn[u] = ++idx;
    idfn[idx] = u;
    top[u] = tp;
    ed[u] = u;
    g[u][0][0] = g[u][0][1] = 0;
    g[u][1][0] = a[u];
    if (son[u])
    {
        dfs2(son[u], tp);
        ed[u] = ed[son[u]];
        f[u][0] += max(f[son[u]][0], f[son[u]][1]);
        f[u][1] += f[son[u]][0];
    }
    for (int v : e[u])
        if (!dfn[v])
        {
            dfs2(v, v);
            g[u][0][0] += max(f[v][0], f[v][1]);
            g[u][1][0] += f[v][0];
        }
    g[u][0][1] = g[u][0][0];
    f[u][0] += g[u][0][0];
    f[u][1] += g[u][1][0];
}
void solve()
{
    int u;
    ll w;
    cin >> u >> w;
    g[u][1][0] += w - a[u];
    a[u] = w;
    while (u)
    {
        bef = sgt::query(1, 1, n, dfn[top[u]], dfn[ed[u]]);
        sgt::update(1, 1, n, dfn[u]);
        aft = sgt::query(1, 1, n, dfn[top[u]], dfn[ed[u]]);
        u = fa[top[u]];
        g[u][0][0] += max(aft[0][0], aft[1][0]) - max(bef[0][0], bef[1][0]);
        g[u][1][0] += aft[0][0] - bef[0][0];
        g[u][0][1] = g[u][0][0];
    }
    ans = sgt::query(1, 1, n, dfn[top[1]], dfn[ed[1]]);
    cout << max(ans[0][0], ans[1][0]) << endl;
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int u, v, i = 1; i < n; i++) cin >> u >> v, e[u].push_back(v), e[v].push_back(u);
    dfs1(1, 0);
    dfs2(1, 1);
    sgt::build(1, 1, n);
    while (m--) solve();
    return 0;
}