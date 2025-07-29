#include <bits/stdc++.h>
using namespace std;
#define N 200005
int n, m, q, a[N], tot, top, ans[N];
// 一个块的左端点、右端点和某点所在块
int l[505], r[505], to[N];
// 界线右边区间对应数的最小、最大下标 和界线左边区间对应数的最小、最大下标
int l1[N], r1[N], l2[N], r2[N];
// 当前界限右边的答案和总区间的答案
int now;
pair<int, int> p[N];
struct node
{
    int l, r, id;
} st[N];
vector<node> b[505];
// 求l、r和to
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
    return i.r < j.r;
}
int main(void)
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        p[i] = {a[i], i};
    }
    // 离散化
    sort(p + 1, p + 1 + n);
    for (int i = 1; i <= n; i++)
    {
        if (p[i].first != p[i - 1].first)
            tot++;
        a[p[i].second] = tot;
    }
    init();
    scanf("%d", &q);
    for (int i = 1; i <= q; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        b[to[x]].push_back({x, y, i});
    }
    for (int i = 1; i <= m; i++)
        sort(b[i].begin(), b[i].end(), cmp);
    // 如果像普通莫队那样直接遍历整个q每次都需要判断是否在新的组内，比较麻烦
    // 可为每组开一个vector，对其分开计算
    for (int i = 1; i <= m; i++)
    {
        int len = b[i].size();
        if (!len)
            continue;
        // 这里的l1得赋较大值，否则后面求min(l1,l2)时会算错
        memset(l1, 0x3f, sizeof(l1));
        memset(r1, 0, sizeof(r1));
        int x = r[to[b[i][0].l]] + 1, y = x - 1;
        now = 0;
        for (int j = 0; j < len; j++)
        {
            // 在同一块内暴力算
            if (to[b[i][j].l] == to[b[i][j].r])
            {
                for (int k = b[i][j].l; k <= b[i][j].r; k++)
                {
                    if (!l2[a[k]])
                        l2[a[k]] = k;
                    r2[a[k]] = k;
                    ans[b[i][j].id] = max(ans[b[i][j].id], r2[a[k]] - l2[a[k]]);
                }
                // 复原时不能memset
                for (int k = b[i][j].l; k <= b[i][j].r; k++)
                    l2[a[k]] = r2[a[k]] = 0;
                continue;
            }
            // 算界线右边的
            for (int k = y + 1; k <= b[i][j].r; k++)
            {
                if (l1[a[k]] == l1[0])
                    l1[a[k]] = k;
                r1[a[k]] = k;
                now = max(now, r1[a[k]] - l1[a[k]]);
            }
            ans[b[i][j].id] = now;
            top = 0;
            // 算界线左边的
            for (int k = x - 1; k >= b[i][j].l; k--)
            {
                l2[a[k]] = k;
                if (!r2[a[k]])
                    r2[a[k]] = k;
                ans[b[i][j].id] = max(ans[b[i][j].id], max(r1[a[k]], r2[a[k]]) - min(l1[a[k]], l2[a[k]]));
            }
            // 复原
            for (int k = x - 1; k >= b[i][j].l; k--)
                l2[a[k]] = r2[a[k]] = 0;
            // 右指针向右跳
            y = b[i][j].r;
        }
    }
    for (int i = 1; i <= q; i++)
        printf("%d\n", ans[i]);
    return 0;
}