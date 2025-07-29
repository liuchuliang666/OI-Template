void update(int x, int v)
{
    a[x] = v;
    for (int i = x; i <= n; i += lowbit(i))
    {
        // 枚举受影响的区间
        C[i] = a[i];
        for (int j = 1; j < lowbit(i); j <<= 1) C[i] = max(C[i], C[i - j]);
    }
}