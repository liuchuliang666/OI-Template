// 权值树状数组查询第 k 小
int kth(int k)
{
    int sum = 0, x = 0;
    for (int i = log2(n); ~i; --i)
    {
        x += (1 << i);                 // 尝试扩展
        if (x >= n || sum + t[x] >= k) // 如果扩展失败
            x -= (1 << i);
        else
            sum += t[x];
    }
    return x + 1;
}