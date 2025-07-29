#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int ll
#define mst(u, val) memset(u, val, sizeof(u))
#define mcp(from, to) memcpy(to, from, sizeof(to))
typedef long long ll;
typedef const int cint;
constexpr int MAXN = 1e3 + 10, mod = 1e9 + 7;
template <typename T> inline void chkmx(T &a, const T b) { a = a < b ? b : a; }
template <typename T> inline void chkmn(T &a, const T b) { a = a > b ? b : a; }
template <typename T> inline void add(T &a, const T b) { a = ((a + b) % mod + mod) % mod; }
template <typename T> inline void mul(T &a, const T b) { a = ((a * b) % mod + mod) % mod; }
vector<int> e[MAXN];
int n, k, f[MAXN][MAXN * 5][6], g[MAXN * 5][6], siz[MAXN];
void dfs(cint u, cint fa)
{
    siz[u] = 1;
    for (int i = 1; i <= k; i++) f[u][0][i] = 1;
    for (cint v : e[u])
        if (v ^ fa)
        {
            dfs(v, u), mst(g, 0);
            for (int i = 0; i <= k * siz[u]; i++)
                for (int j = 0; j <= k; j++)
                    if (f[u][i][j])
                        for (int p = 0; p <= k * siz[v]; p++)
                            for (int q = 0; q <= k; q++)
                                if (f[v][p][q])
                                    add(g[i + p + q][max(i + j + p, i + p + q) - (i + p + q)], f[u][i][j] * f[v][p][q]);
            mcp(g, f[u]), add(siz[u], siz[v]);
        }
}
signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> k;
    for (int u, v, i = 1; i < n; i++) cin >> u >> v, e[u].emplace_back(v), e[v].emplace_back(u);
    dfs(1, 0);
    for (int i = 1; i <= k * n; i++)
    {
        int ans = 0;
        for (int j = 0; j <= min(i, k); j++) add(ans, f[1][i - j][j]);
        cout << ans << endl;
    }
    return 0;
}