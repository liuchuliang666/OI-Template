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
#define int ll
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
    constexpr int MAXN = 5e5 + 10, MAXM = 2e6 + 10, MAXV = MAXN << 2, P = 998244353;
    auto min = [](auto x, auto y) { return x < y ? x : y; };
    auto max = [](auto x, auto y) { return x < y ? y : x; };
    auto tadd = [](auto x, auto y) { return add(x, y); };
    auto cadd = [](auto x, auto y) { return x + min(y, inf - x); };
    auto qmul = [](auto x, auto y) { return (x = (ull)x * y - (ull)((ld)x / P * y) * P) < 0 ? x + P : x; };
    auto cmod = [](auto x) { return (x %= P) < 0 ? x + P : x; };
    auto abs = [](auto x) { return x < 0 ? -x : x; };
    auto lowb = [](auto x) { return x & (-x); };
    int n, m, dfc, low[MAXN], dfn[MAXN], stk[MAXN], tp;
    vii bccs;
    bitset<MAXN> inq;
#define go(u, i) for (int i = head[u]; i; i = e[i].nxt)
    struct edge
    {
        int v, nxt;
    } e[MAXM << 1];
    int head[MAXN];
    inline void addedge(int u, int v)
    {
        static int edgecnt = 1;
        e[++edgecnt] = {v, head[u]};
        head[u] = edgecnt;
    }
    inline void adde(int u, int v) { addedge(u, v), addedge(v, u); }
    void tarjan(int u, int fr)
    {
        low[u] = dfn[u] = ++dfc, stk[++tp] = u, inq[u] = 1;
        go(u, i) if (fr ^ i && fr ^ i ^ 1)
        {
            int v = e[i].v;
            if (!dfn[v])
                tarjan(v, i), chkmn(low[u], low[v]);
            else if (inq[v])
                chkmn(low[u], dfn[v]);
        }
        if (low[u] == dfn[u])
        {
            vi bcc;
            do bcc.eb(stk[tp]), inq[stk[tp]] = 0;
            while (stk[tp--] ^ u);
            bccs.eb(move(bcc));
        }
    }
    void main()
    {
        cin >> n >> m;
        rep(i, 1, m, u, v) cin >> u >> v, adde(u, v);
        rep(i, 1, n) if (!dfn[i]) tarjan(i, 0);
        cout << SZ(bccs) << endl;
        for (vi &bcc : bccs)
        {
            cout << SZ(bcc) << " ";
            for (int &x : bcc) cout << x << " ";
            cout << endl;
        }
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