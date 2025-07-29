#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 5e6 + 5;
ll phi[N];
int mu[N];
int pri[N], cnt;
unordered_map<int, ll> sumphi;
unordered_map<int, int> summu;
ll queryphi(ll x)
{
    if (x < 5e6)
        return phi[x];
    if (sumphi[x])
        return sumphi[x];
    ll ans = x * (x + 1) / 2;
    for (ll l = 2, r; l <= x; l = r + 1)
    {
        r = x / (x / l);
        ans -= (r - l + 1) * queryphi(x / l);
    }
    sumphi[x] = ans;
    return ans;
}
ll querymu(ll x)
{
    if (x < 5e6)
        return mu[x];
    if (summu[x])
        return summu[x];
    ll ans = 1;
    for (ll l = 2, r; l <= x; l = r + 1)
    {
        r = x / (x / l);
        ans -= (r - l + 1) * querymu(x / l);
    }
    summu[x] = ans;
    return ans;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    mu[1] = phi[1] = 1;
    for (int i = 2; i < 5e6; i++)
    {
        if (!phi[i])
        {
            pri[++cnt] = i;
            phi[i] = i - 1;
            mu[i] = -1;
        }
        for (int j = 1; i * pri[j] < 5e6 && j <= cnt; j++)
        {
            int m = i * pri[j];
            if (i % pri[j] == 0)
            {
                phi[m] = phi[i] * pri[j];
                mu[m] = 0;
                break;
            }
            phi[m] = phi[i] * phi[pri[j]];
            mu[m] = -mu[i];
        }
    }
    for (int i = 1; i < 5e6; i++)
    {
        phi[i] = phi[i - 1] + phi[i];
        mu[i] = mu[i - 1] + mu[i];
    }
    int t;
    cin >> t;
    while (t--)
    {
        int x;
        cin >> x;
        cout << queryphi(x) << " " << querymu(x) << '\n';
    }
    return 0;
}