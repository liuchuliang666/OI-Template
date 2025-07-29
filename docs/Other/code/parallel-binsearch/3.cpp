#include <algorithm>
#include <iostream>
using namespace std;
constexpr int N = 200020;
int n, m;
int ans[N];
// BIT begin
int t[N];
int a[N];
int lowbit(const int x) { return x & (-x); }
int sum(int x)
{
    static int res;
    for (res = 0; x; x -= lowbit(x)) res += t[x];
    return res;
}
void add(int x, int v)
{
    for (; x <= n; x += lowbit(x)) t[x] += v;
}
// BIT end
int tot = 0;
struct Query
{
    int l, r, k, id, type; // set values to -1 when they are not used!
} q[N * 2], q1[N * 2], q2[N * 2];
void solve(int l, int r, int ql, int qr)
{
    if (ql > qr) return;
    if (l == r)
    {
        for (int i = ql; i <= qr; i++)
            if (q[i].type == 2) ans[q[i].id] = l;
        return;
    }
    int mid = (l + r) >> 1, cnt1 = 0, cnt2 = 0;
    for (int i = ql; i <= qr; i++)
    {
        if (q[i].type == 1)
        {
            if (q[i].l <= mid)
                add(q[i].id, 1), q1[++cnt1] = q[i];
            else
                q2[++cnt2] = q[i];
        }
        else
        {
            int x = sum(q[i].r) - sum(q[i].l - 1);
            if (q[i].k <= x)
                q1[++cnt1] = q[i];
            else
                q[i].k -= x, q2[++cnt2] = q[i];
        }
    }
    // rollback changes
    for (int i = 1; i <= cnt1; i++)
        if (q1[i].type == 1) add(q1[i].id, -1);
    // move them to the main array
    copy(q1 + 1, q1 + cnt1 + 1, q + ql), copy(q2 + 1, q2 + cnt2 + 1, q + ql + cnt1);
    solve(l, mid, ql, cnt1 + ql - 1), solve(mid + 1, r, cnt1 + ql, qr);
}
pair<int, int> b[N];
int toRaw[N];
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    // read and discrete input data
    for (int x, i = 1; i <= n; i++) cin >> x, b[i] = {x, i};
    sort(b + 1, b + n + 1);
    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        if (b[i].first != b[i - 1].first) cnt++;
        a[b[i].second] = cnt;
        toRaw[cnt] = b[i].first;
    }
    for (int i = 1; i <= n; i++) q[++tot] = {a[i], -1, -1, i, 1};
    for (int l, r, k, i = 1; i <= m; i++) cin >> l >> r >> k, q[++tot] = {l, r, k, i, 2};
    solve(0, cnt + 1, 1, tot);
    for (int i = 1; i <= m; i++) cout << toRaw[ans[i]] << '\n';
}
