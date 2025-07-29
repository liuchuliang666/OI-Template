#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const ll p = 998244353, g = 3;
ll qpow(ll a, ll b)
{
    static ll res;
    for (res = 1; b; b >>= 1, a = a * a % p)
        if (b & 1) res = res * a % p;
    return res;
}
ll inv(ll x) { return qpow(x, p - 2); }
const ll gi = inv(g);
const int MAXN = 3e5 + 10;
int n, rev[MAXN];
ll F[MAXN], G[MAXN];
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
                gk = gk * g1 % p;
            }
        }
    }
    if (op == 1) return;
    const ll ni = inv(n);
    for (int i = 0; i < n; i++) A[i] = A[i] * ni % p;
}
void Inv(ll *F, ll *G, int n)
{
    G[0] = inv(F[0]);
    int lim, len;
    static ll A[MAXN], B[MAXN];
    for (len = 1; len < (n << 1); len <<= 1)
    {
        lim = len << 1;
        copy(F, F + len, A), copy(G, G + len, B);
        for (int i = 0; i < lim; i++)
            rev[i] = (rev[i >> 1] >> 1) | ((lim >> 1) * (i & 1));
        NTT(A, lim, 1), NTT(B, lim, 1);
        for (int i = 0; i < lim; i++)
            G[i] = ((2 - A[i] * B[i] % p) * B[i] % p + p) % p;
        NTT(G, lim, -1);
        fill(G + len, G + lim, 0);
    }
    fill(A, A + len, 0), fill(B, B + len, 0), fill(G + n, G + len, 0);
}
void Sqrt(ll *F, ll *G, int n) // G = sqrt(F)
{
    static const ll inv2 = inv(2);
    G[0] = 1;
    static ll A[MAXN], B[MAXN];
    int len, lim;
    for (len = 1; len < (n << 1); len <<= 1)
    {
        lim = len << 1;
        copy(F, F + len, A);
        Inv(G, B, len);
        for (int i = 0; i < lim; i++)
            rev[i] = (rev[i >> 1] >> 1) | ((lim >> 1) * (i & 1));
        NTT(A, lim, 1), NTT(B, lim, 1);
        for (int i = 0; i < lim; i++) A[i] = A[i] * B[i] % p;
        NTT(A, lim, -1);
        for (int i = 0; i < len; i++) G[i] = (G[i] + A[i]) % p * inv2 % p;
        fill(G + len, G + lim, 0);
    }
    fill(A, A + len, 0), fill(B, B + len, 0), fill(G + n, G + len, 0);
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> F[i];
    Sqrt(F, G, n);
    for (int i = 0; i < n; i++) cout << G[i] << " ";
    return 0;
}