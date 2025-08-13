#include <bits/stdc++.h>
using namespace std;
#ifdef ONLINE_JUDGE
#define debug(...)
#else
#define debug(fmt, ...) fprintf(stderr, "Debug at function %s, line %d: " fmt, __func__, __LINE__, ##__VA_ARGS__)
#endif
#define endl '\n'
#define eb emplace_back
#define ep emplace
#define fi first
#define se second
#define rep(i, l, r, ...) for (int i = (l), i##e = (r), ##__VA_ARGS__; i <= i##e; ++i)
#define per(i, r, l, ...) for (int i = (r), i##e = (l), ##__VA_ARGS__; i >= i##e; --i)
#define mst(x, val, len) memset(x, val, sizeof((x)[0]) * (int(len) + 1))
#define mcp(from, to, len) memcpy(to, from, sizeof((to)[0]) * (int(len) + 1))
#define mid (((l) + (r)) >> 1)
#define ls ((x) << 1)
#define rs ((x) << 1 | 1)
#define pbds __gnu_pbds
#define int ll
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
constexpr int MAXN = 1e5 + 10, inf = 1e9, mod = 998244353, MAXV = MAXN << 2;
template <typename T> inline void chkmx(T &a, const T b) { a = a < b ? b : a; }
template <typename T> inline void chkmn(T &a, const T b) { a = a > b ? b : a; }
template <typename T> inline void Add(T &a, const T b) { a = ((a + b) % mod + mod) % mod; }
template <typename T> inline void Mul(T &a, const T b) { a = ((a * b) % mod + mod) % mod; }
template <typename T> inline void add(T &a, const T b) { a = (a + b >= mod ? a + b - mod : a + b); }
template <typename T> inline void mul(T &a, const T b) { a = a * b % mod; }
bool MST;
// q[i] 为可以转移的 k，g[j] 为 f[i - 1][d + j * v[i]] - j * w[i]
int n, m, ans, hd, tl, q[MAXN], f[MAXN], g[MAXN];
bool MED;
signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    debug("Memory Used: %.2lf Mib.\n", (&MST - &MED) / 1024. / 1024.);
    cin >> n >> m;
    rep(i, 1, n, v, w, c)
    {
        cin >> w >> v >> c;
        if (!v)
        {
            ans += w * c;
            continue;
        }
        chkmn(c, m / v);
        rep(d, 0, v - 1)
        {
            hd = 1, tl = 0;
            rep(j, 0, (m - d) / v)
            {
                while (hd <= tl && f[d + j * v] - j * w >= g[tl]) tl--;
                q[++tl] = j, g[tl] = f[d + j * v] - j * w;
                while (hd <= tl && q[hd] < j - c) hd++;
                chkmx(f[d + j * v], g[hd] + j * w);
            }
        }
    }
    cout << ans + f[m];
    return 0;
}