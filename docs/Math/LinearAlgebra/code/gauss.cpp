#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
bitset<1010> matrix[2010];                  // matrix[1~n]：增广矩阵，0 位置为常数
vector<bool> GaussElimination(int n, int m) // n 为未知数个数，m 为方程个数，返回方程组的解
                                            // （多解 / 无解返回一个空的 vector）
{
    for (int i = 1; i <= n; i++)
    {
        int cur = i;
        while (cur <= m && !matrix[cur].test(i)) cur++;
        if (cur > m) return vector<bool>(0);
        if (cur != i) swap(matrix[cur], matrix[i]);
        for (int j = 1; j <= m; j++)
            if (i != j && matrix[j].test(i)) matrix[j] ^= matrix[i];
    }
    vector<bool> ans(n + 1);
    for (int i = 1; i <= n; i++) ans[i] = matrix[i].test(0);
    return ans;
}
void solve()
{
    constexpr double EPS = 1E-9;
    int n;
    vector<vector<double>> a(n, vector<double>(n));
    double det = 1;
    for (int i = 0; i < n; ++i)
    {
        int k = i;
        for (int j = i + 1; j < n; ++j)
            if (abs(a[j][i]) > abs(a[k][i])) k = j;
        if (abs(a[k][i]) < EPS)
        {
            det = 0;
            break;
        }
        swap(a[i], a[k]);
        if (i != k) det = -det;
        det *= a[i][i];
        for (int j = i + 1; j < n; ++j) a[i][j] /= a[i][i];
        for (int j = 0; j < n; ++j)
            if (j != i && abs(a[j][i]) > EPS)
                for (int k = i + 1; k < n; ++k) a[j][k] -= a[i][k] * a[j][i];
    }
    cout << det;
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    solve();
    return 0;
}