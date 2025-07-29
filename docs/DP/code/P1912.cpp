#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long double ll;
const string sep = "--------------------", fail = "Too hard to arrange";
const int MAXN = 1e5 + 10;
struct Opt
{
    int r, opt;
} q[MAXN];
int n, hd, tl, p, pre[MAXN];
ll L, s[MAXN], f[MAXN];
string str[MAXN];
inline ll qpow(ll a, int b)
{
    static ll res;
    for (res = 1; b; b >>= 1, a = a * a)
        if (b & 1) res = res * a;
    return res;
}
inline ll calc(const int i, const int j) { return f[j] + qpow(fabs(s[i] - s[j] - 1 - L), p); }
int bound(int pos, int nopt)
{
    auto [r, opt] = q[pos];
    int l = q[pos - 1].r + 1, res = r, mid;
    while (l <= r)
    {
        mid = l + r >> 1;
        if (calc(mid, nopt) <= calc(mid, opt))
            res = mid, r = mid - 1;
        else
            l = mid + 1;
    }
    return res;
}
void getdp()
{
    q[hd = tl = 1] = {n, 0};
    for (int i = 1; i <= n; i++)
    {
        while (q[hd].r < i) hd++;
        int pos = n + 1;
        f[i] = calc(i, q[hd].opt), pre[i] = q[hd].opt;
        while (hd <= tl && calc(q[tl].r, i) <= calc(q[tl].r, q[tl].opt))
        {
            if (calc(q[tl - 1].r + 1, q[tl].opt) < calc(q[tl - 1].r + 1, i))
                pos = bound(tl, i), q[tl].r = pos - 1;
            else
                pos = q[--tl].r + 1;
        }
        if (pos <= n) q[++tl] = {n, i};
    }
}
void print(int p)
{
    if (!p) return;
    print(pre[p]);
    for (int i = pre[p] + 1; i <= p; i++) cout << str[i] << " \n"[i == p];
}
void solve()
{
    cin >> n >> L >> p, cin.ignore();
    for (int i = 1; i <= n; i++) getline(cin, str[i]), s[i] = s[i - 1] + str[i].size() + 1;
    getdp();
    if (f[n] > 1e18) return cout << fail << endl
                                 << sep << endl,
                            void();
    cout << (long long)(f[n]) << endl;
    print(n), cout << sep << endl;
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}