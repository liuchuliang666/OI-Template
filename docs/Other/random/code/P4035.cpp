#include <bits/stdc++.h>
using namespace std;
int n;
double spot[15][15], ans[15], dis[15], cans[15];
void check()
{
    double sum = 0;
    for (int i = 1; i <= n + 1; i++)
    {
        dis[i] = cans[i] = 0;
        for (int j = 1; j <= n; j++)
            dis[i] += (spot[i][j] - ans[j]) * (spot[i][j] - ans[j]);
        dis[i] = sqrt(dis[i]);
        sum += dis[i];
    }
    sum /= (n + 1);
    for (int i = 1; i <= n + 1; i++)
        for (int j = 1; j <= n; j++)
            cans[j] += (dis[i] - sum) * (spot[i][j] - ans[j]) / sum;
}
int main(void)
{
    scanf("%d", &n);
    for (int i = 1; i <= n + 1; i++)
        for (int j = 1; j <= n; j++)
        {
            scanf("%lf", &spot[i][j]);
            ans[j] += spot[i][j];
        }
    for (int i = 1; i <= n; i++) ans[i] /= (n + 1);
    for (double t = 10001; t >= 0.0001; t *= 0.99995)
    {
        check();
        for (int i = 1; i <= n; i++) ans[i] += cans[i] * t;
    }
    for (int i = 1; i <= n; i++) printf("%.3lf ", ans[i]);
    return 0;
}