#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
ll qpow(ll a, ll b, ll p)
{
    static ll res;
    for (res = 1; b; b >>= 1ll, a = a * a % p)
        if (b & 1ll) res = res * a % p;
    return res;
}
ll inv(ll a, ll p) { return qpow(a, p - 2, p); }
const ll mod[] = {0, 469762049, 998244353, 1004535809}, g = 3;
const int MAXN = 3e5 + 10;
int n, m, rev[MAXN];
ll A[4][MAXN], B[4][MAXN], p;
void NTT(ll *A, int n, int op, ll p)
{
    const ll gi = inv(g, p), ni = inv(n, p);
    for (int i = 0; i < n; i++)
        if (i < rev[i]) swap(A[i], A[rev[i]]);
    for (int i = 2; i <= n; i <<= 1)
    {
        ll g1 = qpow(op == 1 ? g : gi, (p - 1) / i, p);
        for (int j = 0; j < n; j += i)
        {
            ll gk = 1;
            for (int k = j; k < j + i / 2; k++)
            {
                ll x = A[k], y = A[k + i / 2] * gk % p;
                A[k] = (x + y) % p;
                A[k + i / 2] = (x - y + p) % p;
                gk = gk * g1 % p;
            }
        }
    }
    if (op == -1)
        for (int i = 0; i < n; i++) A[i] = A[i] * ni % p;
}
ll merge(ll a, ll b, ll c, ll p)
{
    const static ll md12 = mod[1] * mod[2], inv12 = inv(mod[1], mod[2]),
                    inv123 = inv(mod[1] * mod[2] % mod[3], mod[3]);
    ll d = (b - a + mod[2]) % mod[2] * inv12 % mod[2] * mod[1] + a;
    ll x =
        (c - d % mod[3] + mod[3]) % mod[3] * inv123 % mod[3] * (md12 % p) % p +
        d;
    return x % p;
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m >> p;
    for (int x, i = 0; i <= n; i++)
        cin >> x, A[1][i] = A[2][i] = A[3][i] = x % p;
    for (int x, i = 0; i <= m; i++)
        cin >> x, B[1][i] = B[2][i] = B[3][i] = x % p;
    for (m = n + m, n = 1; n <= m; n <<= 1);
    for (int i = 0; i < n; i++)
        rev[i] = (rev[i >> 1] >> 1) | ((n >> 1) * (i & 1));
    for (int i = 1; i <= 3; i++)
    {
        NTT(A[i], n, 1, mod[i]);
        NTT(B[i], n, 1, mod[i]);
        for (int j = 0; j < n; j++) A[i][j] = A[i][j] * B[i][j] % mod[i];
        NTT(A[i], n, -1, mod[i]);
    }
    for (int i = 0; i <= m; i++)
        cout << merge(A[1][i], A[2][i], A[3][i], p) << " ";
    return 0;
}