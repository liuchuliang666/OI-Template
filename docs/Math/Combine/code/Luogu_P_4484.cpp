#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll N = 30, p = 998244353;
ll n, ans;
ll cnt, a[N];
ll qpow(ll n, ll k)
{
    ll ans = 1;
    while (k)
    {
        if (k & 1) ans = ans * n % p;
        n = n * n % p;
        k >>= 1;
    }
    return ans;
}
ll fac(ll x)
{
    ll res = 1;
    for (int i = 2; i <= x; i++) res = res * i % p;
    return res;
}
ll calc()
//      n!
//--------------
// x1*x2*x3...*xn
{
    ll res = 1;
    for (int i = 1; i <= cnt; i++)
        for (int j = 1; j <= a[i]; j++)
        {
            ll now = a[i] - j + 1; // 这一行这个格子及右侧格子数
            ll tt = i;
            while (tt < cnt && a[tt + 1] >= j) tt++; // tt-i为这个格子下方格子数
            res = res * (tt - i + now) % p;
        }
    return fac(n) * qpow(res, p - 2) % p;
}
void dfs(ll x, ll last) // 求整数划分
{
    if (x < 0) return;
    if (x == 0)
    {
        ll val = calc();
        ans += val * val % p * a[1] % p;
        ans %= p;
        return;
    }
    for (int i = last; i >= 1; i--) // 每一行格子数都不大于上一行
    {
        a[++cnt] = i;
        dfs(x - i, i);
        cnt--;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n;
    dfs(n, n);
    cout << ans * qpow(fac(n), p - 2) % p;
}