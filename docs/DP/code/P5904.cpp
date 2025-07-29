#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int ll
typedef long long ll;
typedef const int cint;
constexpr int MAXN = 1e5 + 10;
int n, dep[MAXN], son[MAXN];
vector<int> e[MAXN];
ll *f[MAXN], *g[MAXN], p[MAXN << 2], *idx = p, ans;
void dfs(cint u, cint fa)
{
    for (cint v : e[u])
        if (v ^ fa)
        {
            dfs(v, u);
            if (dep[v] > dep[son[u]]) son[u] = v;
        }
    dep[u] = dep[son[u]] + 1;
}
void dp(cint u, cint fa)
{
    if (son[u]) f[son[u]] = f[u] + 1, g[son[u]] = g[u] - 1, dp(son[u], u);
    f[u][0] = 1, ans += g[u][0];
    for (cint v : e[u])
        if (v ^ fa && v ^ son[u])
        {
            f[v] = idx, idx += dep[v] << 1, g[v] = idx, idx += dep[v] << 1;
            dp(v, u);
            for (int i = 0; i < dep[v]; i++)
            {
                if (i) ans += f[u][i - 1] * g[v][i];
                ans += g[u][i + 1] * f[v][i];
            }
            for (int i = 0; i < dep[v]; i++)
            {
                g[u][i + 1] += f[u][i + 1] * f[v][i];
                if (i) g[u][i - 1] += g[v][i];
                f[u][i + 1] += f[v][i];
            }
        }
}
signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int u, v, i = 1; i < n; i++) cin >> u >> v, e[u].emplace_back(v), e[v].emplace_back(u);
    dfs(1, 0), f[1] = idx, idx += dep[1] << 1, g[1] = idx, idx += dep[1] << 1, dp(1, 0), cout << ans;
    return 0;
}