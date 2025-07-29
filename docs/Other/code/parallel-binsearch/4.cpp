struct Opt
{
    int x, y, k, type, id;
    // 对于询问, type = 1, x, y 表示区间左右边界, k 表示询问第 k 小
    // 对于修改, type = 0, x 表示修改位置, y 表示修改后的值,
    // k 表示当前操作是插入(1)还是擦除(-1), 更新树状数组时使用.
    // id 记录每个操作原先的编号, 因二分过程中操作顺序会被打散
};
Opt q[N], q1[N], q2[N];
// q 为所有操作,
// 二分过程中, 分到左边的操作存到 q1 中, 分到右边的操作存到 q2 中.
int ans[N];
void add(int p, int x);
int query(int p); // 树状数组函数, 含义见题3
void solve(int l, int r, int ql, int qr)
// 当前的值域范围为 [l,r], 处理的操作的区间为 [ql,qr]
{
    if (ql > qr) return;
    int cnt1 = 0, cnt2 = 0, mid = (l + r) >> 1;
    // cnt1, cnt2 分别为分到左边, 分到右边的操作数
    if (l == r)
    {
        for (int i = ql; i <= qr; i++)
            if (q[i].type == 1) ans[q[i].id] = l;
        return;
    }
    for (int i = ql; i <= qr; i++)
        if (q[i].type == 1)
        { // 是询问: 进行分类
            int t = query(q[i].y) - query(q[i].x - 1);
            if (q[i].k <= t)
                q1[++cnt1] = q[i];
            else
                q[i].k -= t, q2[++cnt2] = q[i];
        }
        else
            // 是修改: 更新树状数组 & 分类
            if (q[i].y <= mid)
                add(q[i].x, q[i].k), q1[++cnt1] = q[i];
            else
                q2[++cnt2] = q[i];
    for (int i = 1; i <= cnt1; i++)
        if (q1[i].type == 0) add(q1[i].x, -q1[i].k);                                 // 清空树状数组
    copy(q1 + 1, q1 + cnt1 + 1, q + ql), copy(q2 + 1, q2 + cnt2 + 1, q + ql + cnt1); // 将临时数组中的元素合并回原数组
    solve(l, mid, ql, ql + cnt1 - 1), solve(mid + 1, r, ql + cnt1, qr);
}