#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const int MAXN = 1e6 + 10;
int n, T, m, A, B, C, st[MAXN], ed[MAXN], p[MAXN], q[MAXN], hd[MAXN], tl[MAXN];
ll f[MAXN], x[MAXN], y[MAXN], ans = numeric_limits<ll>::max();
vector<int> V[MAXN], G[MAXN], que[MAXN];
int main()
{
    cin >> n >> m >> A >> B >> C;
    for (int i = 1; i <= m; i++)
        cin >> st[i] >> ed[i] >> p[i] >> q[i], T = max(T, q[i]), G[p[i]].push_back(i);
    for (int i = 1; i <= n; i++)
        hd[i] = 0, tl[i] = -1;
    for (int t = 0; t <= T; t++)
    {
        for (int i : V[t])
        {
            int e = ed[i];
            while (hd[e] < tl[e] && 1ll * (y[que[e][tl[e]]] - y[que[e][tl[e] - 1]]) * (x[i] - x[que[e][tl[e]]]) >= 1ll * (y[i] - y[que[e][tl[e]]]) * (x[que[e][tl[e]]] - x[que[e][tl[e] - 1]]))
                --tl[e];
            if (++tl[e] == que[e].size())
                que[e].push_back(i);
            else
                que[e][tl[e]] = i;
        }
        for (int i : G[t])
        {
            int e = st[i];
            while (hd[e] < tl[e] && (y[que[e][hd[e] + 1]] - y[que[e][hd[e]]]) < 2ll * A * p[i] * (x[que[e][hd[e] + 1]] - x[que[e][hd[e]]]))
                ++hd[e];
            if (hd[e] > tl[e] && st[i] != 1)
                continue;
            int j = st[i] == 1 && hd[e] > tl[e] ? 0 : que[e][hd[e]];
            f[i] = f[j] + 1ll * A * (p[i] - q[j]) * (p[i] - q[j]) + 1ll * B * (p[i] - q[j]) + C;
            x[i] = q[i], y[i] = f[i] + 1ll * A * q[i] * q[i] - 1ll * B * q[i];
            V[q[i]].push_back(i);
            if (ed[i] == n)
                ans = min(ans, f[i] + q[i]);
        }
    }
    cout << ans;
    return 0;
}