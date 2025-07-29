#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2005;
const double inf = 0x3f3f3f3f;
struct node
{
    int v, w;
};
int c[N], d[N];
double p[N], f[N][N][2];
int mp[N][N];
signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, m, num, e;
    cin >> n >> m >> num >> e;
    for (int i = 1; i <= n; i++)
        cin >> c[i];
    for (int i = 1; i <= n; i++)
        cin >> d[i];
    for (int i = 1; i <= n; i++)
        cin >> p[i];
    for (int i = 1; i <= num; i++)
        for (int j = 1; j < i; j++)
            mp[i][j] = mp[j][i] = inf;
    for (int i = 1; i <= e; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        mp[u][v] = mp[v][u] = min(mp[u][v], w);
    }
    for (int k = 1; k <= num; k++)
        for (int i = 1; i <= num; i++)
            for (int j = 1; j <= num; j++)
                mp[i][j] = min(mp[i][j], mp[i][k] + mp[k][j]);
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= m; j++)
            f[i][j][0] = f[i][j][1] = inf;
    f[1][0][0] = f[1][1][1] = 0;
    for (int i = 2; i <= n; i++)
    {
        f[i][0][0] = f[i - 1][0][0] + mp[c[i - 1]][c[i]];
        for (int j = 1; j <= min(m, i); j++)
        {
            f[i][j][0] = min(f[i - 1][j][0] + mp[c[i - 1]][c[i]],
                             f[i - 1][j][1] + mp[c[i - 1]][c[i]] * (1 - p[i - 1]) + mp[d[i - 1]][c[i]] * p[i - 1]);
            f[i][j][1] = min(f[i - 1][j - 1][0] + mp[c[i - 1]][c[i]] * (1 - p[i]) + mp[c[i - 1]][d[i]] * p[i],
                             f[i - 1][j - 1][1] + mp[d[i - 1]][d[i]] * p[i] * p[i - 1] + mp[d[i - 1]][c[i]] * p[i - 1] * (1 - p[i]) + mp[c[i - 1]][d[i]] * (1 - p[i - 1]) * p[i] + mp[c[i - 1]][c[i]] * (1 - p[i - 1]) * (1 - p[i]));
        }
    }
    double ans = inf;
    for (int i = 0; i <= m; i++)
        ans = min(ans, min(f[n][i][0], f[n][i][1]));
    cout << fixed << setprecision(2) << ans;
    return 0;
}