#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const ll MAXN = 5e5 + 10, p = 998244353;
int n, m, k;
ll rev[MAXN], res[MAXN], T[MAXN], F[MAXN], G[MAXN], Q[MAXN], R[MAXN], lim;
ll qpow(ll a, ll b)
{
    static ll res;
    for (res = 1; b; b >>= 1, a = a * a % p)
        if (b & 1) res = res * a % p;
    return res;
}
ll inv(ll x) { return qpow(x, p - 2); }
const ll g = 3, gi = inv(g);
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
    const int ni = inv(n);
    for (int i = 0; i < n; i++) A[i] = A[i] * ni % p;
}
void Inv(int n, ll *F, ll *G)
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
void Mul(int n, int m, ll *F, ll *G, bool flag = 1)
{
    static ll A[MAXN], B[MAXN];
    fill(A, A + (n << 2), 0), fill(B, B + (n << 2), 0), copy(F, F + n, A),
        copy(G, G + n, B);
    for (int i = 0; i < n; i++) A[i] = F[i], B[i] = G[i];
    for (lim = 1; lim <= (n + m); lim <<= 1);
    for (int i = 0; i <= lim; i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * (lim >> 1));
    NTT(A, lim, 1), NTT(B, lim, 1);
    for (int i = 0; i < lim; i++) A[i] = A[i] * B[i] % p;
    NTT(A, lim, -1), copy(A, A + (n << 1), F),
        fill(F + (n << 1), F + lim + 1, 0);
    if (flag) fill(F + n, F + (n << 1), 0);
}
void Mod(int n, int m, ll *F, ll *G, ll *R)
{
    static ll A[MAXN], B[MAXN], D[MAXN];
    fill(A, A + (n << 2), 0), fill(B, B + (n << 2), 0),
        fill(D, D + (n << 2), 0);
    for (int i = 0; i < n - m + 1; i++)
        A[i] = F[n - i - 1], B[i] = G[m - i - 1];
    Inv(n - m + 1, B, D), Mul(n - m + 1, n - m + 1, A, D);
    for (int i = 0; i <= n - m; i++) Q[i] = A[n - m - i];
    fill(A, A + (n << 2), 0), fill(B, B + (n << 2), 0), copy(F, F + n, A),
        copy(G, G + m, B), Mul(n, n, B, Q);
    for (int i = 0; i < m - 1; i++) R[i] = (A[i] - B[i] + p) % p;
    fill(R + m - 1, R + lim, 0);
}
void Pow(ll k, int n)
{
    for (T[1] = res[0] = 1; k;
         Mul(n, n, T, T, 0), Mod(n << 1, n, T, G, T), k >>= 1)
        if (k & 1) Mul(n, n, res, T, 0), Mod(n << 1, n, res, G, res);
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    G[0] = 1;
    for (int i = 1; i <= m; i++)
    {
        ll val;
        cin >> val;
        G[i] = (p - (val % p + p) % p) % p;
    }
    reverse(G, G + m + 1);
    for (int i = 0; i < m; i++) cin >> F[i];
    Pow(n, m + 1);
    ll ans = 0;
    for (int i = 0; i < m; i++) ans = (ans + res[i] * F[i] % p + p) % p;
    cout << ans << endl;
    return 0;
}