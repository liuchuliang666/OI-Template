#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
typedef long double ld;
const int MAXN = 1e5 + 10;
int n, m, g[MAXN], q[MAXN], hd, tl;
ll f[MAXN], s[MAXN], ans;
#define X(i) ld(s[i])
#define Y(i) ld(f[i] + s[i] * s[i])
#define K(i) ld((s[i] + 1) * 2)
ld slope(const int i, const int j) { return (Y(i) - Y(j)) / (X(i) - X(j)); }
void dp(ll dta) // add dta to each cost
{
    q[hd = tl = 0] = g[0] = 0, memset(f, 0, sizeof(f));
    for (int i = 1; i <= n; i++)
    {
        while (hd < tl && slope(q[hd], q[hd + 1]) < K(i)) hd++;
        f[i] = f[q[hd]] + (s[i] - s[q[hd]] + 1) * (s[i] - s[q[hd]] + 1) + dta, g[i] = g[q[hd]] + 1;
        while (hd < tl && slope(q[tl - 1], q[tl]) > slope(q[tl], i)) tl--;
        q[++tl] = i;
    }
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> s[i], s[i] += s[i - 1];
    ll l = 0, r = 1e16, mid;
    while (l <= r)
    {
        dp(mid = (l + r) >> 1);
        if (g[n] <= m)
            ans = f[n] - mid * m, r = mid - 1;
        else
            l = mid + 1;
    }
    cout << ans;
    return 0;
}