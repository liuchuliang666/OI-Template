#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define eb emplace_back
#define fi first
#define se second
#define int ll
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
constexpr int MAXN = (1 << 18) + 10, mod = 998244353;
#define mst(x, val) memset(x, val, sizeof(x))
#define mcp(from, to) memcpy(to, from, sizeof(to))
int n, a[MAXN], b[MAXN], m, p[MAXN], q[MAXN];
template <typename T> inline void add(T &a, const T b) { a = ((a + b) % mod + mod) % mod; }
template <typename T> inline void mul(T &a, const T b) { a = ((a * b) % mod + mod) % mod; }
int qpow(int a, int b)
{
    static int res;
    for (res = 1; b; b >>= 1, mul(a, a)) ((b & 1) && (mul(res, a), 1));
    return res;
}
int inv(int x) { return qpow(x, mod - 2); }
void OR(int *a, int op)
{
    for (int x = 2, k = 1; x <= n; x <<= 1, k <<= 1)
        for (int i = 0; i < n; i += x)
            for (int j = 0; j < k; j++)
                add(a[i + j + k], a[i + j] * op);
}
void AND(int *a, int op)
{
    for (int x = 2, k = 1; x <= n; x <<= 1, k <<= 1)
        for (int i = 0; i < n; i += x)
            for (int j = 0; j < k; j++)
                add(a[i + j], a[i + j + k] * op);
}
void XOR(int *a, int op)
{
    for (int x = 2, k = 1; x <= n; x <<= 1, k <<= 1)
        for (int i = 0; i < n; i += x)
            for (int j = 0; j < k; j++)
            {
                int x = a[i + j], y = a[i + j + k];
                a[i + j] = (x + y) % mod;
                a[i + j + k] = (x - y + mod) % mod;
                mul(a[i + j], op), mul(a[i + j + k], op);
            }
}
signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> m, n = (1 << m);
    for (int i = 0; i < n; i++) cin >> p[i];
    for (int i = 0; i < n; i++) cin >> q[i];
    mcp(p, a), mcp(q, b), OR(a, 1), OR(b, 1);
    for (int i = 0; i < n; i++) mul(a[i], b[i]);
    OR(a, mod - 1);
    for (int i = 0; i < n; i++) cout << a[i] << " \n"[i == n - 1];
    mcp(p, a), mcp(q, b), AND(a, 1), AND(b, 1);
    for (int i = 0; i < n; i++) mul(a[i], b[i]);
    AND(a, mod - 1);
    for (int i = 0; i < n; i++) cout << a[i] << " \n"[i == n - 1];
    mcp(p, a), mcp(q, b), XOR(a, 1), XOR(b, 1);
    for (int i = 0; i < n; i++) mul(a[i], b[i]);
    XOR(a, inv(2));
    for (int i = 0; i < n; i++) cout << a[i] << " \n"[i == n - 1];
    return 0;
}