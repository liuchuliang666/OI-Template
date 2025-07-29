#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const int MAXN = 4e6 + 10;
const ll p = 998244353, g = 3;
ll qpow(ll a, ll b)
{
    static ll res;
    for (res = 1; b; b >>= 1ll, a = a * a % p)
        if (b & 1ll) res = res * a % p;
    return res;
}
ll getinv(ll x) { return qpow(x, p - 2); }
const ll gi = getinv(g);
int rev[MAXN], n;
ll inv[MAXN], F[MAXN], G[MAXN], k, k2;
string sk;
void initinv(int n)
{
    inv[1] = 1;
    for (int i = 2; i <= n; i++) inv[i] = (p - p / i) * inv[p % i] % p;
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
        NTT(G, lim, -1), fill(G + len, G + lim, 0);
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
void Exp(int n, ll *F, ll *G)
{
    static ll A[MAXN], B[MAXN];
    int lim, len;
    G[0] = 1;
    for (len = 1; len < (n << 1); len <<= 1)
    {
        lim = len << 1;
        copy(F, F + len, A), Ln(len, G, B);
        for (int i = 0; i < lim; i++)
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * (lim >> 1));
        NTT(A, lim, 1), NTT(B, lim, 1), NTT(G, lim, 1);
        for (int i = 0; i < lim; i++)
            G[i] = (1 - B[i] + A[i] + p) % p * G[i] % p;
        NTT(G, lim, -1), fill(A, A + lim, 0), fill(B, B + lim, 0);
    }
    fill(G + n, G + len, 0);
}
void Pow(ll n, ll k, ll k2, ll *F, ll *G)
{
    static ll A[MAXN], B[MAXN];
    ll t = 0;
    while (t < n && !F[t]) t++;
    copy(F + t, F + n, A);
    ll m = n - t;
    ll f0 = A[0], invf0 = getinv(f0), pf0 = qpow(f0, k2);
    for (ll i = 0; i < m; i++) A[i] = A[i] * invf0 % p;
    Ln(m, A, B);
    for (ll i = 0; i < m; i++) B[i] = B[i] * k % p;
    fill(A, A + m, 0), Exp(m, B, A), t *= k2;
    for (ll i = n - t - 1; i >= 0; i--) G[i + t] = A[i] * pf0 % p;
    fill(A, A + m, 0), fill(B, B + m, 0);
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    initinv(4e6);
    cin >> n >> sk;
    for (char ch : sk)
        k = (k * 10 % p + (ch ^ 48)) % p,
        k2 = (k2 * 10 % (p - 1) + (ch ^ 48)) % (p - 1);
    for (int i = 0; i < n; i++) cin >> F[i];
    if (!(F[0] == 0 && sk.size() > log10(n) + 1)) Pow(n, k, k2, F, G);
    for (int i = 0; i < n; i++) cout << G[i] << " ";
    return 0;
}