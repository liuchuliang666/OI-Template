#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int ll
typedef long long ll;
typedef const int cint;
constexpr int MAXN = 1e6 + 10;
int n, buf[MAXN], *now = buf, *f[MAXN], *g[MAXN], dep[MAXN], son[MAXN], ans[MAXN];
vector<int> e[MAXN];
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
    f[u][0] = 1;
    if (son[u]) f[son[u]] = f[u] + 1, dp(son[u], u), ans[u] = ans[son[u]] + 1;
    for (cint v : e[u])
        if (v ^ fa && v ^ son[u])
        {
            f[v] = now, now += dep[v];
            dp(v, u);
            for (int i = 1; i <= dep[v]; i++)
            {
                f[u][i] += f[v][i - 1];
                if (f[u][i] > f[u][ans[u]] || (f[u][i] == f[u][ans[u]] && i < ans[u])) ans[u] = i;
            }
        }
    if (f[u][ans[u]] == 1) ans[u] = 0;
}
signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int u, v, i = 1; i < n; i++) cin >> u >> v, e[u].emplace_back(v), e[v].emplace_back(u);
    dfs(1, 0), f[1] = now, now += dep[1], dp(1, 0);
    for (int i = 1; i <= n; i++) cout << ans[i] << endl;
    return 0;
}