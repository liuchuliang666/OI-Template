void add(int x, int k)
{
    // 不能越界
    for (; x <= n; x += lowbit(x)) c[x] += k;
}