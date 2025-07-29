#include <bits/stdc++.h>
using namespace std;
#define N 50005
int n, m, k, a[N], cnt[N], ans[N];
struct node
{
    int l, r, id;
} q[N];
int cmp(node x, node y)
{
    if (x.l / 250 == y.l / 250)
        return x.r < y.r;
    return x.l / 250 < y.l / 250;
}
int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &q[i].l, &q[i].r);
        q[i].id = i;
    }
    sort(q + 1, q + 1 + m, cmp);
    int l = 1, r = 0, now = 0;
    for (int i = 1; i <= m; i++)
    {
        for (int j = l; j < q[i].l; j++)
        {
            now += cnt[a[j]] * -2 + 1;
            cnt[a[j]]--;
        }
        for (int j = q[i].l; j < l; j++)
        {
            now += cnt[a[j]] * 2 + 1;
            cnt[a[j]]++;
        }
        for (int j = q[i].r + 1; j <= r; j++)
        {
            now += cnt[a[j]] * -2 + 1;
            cnt[a[j]]--;
        }
        for (int j = r + 1; j <= q[i].r; j++)
        {
            now += cnt[a[j]] * 2 + 1;
            cnt[a[j]]++;
        }
        l = q[i].l;
        r = q[i].r;
        ans[q[i].id] = now;
    }
    for (int i = 1; i <= m; i++)
        printf("%d\n", ans[i]);
    return 0;
}