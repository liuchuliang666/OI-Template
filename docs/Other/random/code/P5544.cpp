#include <bits/stdc++.h>
using namespace std;
#define urd uniform_real_distribution
mt19937 rnd(12);
int n, m, mxr, ans;
struct node
{
    int x, y, r;
} a[15], b[1005];
double gtds(double x, double y, double xx, double yy)
{
    return (x - xx) * (x - xx) + (y - yy) * (y - yy);
}
double _count(double x, double y)
{
    int num1 = 0;
    double num2 = 1e13, r = mxr;
    for (int i = 1; i <= n; i++)
    {
        double dis = sqrt(gtds(a[i].x, a[i].y, x, y));
        r = min(r, max(dis - a[i].r, 0.0));
    }
    for (int i = 1; i <= m; i++)
    {
        double dis = sqrt(gtds(b[i].x, b[i].y, x, y));
        if (dis <= r) num1++;
        num2 = min(num2, dis - r);
    }
    ans = max(ans, num1);
    return num1 - max(0.0, num2) * 14.14;
}
void sa()
{
    double x = 0, y = 0;
    double ls = _count(x, y);
    for (double st = 1e12; st >= 1e-8; st *= 0.9996)
    {
        double xx = x + urd<>(-10, 10)(rnd) * st;
        double yy = y + urd<>(-10, 10)(rnd) * st;
        double now = _count(xx, yy);
        if (now > ls || urd<>(0, 1)(rnd) <= exp((now - ls) / st))
        {
            x = xx;
            y = yy;
            ls = now;
        }
    }
}
int main(void)
{
    scanf("%d%d%d", &n, &m, &mxr);
    for (int i = 1; i <= n; i++) scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].r);
    for (int i = 1; i <= m; i++) scanf("%d%d", &b[i].x, &b[i].y);
    sa();
    rnd = mt19937(20060617);
    sa();
    sa();
    printf("%d", ans);
    return 0;
}