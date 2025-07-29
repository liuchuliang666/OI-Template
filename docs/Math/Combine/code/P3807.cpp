#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1e5 + 10;
ll frac[MAXN], p;
ll qpow(ll a, ll b)
{
    ll res = 1;
    for (; b; b >>= 1, a = a * a % p)
        if (b & 1)
            res = res * a % p;
    return res;
}
ll c(ll n, ll m)
{
    if (m > n)
        return 0;
    return frac[n] * qpow(frac[n - m], p - 2) % p * qpow(frac[m], p - 2) % p;
}
ll lucas(ll n, ll m)
{
    if (!m)
        return 1;
    return lucas(n / p, m / p) * c(n % p, m % p) % p;
}
ll solve()
{
    ll n, m;
    cin >> n >> m >> p;
    n += m;
    for (int i = 1; i <= p; i++)
        frac[i] = frac[i - 1] * i % p;
    return lucas(n, m);
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    frac[0] = 1;
    int T;
    cin >> T;
    while (T--)
        cout << solve() << endl;
    return 0;
}