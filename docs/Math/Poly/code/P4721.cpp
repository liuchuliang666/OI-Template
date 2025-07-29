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
const int MAXN = 2e5 + 10;
int n, rev[MAXN], m;
ll F[MAXN], G[MAXN], A[MAXN], B[MAXN];
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
void solve(int l, int r) // [l, mid) -> [mid, r)
{
    if (r - l < 2) return;
    int mid = (l + r) >> 1, len;
    solve(l, mid);
    copy(F + l, F + mid, A), copy(G, G + r - l, B);
    for (len = 1; len < r - l; len <<= 1);
    for (int i = 0; i < len; i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * (len >> 1));
    NTT(A, len, 1), NTT(B, len, 1);
    for (int i = 0; i < len; i++) A[i] = A[i] * B[i] % p;
    NTT(A, len, -1);
    for (int i = mid; i < r; i++) F[i] = (F[i] + A[i - l]) % p;
    fill(A, A + len, 0), fill(B, B + len, 0);
    solve(mid, r);
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    F[0] = 1;
    cin >> n;
    for (int i = 1; i < n; i++) cin >> G[i];
    solve(0, n);
    for (int i = 0; i < n; i++) cout << F[i] << " ";
    return 0;
}