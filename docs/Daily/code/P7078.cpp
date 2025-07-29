#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 10;
typedef pair<int, int> pii;
int a[MAXN], n, ans, x, id, y;
list<pii> q1, q2;
pii now;
bool chk() // 模拟二阶段判断能不能吃
{
    int cnt = 0; // 二阶段进行的局数
    while (1)
    {
        cnt++;                          // 安全！
        if (q1.size() + q2.size() == 1) // 吃完了，结束
            break;
        if (q2.empty() || !q1.empty() && q1.back() > q2.back()) // 取最强的
            x = q1.back().first, id = q1.back().second, q1.pop_back();
        else
            x = q2.back().first, id = q2.back().second, q2.pop_back();
        now = {x - now.first, id};                                                   // 吃！
        if (!((q1.empty() || now < q1.front()) && (q2.empty() || now < q2.front()))) // 下一条蛇安全，那么自己就会被吃，退出
            break;
    }
    // cnt 是奇数，危险！
    return !(cnt & 1);
}
void solve()
{
    q1.clear(), q2.clear();
    for (int i = 1; i <= n; i++)
        q1.push_back({a[i], i});
    while (1)
    {
        if (q1.size() + q2.size() == 2) // 剩俩蛇
        {
            ans = 1;
            break;
        }
        y = q1.front().first, q1.pop_front(); // 取最弱的
        if (q2.empty() || !q1.empty() && q1.back() > q2.back())
            x = q1.back().first, id = q1.back().second, q1.pop_back(); // 取最强的
        else
            x = q2.back().first, id = q2.back().second, q2.pop_back();
        now = {x - y, id};                  // 吃！
        if (q1.empty() || q1.front() > now) // 自己变成最弱的了，进入二阶段
        {
            ans = q1.size() + q2.size() + 2 - chk();
            break;
        }
        else // 安全！
            q2.push_front(now);
    }
    cout << ans << endl;
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    for (int tid = 1, k, x, y; tid <= T; tid++)
    {
        if (tid == 1)
        {
            cin >> n;
            for (int i = 1; i <= n; i++)
                cin >> a[i];
        }
        else
        {
            cin >> k;
            while (k--)
            {
                cin >> x >> y;
                a[x] = y;
            }
        }
        solve();
    }
    return 0;
}