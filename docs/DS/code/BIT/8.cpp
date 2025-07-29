int getmax(int l, int r)
{
    int ans = 0;
    while (r >= l)
    {
        for (ans = max(ans, a[r--]); r - lowbit(r) >= l; r -= lowbit(r))
        {
            // 注意，循环条件不要写成 r - lowbit(r) + 1 >= l
            // 否则 l = 1 时，r 跳到 0 会死循环
            ans = max(ans, C[r]);
        }
    }
    return ans;
}