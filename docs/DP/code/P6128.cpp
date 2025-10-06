#include <bits/stdc++.h>
using namespace std;
#ifdef ONLINE_JUDGE
#define debug(...) (0)
struct __CERR
{
    template <typename T> __CERR &operator<<(const T &x) { return *this; }
} __cerr;
#define cerr __cerr
#define endl '\n'
#else
#define debug(...) fprintf(stderr, ##__VA_ARGS__)
#endif
#ifdef CPH
#define openfile(x)
#define endl '\n'
#else
#define openfile(x) (freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout))
#endif
#define eb emplace_back
#define ep emplace
#define pb push_back
#define pp push
#define ins insert
#define fi first
#define se second
#define SZ(x) int((x).size())
#define ALL(x) (x).begin(), (x).end()
#define rep(i, l, r, ...) for (int i = int(l), ##__VA_ARGS__; i <= int(r); ++i)
#define per(i, r, l, ...) for (int i = int(r), ##__VA_ARGS__; i >= int(l); --i)
#define Rep(i, l, r, ...) for (int i = int(l), i##e = int(r), ##__VA_ARGS__; i <= i##e; ++i)
#define Per(i, r, l, ...) for (int i = int(r), i##e = int(l), ##__VA_ARGS__; i >= i##e; --i)
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
#define ls ((x) << 1)
#define rs ((x) << 1 | 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r
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
mt19937 rnd(random_device{}());
constexpr int MAXN = 2e5 + 10, inf = (sizeof(int) == 4 ? 1e9 : 1e15), P = 998244353, MAXV = MAXN << 2;
int len, f[36][36][36], num[36];
int dp(int d, bool up, bool lead, int zero, int one)
{
    if (zero + len - d + 1 < one) return 0;
    if (d == len + 1) return zero >= one;
    if (!up && !lead && ~f[d][zero][one]) return f[d][zero][one];
    int lim = up ? num[d] : 1, res = 0;
    res += dp(d + 1, up && !lim, lead, lead ? 0 : zero + 1, one);
    if (lim) res += dp(d + 1, up && lim, 0, zero, one + 1);
    if (up || lead) return res;
    return f[d][zero][one] = res;
}
int solve(int x)
{
    len = 0;
    while (x) num[++len] = x & 1, x >>= 1;
    reverse(num + 1, num + 1 + len);
    Mst(f, -1);
    return dp(1, 1, 1, 0, 0);
}
void Solve()
{
    int l, r;
    cin >> l >> r;
    cout << solve(r) - solve(l - 1);
}
signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--) Solve();
    return 0;
}