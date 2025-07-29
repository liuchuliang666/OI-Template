struct Query
{
    int i, l, r, k;
}; // 第 i 次询问查询区间 [l,r] 的第 k 小值
Query s[200005], t1[200005], t2[200005];
int n, m, cnt, pos, p[200005], ans[200005];
pair<int, int> a[200005];
void add(int x, int y); // 树状数组 位置 x 加 y
int sum(int x);         // 树状数组 [1,x] 前缀和
// 当前处理的询问为 [ql,qr], 答案值域为 [l,r]
void overall_binary(int l, int r, int ql, int qr)
{
    if (ql > qr) return;
    if (l == r)
    {
        for (int i = ql; i <= qr; i++) ans[s[i].i] = l;
        return;
    }
    int cnt1 = 0, cnt2 = 0, mid = (l + r) >> 1;
    // 追踪分治中心,认为 [1,pos] 的值已经载入树状数组
    while (pos <= n - 1 && a[pos + 1].first <= mid) add(a[pos + 1].second, 1), ++pos;
    while (pos >= 1 && a[pos].first > mid) add(a[pos].second, -1), --pos;
    for (int i = ql; i <= qr; i++)
    {
        int now = sum(s[i].r) - sum(s[i].l - 1);
        if (s[i].k <= now)
            t1[++cnt1] = s[i];
        else
            t2[++cnt2] = s[i]; // 注意 不应修改询问信息
    }
    copy(t1 + 1, t1 + cnt1 + 1, s + ql);
    copy(t2 + 1, t2 + cnt2 + 1, s + ql + cnt1);
    overall_binary(l, mid, ql, ql + cnt1 - 1);
    overall_binary(mid + 1, r, ql + cnt1, qr);
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i].first);
        a[i].second = i;
        p[++cnt] = a[i].first;
    }
    sort(a + 1, a + n + 1); // 对序列排序 离散化
    sort(p + 1, p + n + 1);
    cnt = unique(p + 1, p + n + 1) - p - 1;
    for (int i = 1; i <= n; i++) a[i].first = lower_bound(p + 1, p + cnt + 1, a[i].first) - p;
    // 省略读入询问
    overall_binary(1, m, 1, cnt);
    for (int i = 1; i <= n; i++) printf("%d\n", p[ans[i]]);
    return 0;
}