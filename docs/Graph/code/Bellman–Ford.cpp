#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define eb emplace_back
#define ep emplace
#define fi first
#define se second
#define int ll
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
constexpr int MAXN = 2e5 + 10;
vector<tuple<int, int, int>> e;
int dis[MAXN];
constexpr int inf = 0x3f3f3f3f;
bool bellmanford(int n, int s)
{
    memset(dis, 0x3f, (n + 1) * sizeof(int));
    dis[s] = 0;
    bool flag = 0; // 判断一轮循环过程中是否发生松弛操作
    for (int i = 1; i <= n; i++)
    {
        flag = 0;
        for (auto [u, v, w] : e)
        {
            if (dis[u] == inf) continue;
            // 无穷大与常数加减仍然为无穷大
            // 因此最短路长度为 inf 的点引出的边不可能发生松弛操作
            if (dis[v] > dis[u] + w)
            {
                dis[v] = dis[u] + w;
                flag = true;
            }
        }
        // 没有可以松弛的边时就停止算法
        if (!flag) break;
    }
    // 第 n 轮循环仍然可以松弛时说明 s 点可以抵达一个负环
    return flag;
}
signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    return 0;
}