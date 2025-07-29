#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXM = 7, MAXV = 1 << MAXM;
const ll p = 1e9 + 7;
inline ll mod(const ll x) { return x % p; }
ll n, m, k, sz, ans;
struct matrix
{
    ll val[MAXV][MAXV];
    inline ll *operator[](const int i) { return val[i]; }
    matrix() : val({}) {}
    inline void init()
    {
        for (int i = 0; i < sz; i++)
            val[i][i] = 1;
    }
    friend inline matrix operator*(matrix a, matrix b)
    {
        matrix res;
        for (int i = 0; i < sz; i++)
            for (int j = 0; j < sz; j++)
                for (int kk = 0; kk < sz; kk++)
                    res[i][j] = mod(res[i][j] + mod(a[i][kk] * b[kk][j]));
        return res;
    }
    inline matrix pow(ll b)
    {
        matrix res, a = *this;
        res.init();
        while (b)
        {
            if (b & 1ll)
                res = res * a;
            a = a * a;
            b >>= 1ll;
        }
        return res;
    }
} mat, amat;
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m >> k;
    sz = 1 << m;
    for (int i = 0, j; i < sz; i++)
    {
        if (__builtin_popcount(i) > k)
            continue;
        j = i >> 1;
        mat[j][i] = 1;
        j = (i >> 1) | (1 << (m - 1));
        if (__builtin_popcount(j) <= k)
            mat[j][i] = 1;
    }
    amat = mat.pow(n);
    for (int i = 0; i < sz; i++)
        ans = mod(ans + amat[i][i]);
    cout << ans;
    return 0;
}