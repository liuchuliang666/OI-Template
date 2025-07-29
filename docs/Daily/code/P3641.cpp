#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
extern "C" void MinMax(ll, ll, ll *, ll *);
extern "C" ll findGap(int, int);
namespace subtaskA
{
    const int MAXN = 1e5 + 10;
    ll a[MAXN], ans;
    ll findGap(int n)
    {
        MinMax(0, 1e18, a + 1, a + n);
        for (int l = 2, r = n - 1; l <= r; l++, r--)
            MinMax(a[l - 1] + 1, a[r + 1] - 1, a + l, a + r);
        for (int i = 1; i < n; i++)
            ans = max(ans, a[i + 1] - a[i]);
        return ans;
    }
} // namespace subtaskA
namespace subtaskB
{
    ll L, R, mn, mx, len, block, lst, ans;
    ll findGap(int n)
    {
        MinMax(0, 1e18, &L, &R);
        len = (R - L + 1);
        block = len / (n - 1);
        if (len % (n - 1))
            block++;
        lst = L;
        for (ll l = L + 1; l < R; l += block)
        {
            ll r = min(l + block - 1, R - 1);
            MinMax(l, r, &mn, &mx);
            ans = max(ans, mn - lst);
            if (mx > 0)
                lst = mx;
        }
        ans = max(ans, R - lst);
        return ans;
    }
} // namespace subtaskB
ll findGap(int T, int n)
{
    if (T == 1)
        return subtaskA::findGap(n);
    else
        return subtaskB::findGap(n);
}