#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e5 + 5;
int n;
double p[N], Ex[N], Ex2[N], f[N];
signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> p[i];
    for (int i = 1; i <= n; i++)
    {
        Ex[i] = p[i] * (Ex[i - 1] + 1);
        Ex2[i] = p[i] * (Ex2[i - 1] + 2 * Ex[i - 1] + 1);
        f[i] = f[i - 1] + p[i] * (3 * (Ex[i - 1] + Ex2[i - 1]) + 1);
    }
    cout << fixed << setprecision(1) << f[n];
    return 0;
}