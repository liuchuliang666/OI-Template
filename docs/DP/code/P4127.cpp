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
int num[20], len, f[20][170][170], tar;
int dp(int d, bool up, int sum, int now)
{
    if (sum > tar || sum + (len - d + 1) * 9 < tar) return 0; // 小剪枝，这也是记忆化搜索的一个优点。
    if (d == len + 1) return tar == sum && !now;
    if (!up && ~f[d][sum][now]) return f[d][sum][now];
    int res = 0, lim = up ? num[d] : 9;
    rep(i, 0, lim) res += dp(d + 1, up && i == lim, sum + i, (now * 10 + i) % tar);
    if (up) return res;
    return f[d][sum][now] = res;
}
bool chk(string s)
{
    int num = 0, sum = 0;
    for (char c : s) c -= '0', num = num * 10 + c, sum += c;
    return num % sum == 0;
}
int solve(const string &s)
{
    Mst(f, -1), len = 0;
    for (char c : s) num[++len] = c - '0';
    return dp(1, 1, 0, 0);
}
int calc(const string &sl, const string &sr, int x)
{
    tar = x;
    return solve(sr) - solve(sl);
}
void Solve()
{
    string sl, sr;
    cin >> sl >> sr;
    int ans = chk(sl);
    rep(i, 1, 162) ans += calc(sl, sr, i);
    cout << ans;
}
signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--) Solve();
    return 0;
}