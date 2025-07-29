#include <bits/stdc++.h>
using namespace std;
#define urd uniform_real_distribution
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
int n, m, c, a[25][25], aa[25][25], ans = 2e9, b[25][25], book[25];
int check(int xa, int ya, int xb, int yb)
{
    if (xa < 1 || xa > n) return 0;
    if (xb < 1 || xb > n) return 0;
    if (ya < 1 || ya > m) return 0;
    if (yb < 1 || yb > m) return 0;
    if (a[xa][ya] != a[xb][yb]) return 1;
    return 0;
}
void sa()
{
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) a[i][j] = aa[i][j];
    int lst = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            lst += check(i, j, i + 1, j) + check(i, j, i, j + 1);
    for (double st = 1; st >= 1e-15; st *= 0.99999)
    {
        if (lst < ans)
        {
            ans = lst;
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= m; j++) b[i][j] = a[i][j];
        }
        int xa = rnd() % n + 1, ya = rnd() % m + 1;
        int xb = rnd() % n + 1, yb = rnd() % m + 1;
        int now = lst;
        now -= check(xa, ya, xa - 1, ya) + check(xb, yb, xb - 1, yb);
        now -= check(xa, ya, xa + 1, ya) + check(xb, yb, xb + 1, yb);
        now -= check(xa, ya, xa, ya - 1) + check(xb, yb, xb, yb - 1);
        now -= check(xa, ya, xa, ya + 1) + check(xb, yb, xb, yb + 1);
        swap(a[xa][ya], a[xb][yb]);
        now += check(xa, ya, xa - 1, ya) + check(xb, yb, xb - 1, yb);
        now += check(xa, ya, xa + 1, ya) + check(xb, yb, xb + 1, yb);
        now += check(xa, ya, xa, ya - 1) + check(xb, yb, xb, yb - 1);
        now += check(xa, ya, xa, ya + 1) + check(xb, yb, xb, yb + 1);
        if (now < lst || urd<>(0, 1)(rnd) <= exp((lst - now) / st))
            lst = now;
        else
            swap(a[xa][ya], a[xb][yb]);
    }
}
int main(void)
{
    scanf("%d%d%d", &n, &m, &c);
    int nx = 1, ny = 1;
    for (int i = 1; i <= c; i++)
    {
        int x;
        scanf("%d", &x);
        while (x--)
        {
            aa[nx][ny] = i;
            nx++;
            if (nx > n)
            {
                nx = 1;
                ny++;
            }
        }
    }
    sa();
    sa();
    sa();
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++) printf("%d ", b[i][j]);
        putchar('\n');
    }
    return 0;
}