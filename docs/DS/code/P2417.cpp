#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
#define mid ((l + r) >> 1)
#define ls ((x) << 1)
#define rs ((x) << 1 | 1)
const int MAXN = 1e5 + 10, MAXM = 2e5 + 10, MAXV = MAXM << 2;
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
int n, q;
map<ll, int> edge;
vector<ll> tr[MAXV];
ll qry[MAXM];
struct DSU
{
    int f[MAXN], stktop, dep[MAXN], siz[MAXN];
    struct oper
    {
        int x, y; // f[y] = x, dep[x] += add, siz[x] += siz[y]
        bool add;
    } his[MAXM];
    inline void init(int n)
    {
        stktop = 0;
        for (int i = 1; i <= n; i++) f[i] = i, dep[i] = siz[i] = 1;
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
    inline int qry(const int x) { return siz[getf(x)]; }
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
        if (qry[l])
        {
            int p, q;
            dec(qry[l], p, q);
            cout << dsu.qry(p) * dsu.qry(q) << endl;
        }
    }
    else
        solve(ls, l, mid), solve(rs, mid + 1, r);
    while (dsu.stktop > tp) dsu.back();
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> q;
    dsu.init(n);
    char ch;
    int x, y, tim = 0;
    ll id;
    for (int i = 1; i <= q; i++)
    {
        cin >> ch >> x >> y;
        id = enc(x, y);
        switch (ch)
        {
        case 'A':
            edge[id] = ++tim;
            break;
        case 'Q':
            insert(1, 1, q << 1, edge[id], tim++, id);
            qry[tim] = id;
            edge[id] = ++tim;
            break;
        }
    }
    for (auto [id, t] : edge)
        if (t)
        {
            dec(id, x, y);
            insert(1, 1, q << 1, t, tim, id);
        }
    solve(1, 1, q << 1);
    return 0;
}