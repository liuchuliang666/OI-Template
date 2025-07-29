#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const int MAXN = 4e6 + 10;
const ll p = 998244353, g = 3; // 模数和原根
ll A[MAXN], B[MAXN];
int rev[MAXN], n, m;
ll qpow(ll a, ll b)
{
    static ll res;
    for (res = 1; b; b >>= 1, a = a * a % p)
        if (b & 1) res = res * a % p;
    return res;
}
ll inv(ll x) { return qpow(x, p - 2); }
const ll gi = inv(g);
void NTT(ll *A, int n, int op)
{
    for (int i = 0; i < n; i++) // 位逆序变换
        if (i < rev[i]) swap(A[i], A[rev[i]]);
    for (int i = 2; i <= n; i <<= 1)
    {
        ll g1 = qpow(op == 1 ? g : gi, (p - 1) / i); // 对应FFT中的单位根omega1
        for (int j = 0; j < n; j += i)
        {
            ll gk = 1;
            for (int k = j; k < j + i / 2; k++) // 这里的合并与FFT都是一样的
            {
                ll x = A[k], y = A[k + i / 2] * gk % p;
                A[k] = (x + y) % p;
                A[k + i / 2] = (x - y + p) % p;
                gk = gk * g1 % p; // 求解gk
            }
        }
    }
    if (op == 1) return;
    const ll ni = inv(n);
    for (int i = 0; i < n; i++) A[i] = A[i] * ni % p; // INTT
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 0; i <= n; i++) cin >> A[i];
    for (int i = 0; i <= m; i++) cin >> B[i];
    for (m = n + m, n = 1; n <= m; n <<= 1);
    for (int i = 0; i < n; i++) rev[i] = (rev[i >> 1] >> 1) | ((n >> 1) * (i & 1));
    NTT(A, n, 1), NTT(B, n, 1);
    for (int i = 0; i < n; i++) A[i] = A[i] * B[i] % p;
    NTT(A, n, -1);
    for (int i = 0; i <= m; i++) cout << A[i] << ' ';
    return 0;
}