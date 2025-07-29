#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const int MAXN = 2e6 + 10;
ll n, m, ans[MAXN], M;
int ops[MAXN];
struct BIT
{
    int lowbit(const int x) { return x & (-x); }
    ll tr[MAXN];
    void add(int x, ll v)
    {
        for (x++; x <= n + 1; x += lowbit(x)) tr[x] += v;
    }
    void del(int x)
    {
        for (x++; x <= n + 1; x += lowbit(x)) tr[x] = 0;
    }
    ll qry(int x)
    {
        ll res = 0;
        for (x++; x; x -= lowbit(x)) res += tr[x];
        return res;
    }
} bit;
struct node
{
    // opt == 0: add a, opt == 1 or -1: ans[tim] += qry * opt
    ll opt, tim, x, y, a;
} a[MAXN];
void solve(int l, int r) // solve tim in [l, r] and sort array a[] by x
{
    if (l == r) return;
    int mid = (l + r) >> 1;
    solve(l, mid), solve(mid + 1, r);
    int i = l, j = mid + 1, k = l;
    while (i <= mid && j <= r)
    {
        if (a[i].x <= a[j].x)
        {
            if (!a[i].opt) bit.add(a[i].y, a[i].a);
            i++;
        }
        else
        {
            if (a[j].opt) ans[a[j].tim] += a[j].opt * bit.qry(a[j].y);
            j++;
        }
    }
    while (j <= r)
    {
        if (a[j].opt) ans[a[j].tim] += a[j].opt * bit.qry(a[j].y);
        j++;
    }
    for (int t = l; t < i; t++)
        if (!a[t].opt) bit.del(a[t].y);
    inplace_merge(a + l, a + mid + 1, a + r + 1,
                  [](node p, node q)
                  { return p.x <= q.x; });
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> n;
    for (ll &i = M = 1, x1, y1, x2, y2, x, y, v, opt;; i++)
    {
        cin >> opt;
        ops[i] = opt;
        if (opt == 3)
        {
            i--;
            break;
        }
        switch (opt)
        {
        case 1:
            cin >> x >> y >> v;
            a[++m] = {0, i, x, y, v};
            break;
        case 2:
            cin >> x1 >> y1 >> x2 >> y2;
            a[++m] = {1, i, x1 - 1, y1 - 1, 0};
            a[++m] = {1, i, x2, y2, 0};
            a[++m] = {-1, i, x1 - 1, y2, 0};
            a[++m] = {-1, i, x2, y1 - 1, 0};
            break;
        }
    }
    solve(1, m);
    for (int i = 1; i <= M; i++)
        if (ops[i] == 2) cout << ans[i] << endl;
    return 0;
}