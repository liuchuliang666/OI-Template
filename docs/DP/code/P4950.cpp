#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int ll
typedef long long ll;
typedef const int cint;
constexpr int MAXN = 1e3 + 5, mod = 1e9 + 7;
int n, k, dp[2][(1 << 15) + 5][3], f1[20], f2[20], ans[20];
char s[20];
template <typename T> inline void add(T &a, const T b) { a = ((a + b) % mod + mod) % mod; }
int encrypt(cint *f)
{
    int S = 0;
    for (int i = 0; i < k; i++) S += (f[i + 1] - f[i]) * (1ll << i);
    return S;
}
void decrypt(int *f, cint S)
{
    for (int i = 0; i < k; i++) f[i + 1] = S >> i & 1;
    for (int i = 1; i <= k; i++) f[i] += f[i - 1];
}
void DP(cint S, cint newi, cint newj, char c, cint val)
{
    decrypt(f1, S);
    for (int i = 1; i <= k; i++) f2[i] = max({f2[i - 1], f1[i], f1[i - 1] + (c == s[i])});
    add(dp[newi & 1][encrypt(f2)][newj], val);
}
signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> k >> (s + 1), dp[0][0][0] = 1;
    for (int i = 0; i < n; i++)
    {
        for (int S = 0; S < (1 << k); S++) dp[i & 1 ^ 1][S][0] = dp[i & 1 ^ 1][S][1] = dp[i & 1 ^ 1][S][2] = 0;
        for (int S = 0; S < (1 << k); S++)
        {
            if (dp[i & 1][S][0])
            {
                DP(S, i + 1, 1, 'N', dp[i & 1][S][0]);
                DP(S, i + 1, 0, 'O', dp[i & 1][S][0]);
                DP(S, i + 1, 0, 'I', dp[i & 1][S][0]);
            }
            if (dp[i & 1][S][1])
            {
                DP(S, i + 1, 1, 'N', dp[i & 1][S][1]);
                DP(S, i + 1, 2, 'O', dp[i & 1][S][1]);
                DP(S, i + 1, 0, 'I', dp[i & 1][S][1]);
            }
            if (dp[i & 1][S][2])
            {
                DP(S, i + 1, 1, 'N', dp[i & 1][S][2]);
                DP(S, i + 1, 0, 'O', dp[i & 1][S][2]);
            }
        }
    }
    for (int S = 0; S < (1 << k); S++) add(ans[__builtin_popcount(S)], ((dp[n & 1][S][0] + dp[n & 1][S][1]) % mod + dp[n & 1][S][2]) % mod);
    for (int i = 0; i <= k; i++) cout << ans[i] << endl;
    return 0;
}