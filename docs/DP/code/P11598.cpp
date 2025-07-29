#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
priority_queue<ll> pqmx;
priority_queue<ll, vector<ll>, greater<>> pqmn;
int n;
ll h, x, lt, rt, res;
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> h;
    while (n--)
    {
        cin >> x;
        lt += h;
        rt += h;
        pqmx.emplace(x + lt);
        pqmn.emplace(x - rt);
        auto l = pqmx.top() - lt;
        auto r = pqmn.top() + rt;
        while (l > r)
        {
            pqmx.pop();
            pqmn.pop();
            res += l - r;
            pqmx.emplace(r + lt);
            pqmn.emplace(l - rt);
            l = pqmx.top() - lt;
            r = pqmn.top() + rt;
        }
    }
    cout << res << endl;
    return 0;
}