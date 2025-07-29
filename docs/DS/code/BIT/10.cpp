// Θ(n) 建树
void init()
{
    for (int i = 1; i <= n; i++)
    {
        t[i] += a[i];
        int j = i + lowbit(i);
        if (j <= n) t[j] += t[i];
    }
}