#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
#define mid ((l + r) >> 1)
#define ls ((x) << 1)
#define rs ((x) << 1 | 1)
const int MAXN = 1e6 + 10, MAXM = 2e6 + 10, MAXV = MAXM << 2, MAXW = 1e5 + 1;
inline ll enc(int u, int v)
{
    if (u > v) swap(u, v);
    return 1ll * u * MAXN + v;
}
inline void dec(ll id, int &u, int &v)
{
    u = id / ll(MAXN);
    v = id % ll(MAXN);
}
int n, m;
vector<ll> tr[MAXV];
struct DSU
{
    int f[MAXN], stktop, dep[MAXN], siz[MAXN];
    struct oper
    {
        int x, y; // f[y] = x, dep[x] += add, siz[x] += siz[y];
        bool add;
    } his[MAXM];
    inline void init()
    {
        stktop = 0;
        for (int i = 1; i <= n; i++) f[i] = i, siz[i] = dep[i] = 1;
    }
    inline int getf(int x)
    {
        while (x != f[x]) x = f[x];
        return x;
    }
    inline void merge(int x, int y)
    {
        x = getf(x), y = getf(y);
        if (x == y) return;
        if (dep[x] < dep[y]) swap(x, y);
        his[++stktop] = {x, y, dep[x] == dep[y]};
        dep[x] += dep[x] == dep[y];
        siz[x] += siz[y];
        f[y] = x;
    }
    inline void back()
    {
        const auto [x, y, add] = his[stktop--];
        dep[x] -= add;
        siz[x] -= siz[y];
        f[y] = y;
    }
    inline bool qry() { return siz[getf(1)] == n; }
} dsu;
void insert(int x, int l, int r, int pl, int pr, ll v)
{
    if (pl <= l && r <= pr) return tr[x].emplace_back(v), void();
    if (pl <= mid) insert(ls, l, mid, pl, pr, v);
    if (mid < pr) insert(rs, mid + 1, r, pl, pr, v);
}
void solve(int x, int l, int r)
{
    int tp = dsu.stktop;
    for (ll v : tr[x])
    {
        int p, q;
        dec(v, p, q);
        dsu.merge(p, q);
    }
    if (l == r)
    {
        if (dsu.qry())
        {
            cout << l;
            exit(0);
        }
    }
    else
        solve(ls, l, mid), solve(rs, mid + 1, r);
    while (dsu.stktop > tp) dsu.back();
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    dsu.init();
    string ch;
    int u, v, w;
    for (int i = 1; i <= m; i++)
    {
        cin >> u >> v >> w;
        if (w) insert(1, 0, MAXW, 0, w - 1, enc(u, v));
        insert(1, 0, MAXW, w + 1, MAXW, enc(u, v));
    }
    solve(1, 0, MAXW);
    return 0;
}