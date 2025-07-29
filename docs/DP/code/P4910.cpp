#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const ll mod = 1e9 + 7;
inline void add(ll &a, ll b)
{
    a = (a + b) % mod;
}
struct Matrix
{
    int lx, ly;
    ll val[3][3];
    inline void init()
    {
        for (int i = 1; i <= min(lx, ly); i++)
            val[i][i] = 1;
    }
    inline ll *operator[](const int i)
    {
        return val[i];
    }
} trans, vec;
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
void init()
{
    vec.lx = 2, vec.ly = 1;
    vec[2][1] = 1;
    trans.lx = trans.ly = 2;
    trans[1][2] = trans[2][1] = trans[2][2] = 1;
}
void solve()
{
    ll n;
    cin >> n;
    Matrix tvec = qpow(trans, n - 1) * vec;
    cout << (tvec[1][1] * 2 + tvec[2][1]) % mod << endl;
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    init();
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}