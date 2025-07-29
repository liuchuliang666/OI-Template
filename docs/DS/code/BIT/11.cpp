// Θ(n) 建树
void init()
{
    for (int i = 1; i <= n; i++)
        t[i] = sum[i] - sum[i - lowbit(i)];
}