#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const int MAXN = 4e5 + 10;
const ll p = 1004535809, g = 3;
ll qpow(ll a, ll b)
{
    ll res = 1;
    for (; b; b >>= 1, a = a * a % p)
        if (b & 1) res = res * a % p;
    return res;
}
ll getinv(ll x) { return qpow(x, p - 2); }
const ll gi = getinv(g);
int rev[MAXN], n;
ll inv[MAXN], F[MAXN], G[MAXN], frac[MAXN], ifrac[MAXN];
void initinv(int n)
{
    inv[1] = frac[1] = frac[0] = 1;
    for (int i = 2; i <= n; i++)
        inv[i] = (p - p / i) * inv[p % i] % p, frac[i] = frac[i - 1] * i % p;
    ifrac[n] = getinv(frac[n]);
    for (int i = n - 1; i + 1; i--) ifrac[i] = (i + 1) * ifrac[i + 1] % p;
}
void Dert(int n, ll *F, ll *G)
{
    for (int i = 1; i < n; i++) G[i - 1] = F[i] * i % p;
}
void Int(int n, ll *F, ll *G)
{
    for (int i = 0; i < n; i++) G[i + 1] = F[i] * inv[i + 1] % p;
}
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
    ll ni = getinv(n);
    for (int i = 0; i < n; i++) A[i] = A[i] * ni % p;
}
void Inv(int n, ll *F, ll *G)
{
    static ll A[MAXN], B[MAXN];
    G[0] = getinv(F[0]);
    int len, lim;
    for (len = 1; len < (n << 1); len <<= 1)
    {
        lim = len << 1;
        copy(F, F + len, A), copy(G, G + len, B);
        for (int i = 0; i < lim; i++)
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * len);
        NTT(A, lim, 1), NTT(B, lim, 1);
        for (int i = 0; i < lim; i++)
            G[i] = ((2 - A[i] * B[i] % p) * B[i] % p + p) % p;
        NTT(G, lim, -1);
        fill(G + len, G + lim, 0);
    }
    fill(A, A + len, 0), fill(B, B + len, 0), fill(G + n, G + len, 0);
}
void Ln(int n, ll *F, ll *G)
{
    static ll A[MAXN], B[MAXN];
    Inv(n, F, A), Dert(n, F, B);
    int lim;
    for (lim = 1; lim < (n << 1); lim <<= 1);
    for (int i = 0; i < lim; i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * (lim >> 1));
    NTT(A, lim, 1), NTT(B, lim, 1);
    for (int i = 0; i < lim; i++) A[i] = A[i] * B[i] % p;
    NTT(A, lim, -1), fill(A + n, A + lim, 0), Int(n - 1, A, G),
        fill(A, A + lim, 0), fill(B, B + lim, 0);
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    initinv(4e5);
    cin >> n;
    F[0] = 1;
    for (int i = 1; i <= n; i++)
        F[i] = qpow(2, 1ll * i * (i - 1) / 2) * ifrac[i] % p;
    Ln(n + 1, F, G);
    cout << G[n] * frac[n] % p;
    return 0;
}