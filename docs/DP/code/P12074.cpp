#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const int MAXN = 3e5 + 10;
ll x[MAXN];
int n, m;
void solve()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++) cin >> x[m - i + 1];
    ll val = 0;
    multiset<int, greater<>> s;
    for (int i = 1; i <= m; i++)
    {
        s.emplace(x[i] << 1);
        val -= x[i];
        if (i & 1) val += *s.begin(), s.erase(s.begin());
        while (s.size() >= (i & 1 ? (n + 1) >> 1 : (n + 2) >> 1)) s.erase(prev(s.end()));
    }
    ll ans = val;
    for (int v : s) val += v, ans = max(ans, val);
    cout << ans << endl;
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}