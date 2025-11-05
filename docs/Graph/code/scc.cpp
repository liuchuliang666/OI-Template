#include <bits/stdc++.h>
using namespace std;
#define TEMPTK template <typename T = int, typename K = int>
#ifdef ONLINE_JUDGE
#define debug(...) (0)
struct __CERR
{
    TEMPTK __CERR &operator<<(const T &x) { return *this; }
} __cerr;
#define cerr __cerr
#define endl '\n'
#else
#define debug(...) fprintf(stderr, ##__VA_ARGS__)
#endif
#ifdef CPH
#define openfile(x) (0)
#define endl '\n'
#else
#define openfile(x) (freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout))
#endif
#define ef emplace_front
#define eb emplace_back
#define ep emplace
#define pb push_back
#define ins insert
#define fi first
#define se second
#define SZ(x) int((x).size())
#define ALL(x) (x).begin(), (x).end()
#define rep(i, l, r, ...) for (int i = int(l), ##__VA_ARGS__; i <= int(r); ++i)
#define per(i, r, l, ...) for (int i = int(r), ##__VA_ARGS__; i >= int(l); --i)
#define Rep(i, l, r, ...) for (int i = int(l), i##e = int(r), ##__VA_ARGS__; i <= i##e; ++i)
#define Per(i, r, l, ...) for (int i = int(r), i##e = int(l), ##__VA_ARGS__; i >= i##e; --i)
#define Mst(x, val, len) memset(x, val, sizeof((x)[0]) * int(len))
#define Mcp(from, to, len) memcpy(to, from, sizeof((to)[0]) * int(len))
#define mst(x, val) memset(x, val, sizeof(x))
#define mcp(from, to) memcpy(to, from, sizeof(from))
#define Bit(x) (int(1) << (x))
#define Add(a, b) ((a) = tadd((a), (b)))
#define Mul(a, b) ((a) = qmul((a), (b)))
#define add(a, b) (((a) += (b)) >= P ? (a) -= P : (a))
#define mul(a, b) (((a) *= (b)) %= P)
#define mid (((l) + (r)) >> 1)
#define ls ((x) << 1)
#define rs ((x) << 1 | 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define pbds __gnu_pbds
#define i128 __int128
// #define int ll
typedef long long ll;
typedef unsigned long long ull;
#define db double
typedef long double ld;
#define vi vector<int>
#define vii vector<vi>
#define pii pair<int, int>
#define vpii vector<pii>
#define chkmx(a, b) ((a) = max((a), (b)))
#define chkmn(a, b) ((a) = min((a), (b)))
constexpr int inf = (sizeof(int) == 4 ? 1e9 : 1e15), INF = numeric_limits<int>::max() / 2;
mt19937 rnd(random_device{}());
namespace LCL
{
    constexpr int MAXN = 1e4 + 10, MAXV = MAXN << 2, P = 998244353;
    auto min = [](auto x, auto y) { return x < y ? x : y; };
    auto max = [](auto x, auto y) { return x < y ? y : x; };
    auto tadd = [](auto x, auto y) { return add(x, y); };
    auto cadd = [](auto x, auto y) { return x + min(y, inf - x); };
    auto qmul = [](auto x, auto y) { return (x = (ull)x * y - (ull)((ld)x / P * y) * P) < 0 ? x + P : x; };
    auto cmod = [](auto x) { return (x %= P) < 0 ? x + P : x; };
    auto abs = [](auto x) { return x < 0 ? -x : x; };
    auto lowb = [](auto x) { return x & (-x); };
    int n, m, a[MAXN], w[MAXN], dfc, dfn[MAXN], low[MAXN], scc[MAXN], sidx, dp[MAXN], stk[MAXN], tp;
    vi e[MAXN], g[MAXN];
    bitset<MAXN> vis;
    void dfs(int u)
    {
        if (vis[u]) return;
        for (int v : g[u]) dfs(v), chkmx(dp[u], dp[v]);
        dp[u] += w[u], vis[u] = 1;
    }
    void tarjan(int u)
    {
        dfn[u] = low[u] = ++dfc, stk[++tp] = u;
        for (int v : e[u])
            if (!dfn[v])
                tarjan(v), chkmn(low[u], low[v]);
            else if (!scc[v])
                chkmn(low[u], dfn[v]);
        if (low[u] == dfn[u])
        {
            sidx++;
            do scc[stk[tp]] = sidx, w[sidx] += a[stk[tp]];
            while (stk[tp--] ^ u);
        }
    }
    void main()
    {
        cin >> n >> m;
        rep(i, 1, n) cin >> a[i];
        rep(i, 1, m, u, v) cin >> u >> v, e[u].eb(v);
        rep(i, 1, n) if (!dfn[i]) tarjan(i);
        rep(u, 1, n) for (int v : e[u]) if (scc[u] ^ scc[v]) g[scc[u]].eb(scc[v]);
        rep(i, 1, sidx) dfs(i);
        cout << *max_element(dp + 1, dp + 1 + sidx);
    }
} // namespace LCL
signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--) LCL::main();
    return 0;
}