#include <bits/stdc++.h>
using namespace std;
#define mod 298999
#define int long long
int n, m;
int lst, now;             // 滚动
int head[300000], cnt[2]; // 滚动的总合法方案数
bool mp[15][15];
// 0 1 2 没有插头 左括号 右括号
struct HashTable
{
    int sta[2], dp[2], nxt;
} Hash[300000];
void insert(int sta, int val)
{
    int key = sta % mod;
    for (int i = head[key]; i; i = Hash[i].nxt)
        if (sta == Hash[i].sta[now])
        {
            Hash[i].dp[now] += val;
            return;
        }
    ++cnt[now];
    Hash[cnt[now]].sta[now] = sta;
    Hash[cnt[now]].dp[now] = val;
    Hash[cnt[now]].nxt = head[key];
    head[key] = cnt[now];
};
struct node
{
    int s[15];
};
node unZip(int sta)
{ // 解压
    node code;
    code.s[0] = sta & 3; // 单独的竖直轮廓线
    for (int i = 1; i <= m; i++)
        code.s[i] = (sta >> (i << 1)) & 3;
    return code;
}
int Zip(node code)
{ // 压缩
    int sta = 0;
    for (int i = 1; i <= m; i++)
        sta |= (code.s[i] << (i << 1));
    sta |= code.s[0];
    return sta;
}
signed main()
{
    int ans = 0, Endx, Endy;
    scanf("%lld %lld", &n, &m);
    char ch[20];
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", ch + 1);
        for (int j = 1; j <= m; j++)
            if (ch[j] == '.')
                mp[i][j] = 1, Endx = i, Endy = j;
    }
    insert(0, 1);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            lst = now, now ^= 1, cnt[now] = 0;
            memset(head, 0, sizeof(head));
            for (int k = 1; k <= cnt[lst]; k++)
            {
                node code = unZip(Hash[k].sta[lst]);
                int Left = code.s[0], Up = code.s[j]; // 左插头 上插头 0 1 2 没有插头 左括号 右括号
                int dp = Hash[k].dp[lst];
                if (!mp[i][j])
                {
                    if (!Left && !Up)
                        insert(Zip(code), dp);
                }
                else if (!Left && !Up)
                {
                    if (mp[i + 1][j] && mp[i][j + 1])
                    {
                        code.s[0] = 2, code.s[j] = 1;
                        insert(Zip(code), dp);
                    }
                }
                else if (!Left && Up)
                {
                    if (mp[i + 1][j])
                        insert(Zip(code), dp);
                    if (mp[i][j + 1])
                    {
                        code.s[0] = Up, code.s[j] = 0;
                        insert(Zip(code), dp);
                    }
                }
                else if (Left && !Up)
                {
                    if (mp[i][j + 1])
                        insert(Zip(code), dp);
                    if (mp[i + 1][j])
                    {
                        code.s[0] = 0, code.s[j] = Left;
                        insert(Zip(code), dp);
                    }
                }
                else if (Left == 1 && Up == 1)
                {
                    // 不属于同一个连通块 都是左括号
                    // 得连起来 然后与这两个左括号匹配的右括号中较近的一个改成左括号 方法使用括号匹配
                    // 显然肯定是左插头的匹配括号在右 呈包含关系
                    int p, tot = 1;
                    for (p = j + 1; p <= m; p++)
                    {
                        if (code.s[p] == 1)
                            tot++;
                        if (code.s[p] == 2)
                            tot--;
                        if (!tot)
                            break;
                    }
                    code.s[0] = code.s[j] = 0, code.s[p] = 1;
                    insert(Zip(code), dp);
                }
                else if (Left == 2 && Up == 2)
                {
                    // 显然肯定是上插头的匹配括号在左 呈包含关系
                    int p, tot = -1;
                    for (p = j - 1; p; p--)
                    {
                        if (code.s[p] == 1)
                            tot++;
                        if (code.s[p] == 2)
                            tot--;
                        if (!tot)
                            break;
                    }
                    code.s[0] = code.s[j] = 0, code.s[p] = 2;
                    insert(Zip(code), dp);
                }
                else if (Left == 2 && Up == 1)
                {
                    code.s[0] = code.s[j] = 0;
                    insert(Zip(code), dp);
                }
                else if (Left == 1 && Up == 2)
                { // 回路形成
                    code.s[0] = code.s[j] = 0;
                    bool flag = 0; // 判断是否合法
                    for (int p = 0; p <= m && !flag; p++)
                        if (code.s[i])
                            flag = 1;
                    if (!flag && i == Endx && j == Endy)
                        ans += dp;
                }
            }
        }
    }
    printf("%lld\n", ans);
    return 0;
}
