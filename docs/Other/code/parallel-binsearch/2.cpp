struct Num
{
    int p, x;
}; // 位于数列中第 p 项的数的值为 x
struct Query
{
    int l, r, k, id;
}; // 一个编号为 id, 询问 [l,r] 中第 k 小数的询问
int ans[N];
void add(int p, int x); // 树状数组, 在 p 位置加上 x
int query(int p);       // 树状数组, 求 [1,p] 的和
void clear();           // 树状数组, 清空
void solve(int l, int r, vector<Num> a, vector<Query> q)
// a中为给定数列中值在值域区间 [l,r] 中的数
{
    int mid = (l + r) >> 1;
    if (l == r)
    {
        for (unsigned i = 0; i < q.size(); i++) ans[q[i].id] = l;
        return;
    }
    vector<Num> a1, a2;
    vector<Query> q1, q2;
    for (unsigned i = 0; i < a.size(); i++)
        if (a[i].x <= mid)
            a1.push_back(a[i]), add(a[i].p, 1);
        else
            a2.push_back(a[i]);
    for (unsigned i = 0; i < q.size(); i++)
    {
        int t = query(q[i].r) - query(q[i].l - 1);
        if (q[i].k <= t)
            q1.push_back(q[i]);
        else
            q[i].k -= t, q2.push_back(q[i]);
    }
    clear();
    solve(l, mid, a1, q1), solve(mid + 1, r, a2, q2);
}