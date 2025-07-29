#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
int main()
{
    int n;
    ll x, y, z;
    cin >> n >> x >> y >> z;
    stack<ll> neg, pos;
    ll lt = 0, rt = 0;
    ll res = 0;
    for (; n; --n)
    {
        int a, b;
        cin >> a >> b;
        lt -= z;
        rt += z;
        for (; b < a; ++b)
        {
            auto l = -y;
            if (!neg.empty())
            {
                l = max(l, neg.top() + lt);
                neg.pop();
            }
            pos.emplace(l - rt);
            res -= l;
        }
        for (; b > a; --b)
        {
            auto r = x;
            if (!pos.empty())
            {
                r = min(r, pos.top() + rt);
                pos.pop();
            }
            neg.emplace(r - lt);
            res += r;
        }
    }
    cout << res << endl;
    return 0;
}