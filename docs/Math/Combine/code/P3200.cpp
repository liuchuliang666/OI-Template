#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e6 + 5;
int mp[N], pri[N], cnt[N], mod, num, n;
int qpow(int n, int k)
{
    int ans = 1;
    while (k)
    {
        if (k & 1) ans = ans * n % mod;
        n = n * n % mod;
        k >>= 1;
    }
    return ans;
}
signed main()
{
    cin >> n >> mod;
    for (int i = 2; i <= 2 * n; i++)
    {
        if (!mp[i])
        {
            pri[++num] = i;
            mp[i] = i;
        }
        for (int j = 1; j <= num && i * pri[j] <= 2 * n; j++)
        {
            mp[i * pri[j]] = pri[j];
            if (i % pri[j] == 0) break;
        }
    }
    for (int i = 1; i <= n; i++) cnt[i] = -1;
    for (int i = n + 2; i <= 2 * n; i++) cnt[i] = 1;
    for (int i = 2 * n; i > 1; i--)
        if (mp[i] < i)
        {
            cnt[mp[i]] += cnt[i];
            cnt[i / mp[i]] += cnt[i];
        }
    int ans = 1;
    for (int i = 2; i <= 2 * n; i++)
        if (mp[i] == i) ans = ans * qpow(i, cnt[i]) % mod;
    cout << ans;
    return 0;
}