#include <bits/stdc++.h>
using namespace std;
int n, m, q, a[200005], l[505], r[505], to[200005], flag1[200005], flag2[200005], now, ans[200005];
struct node
{
    int l, r, id;
} b[200005];
void init()
{
    m = sqrt(n);
    for (int i = 1; i <= m; i++)
    {
        l[i] = r[i - 1] + 1;
        r[i] = l[i] + m - 1;
    }
    if (r[m] < n)
    {
        m++;
        l[m] = r[m - 1] + 1;
        r[m] = n;
    }
    for (int i = 1; i <= m; i++)
        for (int j = l[i]; j <= r[i]; j++)
            to[j] = i;
}
bool cmp(node i, node j)
{
    if (to[i.l] == to[j.l])
        return i.r > j.r;
    return to[i.l] < to[j.l];
}
int main(void)
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= q; i++)
    {
        scanf("%d%d", &b[i].l, &b[i].r);
        b[i].id = i;
    }
    init();
    sort(b + 1, b + 1 + q, cmp);
    int x = 0, y = 0;
    // 这里也可以用上一题的写法，懒得改了QwQ
    for (int i = 1; i <= q; i++)
    {
        // 在同一块内暴力算
        if (to[b[i].l] == to[b[i].r])
        {
            for (int j = b[i].l; j <= b[i].r; j++)
                flag2[a[j]] = 1;
            ans[b[i].id] = n;
            if (!flag2[0])
                ans[b[i].id] = 0;
            for (int j = b[i].l; j <= b[i].r; j++)
                if (!flag2[a[j] + 1])
                    ans[b[i].id] = min(ans[b[i].id], a[j] + 1);
            // 复原
            for (int j = b[i].l; j <= b[i].r; j++)
                flag2[a[j]] = 0;
            continue;
        }
        // 如果这次询问和上次不在一组
        if (to[b[i].l] != to[x])
        {
            for (int j = l[to[x]]; j <= y; j++)
                flag1[a[j]] = 0;
            now = n;
            for (int j = l[to[b[i].l]]; j <= b[i].r; j++)
                flag1[a[j]]++;
            // 暴力算mex
            for (int j = 0; j < n; j++)
                if (!flag1[j])
                {
                    now = j;
                    break;
                }
            x = b[i].l;
            y = b[i].r;
        }
        // 减右边的
        for (int j = y; j > b[i].r; j--)
        {
            flag1[a[j]]--;
            if (!flag1[a[j]])
                now = min(now, a[j]);
        }
        ans[b[i].id] = now;
        // 减左边的
        for (int j = l[to[b[i].l]]; j < b[i].l; j++)
        {
            flag1[a[j]]--;
            if (!flag1[a[j]])
                ans[b[i].id] = min(ans[b[i].id], a[j]);
        }
        // 复原
        for (int j = l[to[b[i].l]]; j < b[i].l; j++)
            flag1[a[j]]++;
        x = b[i].l;
        y = b[i].r;
    }
    for (int i = 1; i <= q; i++)
        printf("%d\n", ans[i]);
    return 0;
}