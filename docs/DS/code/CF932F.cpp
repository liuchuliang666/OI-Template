#include <bits/stdc++.h>
using namespace std;
// #define ONLINE_JUDGE
#define Debug(...) fprintf(stderr, ##__VA_ARGS__)
#ifdef ONLINE_JUDGE
#define debug(...)
#else
#define debug Debug
#endif
#define endl '\n'
#define eb emplace_back
#define ep emplace
#define pb push_back
#define pp push
#define ins insert
#define fi first
#define se second
#define SZ(x) int((x).size())
#define ALL(x) (x).begin(), (x).end()
#define rep(i, l, r, ...) for (int i = (l), ##__VA_ARGS__; i <= (r); ++i)
#define per(i, r, l, ...) for (int i = (r), ##__VA_ARGS__; i >= (l); --i)
#define mst(x, val, len) memset(x, val, sizeof((x)[0]) * int(len))
#define mcp(from, to, len) memcpy(to, from, sizeof((to)[0]) * int(len))
#define Mst(x, val) memset(x, val, sizeof(x))
#define Mcp(from, to) memcpy(to, from, sizeof(from))
#define lowbit(x) ((x) & (-x))
#define Add(a, b) ((a) = (((a) + (b)) % P + P) % P)
#define Mul(a, b) ((a) = (((a) * (b)) % P + P) % P)
#define add(a, b) (((a) += (b)) >= P ? (a) -= P : (a))
#define dec(a, b) (((a) -= (b)) < 0 ? (a) += P : (a))
#define mul(a, b) (((a) *= (b)) %= P)
#define chkmx(a, b) ((a) = max((a), (b)))
#define chkmn(a, b) ((a) = min((a), (b)))
#define mid (((l) + (r)) >> 1)
#define lson ls[x], l, mid
#define rson rs[x], mid + 1, r
#define pbds __gnu_pbds
#define i128 __int128
#define int ll
typedef long long ll;
#define db double
typedef long double ld;
#define vi vector<int>
#define vii vector<vi>
#define pii pair<int, int>
#define vpii vector<pii>
constexpr int MAXN = 2e5 + 10, inf = 1e18, P = 998244353, MAXV = MAXN << 5;
bool MST;
struct seg
{
    int k = 0, b = inf;
    int operator()(int x) { return k * x + b; }
} s[MAXN];
int n, a[MAXN], b[MAXN], dp[MAXN], tr[MAXV], ls[MAXV], rs[MAXV], tot, rt[MAXN];
vi e[MAXN];
void upd(int &x, int l, int r, int id1)
{
    int &id2 = tr[x ? x : (x = ++tot)];
    if (s[id1](mid) < s[id2](mid)) swap(id1, id2);
    if (s[id1](l) < s[id2](l)) upd(lson, id1);
    if (s[id1](r) < s[id2](r)) upd(rson, id1);
}
int qry(int x, int l, int r, int p)
{
    int res = s[tr[x]](p);
    if (l == r || !x) return res;
    if (p <= mid)
        chkmn(res, qry(lson, p));
    else
        chkmn(res, qry(rson, p));
    return res;
}
int merge(int x, int y, int l, int r)
{
    if (!x || !y) return x | y;
    if (l == r) return (s[tr[x]](l) < s[tr[y]](l) ? x : y);
    ls[x] = merge(ls[x], ls[y], l, mid);
    rs[x] = merge(rs[x], rs[y], mid + 1, r);
    return upd(x, l, r, tr[y]), x;
}
void dfs(int u, int f)
{
    for (int v : e[u])
        if (v ^ f) dfs(v, u), rt[u] = merge(rt[u], rt[v], -1e5, 1e5);
    if (rt[u]) dp[u] = qry(rt[u], -1e5, 1e5, a[u]);
    s[u] = {b[u], dp[u]}, upd(rt[u], -1e5, 1e5, u);
}
void solve()
{
    cin >> n;
    rep(i, 1, n) cin >> a[i];
    rep(i, 1, n) cin >> b[i];
    rep(i, 2, n, u, v) cin >> u >> v, e[u].eb(v), e[v].eb(u);
    dfs(1, 0);
    rep(i, 1, n) cout << dp[i] << " ";
}
bool MED;
signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    Debug("Memory Used: %.2lf Mib.\n", (&MST - &MED) / 1024. / 1024.);
    int T = 1;
    // cin >> T;
    while (T--) solve();
    return 0;
}