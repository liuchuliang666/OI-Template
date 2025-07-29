#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 5e6 + 5;
int n, m, k, mu[N], p[N], v[N], g[2005], f[N], cnt;
int ans;
unordered_map<int, int> ff;
int G(int x) { return x / k * g[k] + g[x % k]; }
void init()
{
    for (int i = 1; i <= k; i++)
        g[i] = g[i - 1] + (__gcd(i, k) == 1);
    mu[1] = f[1] = 1;
    for (int i = 2; i <= N - 5; i++)
    {
        if (!v[i])
        {
            p[++cnt] = i;
            mu[i] = -1;
        }
        for (int j = 1; j <= cnt && i * p[j] <= N - 5; j++)
        {
            v[i * p[j]] = 1;
            if (i % p[j] == 0)
                break;
            else
                mu[i * p[j]] = -mu[i];
        }
        f[i] = f[i - 1] + mu[i] * (G(i) - G(i - 1));
    }
}
int F(int x)
{
    if (x <= N - 5)
        return f[x];
    if (ff[x])
        return ff[x];
    int ans = 1;
    for (int l = 2, r; l <= x; l = r + 1)
    {
        r = x / (x / l);
        ans -= F(x / l) * (G(r) - G(l - 1));
    }
    ff[x] = ans;
    return ans;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> m >> k;
    init();
    for (int l = 1, r; l <= min(n, m); l = r + 1)
    {
        r = min(n / (n / l), m / (m / l));
        ans += (n / l) * G(m / l) * (F(r) - F(l - 1));
    }
    cout << ans;
    return 0;
}