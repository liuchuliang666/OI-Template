#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const int MAXN = 4e5 + 10;
const ll p = 998244353, g = 3;
ll qpow(ll a, ll b)
{
    static ll res;
    for (res = 1; b; b >>= 1, a = a * a % p)
        if (b & 1) res = res * a % p;
    return res;
}
ll getinv(ll x) { return qpow(x, p - 2); }
const ll gi = getinv(g);
int rev[MAXN];
ll inv[MAXN], F[MAXN], G[MAXN];
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
    NTT(A, lim, -1), fill(A + n, A + lim, 0), Int(n - 1, A, G);
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
ll cnt[MAXN], n, m;
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    initinv(4e5);
    cin >> n >> m;
    for (int v, i = 1; i <= n; i++) cin >> v, cnt[v]++;
    for (ll i = 1; i <= m; i++)
        if (cnt[i])
            for (ll j = 1; j <= m / i; j++)
                F[i * j] = (F[i * j] + cnt[i] * (p - inv[j])) % p;
    Exp(m + 1, F, G), memset(F, 0, sizeof(F)), Inv(m + 1, G, F);
    for (int i = 1; i <= m; i++) cout << F[i] << endl;
    return 0;
}