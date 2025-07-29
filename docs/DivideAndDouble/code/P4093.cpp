#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 10, inf = 0x7fffffff, MAXV = 1e5 + 10;
struct node
{
    int mx, mn, val, pos;
} a[MAXN];
namespace bit
{
    int tr[MAXV];
    inline int lowbit(int x) { return x & (-x); }
    inline void update(int x, int val)
    {
        while (x <= 1e5)
        {
            tr[x] = max(tr[x], val);
            x += lowbit(x);
        }
    }
    inline int query(int x)
    {
        int res = 0;
        while (x)
        {
            res = max(res, tr[x]);
            x -= lowbit(x);
        }
        return res;
    }
    inline void clear(int x)
    {
        while (x <= 1e5)
        {
            tr[x] = 0;
            x += lowbit(x);
        }
    }
} // namespace bit
int dp[MAXN], n, m, ans;
void cdq(int l, int r)
{
    if (l >= r)
    {
        dp[l] = max(dp[l], 1);
        return;
    }
    int mid = (l + r) >> 1;
    sort(a + l, a + r + 1, [](node p, node q)
         { return p.pos < q.pos; });
    cdq(l, mid);
    sort(a + l, a + mid + 1, [](node p, node q)
         { return p.mx < q.mx; });
    sort(a + mid + 1, a + r + 1, [](node p, node q)
         { return p.val < q.val; });
    int i = l, j;
    // a[i].mx <= a[j].val && a[i].val <= a[j].mn
    for (j = mid + 1; j <= r; j++)
    {
        while (a[i].mx <= a[j].val && i <= mid)
        {
            bit::update(a[i].val, dp[a[i].pos]);
            i++;
        }
        dp[a[j].pos] = max(dp[a[j].pos], bit::query(a[j].mn) + 1);
    }
    while (i >= l)
        bit::clear(a[i--].val);
    cdq(mid + 1, r);
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i].val, a[i].mx = a[i].mn = a[i].val, a[i].pos = i;
    while (m--)
    {
        int x, y;
        cin >> x >> y;
        a[x].mn = min(a[x].mn, y);
        a[x].mx = max(a[x].mx, y);
    }
    cdq(1, n);
    for (int i = 1; i <= n; i++)
        ans = max(ans, dp[i]);
    cout << ans;
    return 0;
}