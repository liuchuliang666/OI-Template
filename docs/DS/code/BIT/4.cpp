int t1[MAXN], t2[MAXN], n;
int lowbit(int x) { return x & (-x); }
void add(int k, int v)
{
    int v1 = k * v;
    for (; k <= n; k += lowbit(k)) t1[k] += v, t2[k] += v1;
    // 注意不能写成 t2[k] += k * v，因为 k 的值已经不是原数组的下标了
}
int getsum(int *t, int k)
{
    static int ret;
    for (ret = 0; k; k -= lowbit(k)) ret += t[k];
    return ret;
}
void add1(int l, int r, int v)
{
    add(l, v), add(r + 1, -v); // 将区间加差分为两个前缀加
}
long long getsum1(int l, int r) { return (r + 1ll) * getsum(t1, r) - 1ll * l * getsum(t1, l - 1) - (getsum(t2, r) - getsum(t2, l - 1)); }