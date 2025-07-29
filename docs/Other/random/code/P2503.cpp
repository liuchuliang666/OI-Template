#include <bits/stdc++.h>
using namespace std;
#define urd uniform_real_distribution
int n, m, a[25], b[25];
double num1, ans = 2e9;
mt19937 rnd(1919810);
double ask()
{
    memset(b, 0, sizeof(b));
    b[0] = 2e9;
    for (int i = 1; i <= n; i++)
    {
        int x = 0;
        for (int j = 1; j <= m; j++)
            if (b[j] < b[x]) x = j;
        b[x] += a[i];
    }
    double num2 = 0;
    for (int i = 1; i <= m; i++) num2 += (num1 - b[i]) * (num1 - b[i]);
    return sqrt(num2 / m);
}
void sa()
{
    for (double st = 3000; st > 0.00000001; st *= 0.95)
    {
        int x = rnd() % n + 1, y = rnd() % n + 1;
        swap(a[x], a[y]);
        double now = ask(); // 省略
        if (now < ans)
            ans = now;
        else if (urd<>(0, 1)(rnd) > exp((now - ans) / st))
            swap(a[x], a[y]);
    }
}
int main(void)
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        num1 += a[i];
    }
    num1 /= m;
    const clock_t st = clock();
    while (1) // 卡时
    {
        rnd = mt19937(rnd());
        sa();
        const clock_t ed = clock();
        const int time_limit = 950;
        if (double(ed - st) * 1000 / CLOCKS_PER_SEC >= time_limit) break;
    }
    printf("%.2lf", ans);
    return 0;
}