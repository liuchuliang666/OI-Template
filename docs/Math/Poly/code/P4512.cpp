#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const int MAXN = 4e5 + 10;
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
    ll ni = inv(n);
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
ll F[MAXN], G[MAXN], Q[MAXN], R[MAXN];
void Div(ll *F, ll *G, ll *Q, ll *R, int n, int m)
{
    static ll B[MAXN], BR[MAXN], A[MAXN];
    static int lim;
    for (lim = 1; lim < (n << 1); lim <<= 1);
    copy(G, G + m, B), reverse(B, B + m), Inv(n, B, BR);
    for (lim = 1; lim < (n << 1); lim <<= 1);
    copy(F, F + n, B), reverse(B, B + n);
    NTT(B, lim, 1), NTT(BR, lim, 1);
    for (int i = 0; i < lim; i++) Q[i] = B[i] * BR[i] % p;
    NTT(Q, lim, -1), fill(Q + n - m + 1, Q + lim, 0), reverse(Q, Q + n - m + 1),
        fill(B, B + lim, 0), fill(BR, BR + lim, 0), copy(Q, Q + n - m + 1, A),
        copy(G, G + m, B), NTT(A, lim, 1), NTT(B, lim, 1);
    for (int i = 0; i < lim; i++) A[i] = A[i] * B[i] % p;
    NTT(A, lim, -1);
    for (int i = 0; i < m - 1; i++) R[i] = (F[i] + p - A[i]) % p;
    fill(B, B + lim, 0), fill(BR, BR + lim, 0), fill(A, A + lim, 0);
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i <= n; i++) cin >> F[i];
    for (int i = 0; i <= m; i++) cin >> G[i];
    n++, m++;
    Div(F, G, Q, R, n, m);
    for (int i = 0; i <= n - m; i++) cout << Q[i] << " ";
    cout << endl;
    for (int i = 0; i < m - 1; i++) cout << R[i] << " ";
    cout << endl;
    return 0;
}