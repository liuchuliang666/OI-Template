#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const int MAXN = 1 << 21;
const ll p = 998244353, g = 3;
ll qpow(ll a, ll b)
{
    ll res = 1;
    for (; b; b >>= 1, a = a * a % p)
        if (b & 1) res = res * a % p;
    return res;
}
ll inv(ll x) { return qpow(x, p - 2); }
const ll gi = inv(g);
int rev[MAXN];
ll F[MAXN], G[MAXN], H[MAXN];
void NTT(ll *A, int n, int op)
{
    for (int i = 0; i < n; i++)
        if (i < rev[i]) swap(A[i], A[rev[i]]);
    for (int i = 2; i <= n; i <<= 1)
    {
        ll g1 = qpow(op == 1 ? g : gi, (p - 1) / i);
        for (int j = 0; j < n; j += i)
        {
            ll gk = 1;
            for (int k = j; k < j + i / 2; k++)
            {
                ll x = A[k], y = A[k + i / 2] * gk % p;
                A[k] = (x + y) % p;
                A[k + i / 2] = (x - y + p) % p;
                gk = g1 * gk % p;
            }
        }
    }
    if (op == 1) return;
    const ll ni = inv(n);
    for (int i = 0; i < n; i++) A[i] = A[i] * ni % p;
}
void Inv(int n, ll *F, ll *G)
{
    static ll A[MAXN], B[MAXN];
    G[0] = inv(F[0]);
    int len, lim;
    for (len = 1; len < (n << 1); len <<= 1)
    {
        lim = len << 1;
        copy(F, F + len, A), copy(G, G + len, B);
        for (int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * len);
        NTT(A, lim, 1), NTT(B, lim, 1);
        for (int i = 0; i < lim; i++)
            G[i] = ((2 - A[i] * B[i] % p) * B[i] % p + p) % p;
        NTT(G, lim, -1);
        fill(G + len, G + lim, 0);
    }
    fill(A, A + len, 0), fill(B, B + len, 0), fill(G + n, G + len, 0);
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> F[i];
    Inv(n, F, G);
    for (int i = 0; i < n; i++) cout << G[i] << " ";
    return 0;
}