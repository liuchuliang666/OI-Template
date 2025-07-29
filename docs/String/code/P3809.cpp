#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e6 + 5;
int n, m, rk[N << 1], oldrk[N], sa[N << 1], id[N], cnt[N], p;
string s;
void ssort()
{
    for (int i = 1; i <= n; i++) cnt[rk[i]]++;                 // 桶排
    for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];         // 求前缀和
    for (int i = n; i >= 1; i--) sa[cnt[rk[id[i]]]--] = id[i]; // 更新 sa
}
signed main()
{
    cin >> s;
    n = s.length();
    s = ' ' + s;
    m = 128;
    for (int i = 1; i <= n; i++) rk[i] = s[i], id[i] = i;
    ssort();
    for (int w = 1;; w <<= 1, m = p) // m 是字符个数，每次排完之后元素有了你新编号就可以改掉了
    {
        int cur = 0;
        for (int i = n - w + 1; i <= n; i++) id[++cur] = i; // 第二关键字为 0 的数先排
        for (int i = 1; i <= n; i++)
            if (sa[i] > w) id[++cur] = sa[i] - w;
        // 对于可以作为第二关键字的，由于目前 sa 数组已经排好，元素 (i, j) 一定排序后在元素 (i + 1, j + 1) 之前，可以直接加入
        memset(cnt, 0, sizeof(cnt));
        ssort();
        p = 0; // 排名
        memcpy(oldrk, rk, sizeof(oldrk));
        for (int i = 1; i <= n; i++) // 再一个一个比对双关键字
        {
            if (oldrk[sa[i]] == oldrk[sa[i - 1]] && oldrk[sa[i] + w] == oldrk[sa[i - 1] + w])
                rk[sa[i]] = p;
            else
                rk[sa[i]] = ++p;
        }
        if (p == n) break; // 全排完就好了
    }
    for (int i = 1; i <= n; i++) cout << sa[i] << ' ';
    return 0;
}
