#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const int MAXX = 5e5 + 10, MAXN = 1e5 + 10;
const ll inf = 1e12;
inline void chkmx(int &a, int b) { a = a < b ? b : a; }
inline void chkmn(int &a, int b) { a = a > b ? b : a; }
inline void chkmx(ll &a, ll b) { a = a < b ? b : a; }
inline void chkmn(ll &a, ll b) { a = a > b ? b : a; }
ll a[MAXN], d[MAXN], s[MAXN], f[MAXX], n, mx, mxa, ans = inf;
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i], d[i - 1] = a[i] - a[i - 1], chkmx(mxa, a[i]);
    for (int i = 1; i <= mxa * n; i++)
        f[i] = inf;
    f[0] = s[0] = 0;
    sort(d + 1, d + n);
    for (int i = 1; i <= n; i++)
    {
        s[i] = s[i - 1] + d[i];
        if (!d[i])
            continue;
        for (int j = mx; j >= 0; --j)
        {
            if (f[j] == inf)
                continue;
            chkmn(f[j + i * d[i]], f[j] + 2 * j * d[i] + i * d[i] * d[i]);
            chkmn(f[j + s[i]], f[j] + s[i] * s[i]);
            mx = max(mx, max(j + i * d[i], j + s[i]));
            f[j] = inf;
        }
    }
    for (int i = 0; i <= mx; i++)
        if (f[i] < inf)
            chkmn(ans, n * f[i] - 1ll * i * i);
    cout << ans;
    return 0;
}