#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const int MAXN = 1e6 + 10;
priority_queue<ll> pq;
int n;
ll a[MAXN], b[MAXN], ans;
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], a[i] -= i;
    for (int i = 1; i <= n; i++)
    {
        pq.emplace(a[i]), pq.emplace(a[i]);
        ans += pq.top() - a[i];
        pq.pop();
        b[i] = pq.top();
    }
    cout << ans << endl;
    for (int i = n - 1; i; i--) b[i] = min(b[i], b[i + 1]);
    for (int i = 1; i <= n; i++) cout << b[i] + i << " ";
    return 0;
}