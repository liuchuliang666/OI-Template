#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const int MAXN = 1e6 + 10;
priority_queue<ll> pq;
int n;
ll a, ans;
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a;
        pq.emplace(-a), pq.emplace(-a);
        ans += a + pq.top();
        pq.pop();
    }
    cout << ans;
    return 0;
}