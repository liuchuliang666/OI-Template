#include <bits/stdc++.h>
using namespace std;
#define int ll
typedef long long ll;
typedef double db;
constexpr int MAXN = 1e5 + 10;
struct node
{
    int v, c;
    db val;
} a[MAXN];
bool cmp(node x, node y) { return x.val < y.val; }
int n, m;
db check(db num)
{
    for (int i = 1; i <= n; i++) a[i].val = num * a[i].c - 1.0 * a[i].v;
    sort(a + 1, a + 1 + n, cmp);
    db now = 0;
    for (int i = 1; i <= m; i++) now += a[i].val;
    return now;
}
signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i].v;
    for (int i = 1; i <= n; i++) cin >> a[i].c;
    db l = 0, r = 2000, ans = 0;
    while (r - l >= 1e-5)
    {
        db mid = (l + r) / 2.0, num = check(mid);
        if (num < 0)
            l = mid;
        else
            ans = mid, r = mid;
    }
    cout << fixed << setprecision(3) << ans;
    return 0;
}