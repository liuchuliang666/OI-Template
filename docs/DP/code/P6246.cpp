#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const int MAXN = 5e5 + 10;
struct Opt
{
    int r, opt;
} q[MAXN];
int n, g[MAXN], hd, tl, m;
ll f[MAXN], s[MAXN];
inline ll getw(const int l, const int r) { return (s[r] - s[((l + r + 1) >> 1) - 1]) - (s[(l + r) >> 1] - s[l - 1]); }
inline ll calc(const int i, const int j) { return f[j] + getw(j + 1, i); }
inline int bound(int pos, int nopt)
{
    auto [r, opt] = q[pos];
    int l = q[pos - 1].r + 1, mid, res;
    while (l <= r)
    {
        mid = l + r >> 1;
        if (calc(mid, nopt) <= calc(mid, opt))
            res = mid, r = mid - 1;
        else
            l = mid + 1;
    }
    return res;
}
inline void getdp(ll dta)
{
    q[hd = tl = 1] = {n, 0}, g[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        while (q[hd].r < i) hd++;
        f[i] = calc(i, q[hd].opt) + dta, g[i] = g[q[hd].opt] + 1;
        int pos = n + 1;
        while (hd <= tl && calc(q[tl].r, i) <= calc(q[tl].r, q[tl].opt))
        {
            if (calc(q[tl - 1].r + 1, q[tl].opt) < calc(q[tl - 1].r + 1, i))
                pos = bound(tl, i), q[tl].r = pos - 1;
            else
                pos = q[--tl].r + 1;
        }
        if (pos <= n) q[++tl] = {n, i};
    }
}
ll wqs()
{
    ll l = -1e12, r = 1e12, mid, ans;
    while (l <= r)
    {
        getdp(mid = l + r >> 1);
        if (g[n] < m)
            r = mid - 1;
        else
            ans = f[n] - mid * m, l = mid + 1;
    }
    return ans;
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> s[i], s[i] += s[i - 1];
    cout << wqs();
    return 0;
}