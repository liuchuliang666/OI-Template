#include <bits/stdc++.h>
using namespace std;
int n, m;
long long f[2][(1 << 10)];
int p[20];
int main()
{
    for (int i = 1; i <= 15; i++)
    {
        p[i] = 1 << (i - 1);
    } // 预处理
    while (~scanf("%d %d", &n, &m))
    {
        if (n < m)
            swap(n, m);          // 交换，使m不大于10
        int d = 0;               // 滚动数组下标
        memset(f, 0, sizeof(f)); // 清空
        f[0][(1 << m) - 1] = 1;  // 初始化
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                d ^= 1;                        // d在0与1之间滚动
                memset(f[d], 0, sizeof(f[d])); // 清空
                for (int k = 0; k < (1 << m); k++)
                {
                    if (k & p[j])
                        f[d][k ^ p[j]] += f[d ^ 1][k];            // 留空
                    if ((j > 1) && !(k & p[j - 1]) && (k & p[j])) // 横放
                        f[d][k | p[j - 1]] += f[d ^ 1][k];
                    if ((i > 1) && !(k & p[j]))
                        f[d][k | p[j]] += f[d ^ 1][k]; // 竖放
                }
            }
        }
        cout << f[d][(1 << m) - 1] << endl; // 最终输出最后一行也填满的情况
    }
}