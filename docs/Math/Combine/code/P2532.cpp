#include <bits/stdc++.h>
using namespace std;
int f[505][500];
int len = 1;
void mul(int u)
{
    for (int i = 1; i <= len; i++) f[u][i] += f[u - 1][i];
    for (int i = 1; i <= len; i++)
    {
        f[u][i + 1] += f[u][i] / 10;
        f[u][i] %= 10;
    }
    if (f[u][len + 1]) len++;
}
int main()
{
    int n;
    cin >> n;
    f[1][1] = 1;
    for (int i = 2; i <= n + 1; i++)
        for (int j = 1; j <= i; j++) mul(j);
    for (int i = len; i >= 1; i--) cout << f[n][i];
    return 0;
}
