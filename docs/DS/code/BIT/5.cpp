void add(int x, int y, int v)
{ // 单点加
    for (int i = x; i <= n; i += lowbit(i))
        for (int j = y; j <= m; j += lowbit(j))
            // 注意这里必须得建循环变量，不能像一维数组一样直接 while (x <= n) 了
            c[i][j] += v;
}
int sum(int x, int y)
{ // 查询子矩阵和
    int res = 0;
    for (int i = x; i; i -= lowbit(i))
        for (int j = y; j; j -= lowbit(j)) res += c[i][j];
    return res;
}
int ask(int x1, int y1, int x2, int y2)
{
    // 查询子矩阵和
    return sum(x2, y2) - sum(x2, y1 - 1) - sum(x1 - 1, y2) + sum(x1 - 1, y1 - 1);
}