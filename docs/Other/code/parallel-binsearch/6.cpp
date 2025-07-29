int a[500005], ans[500005]; // a:原序列 ans:构造的序列
void overall_binary(int l, int r, int ql, int qr)
{
    if (ql > qr) return;
    if (l == r)
    {
        for (int i = ql; i <= qr; i++) ans[i] = l;
        return;
    }
    int cnt = 0, mid = l + ((r - l) >> 1); // 默认开始都填 mid+1 全部划分到右区间
    long long res = 0ll, sum = 0ll;
    for (int i = ql; i <= qr; i++) sum += abs(a[i] - (mid + 1));
    res = sum;
    for (int i = ql; i <= qr; i++)
    { // 尝试把 [ql,i] 从 mid+1 换成 mid 并且划分到左区间
        sum -= abs(a[i] - (mid + 1));
        sum += abs(a[i] - mid);
        if (sum < res) cnt = i - ql + 1, res = sum; // 发现 [ql,i] 取 mid 更优,更新
    }
    overall_binary(l, mid, ql, ql + cnt - 1), overall_binary(mid + 1, r, ql + cnt, qr);
}