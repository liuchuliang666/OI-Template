#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const ll mod = 2009;
ll n, t;
inline int getid(int x, int y) { return n * y + x; }
inline void add(ll &a, ll b)
{
    a = (a + b) % mod;
}
struct Matrix
{
    int lx, ly;
    ll val[120][120];
    inline void init()
    {
        for (int i = 1; i <= min(lx, ly); i++)
            val[i][i] = 1;
    }
    inline ll *operator[](const int i)
    {
        return val[i];
    }
} e;
Matrix operator*(Matrix a, Matrix b)
{
    Matrix c = {a.lx, b.ly, {}};
    for (int i = 1; i <= a.lx; i++)
        for (int k = 1; k <= a.ly; k++)
            for (int j = 1; j <= b.ly; j++)
                add(c[i][j], a[i][k] * b[k][j] % mod);
    return c;
}
Matrix qpow(Matrix a, ll b)
{
    Matrix c = {a.lx, a.ly, {}};
    for (c.init(); b; b >>= 1ll, a = a * a)
        if (b & 1ll)
            c = c * a;
    return c;
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> t;
    e.lx = e.ly = 9 * n;
    char c;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j < 10; j++)
            e[getid(i, j)][getid(i, j - 1)] = 1;
        for (int j = 1; j <= n; j++)
        {
            cin >> c;
            if (c == '0')
                continue;
            e[getid(i, 0)][getid(j, c - '0' - 1)] = 1;
        }
    }
    Matrix g = qpow(e, t);
    cout << g[getid(1, 0)][getid(n, 0)];
    return 0;
}