// 时间戳优化
int tag[MAXN], t[MAXN], Tag;
void reset() { ++Tag; }
void add(int k, int v)
{
    for (; k <= n; k += lowbit(k))
    {
        if (tag[k] != Tag) t[k] = 0;
        t[k] += v, tag[k] = Tag;
    }
}
int getsum(int k)
{
    int ret = 0;
    while (; k; k -= lowbit(k))
        if (tag[k] == Tag) ret += t[k];
    return ret;
}