#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
const int MAXN = 1e5 + 10;
int id, rt;
int fa[MAXN], val[MAXN], cnt[MAXN], siz[MAXN], ch[MAXN][2];
#define ls(x) ch[x][0]
#define rs(x) ch[x][1]
bool dir(int x) { return rs(fa[x]) == x; }
void pu(int x) { siz[x] = siz[ls(x)] + siz[rs(x)] + cnt[x]; }
void rotate(int x)
{
    int y = fa[x], z = fa[y];
    bool r = dir(x);
    ch[y][r] = ch[x][!r];
    ch[x][!r] = y;
    if (z) ch[z][dir(y)] = x;
    if (ch[y][r]) fa[ch[y][r]] = y;
    fa[y] = x;
    fa[x] = z;
    pu(y);
    pu(x);
}
void splay(int &z, int x)
{
    int w = fa[z];
    for (int y; (y = fa[x]) != w; rotate(x))
        if (fa[y] != w) rotate(dir(x) == dir(y) ? y : x);
    z = x;
}
void find(int &z, int v)
{
    int x = z, y = fa[x];
    while (x && val[x] != v) x = ch[y = x][v > val[x]];
    splay(z, x ? x : y);
}
void loc(int &z, int k)
{
    int x = z;
    while (1)
    {
        if (siz[ls(x)] >= k)
            x = ls(x);
        else if (siz[ls(x)] + cnt[x] >= k)
        {
            break;
        }
        else
        {
            k -= siz[ls(x)] + cnt[x];
            x = rs(x);
        }
    }
    splay(z, x);
}
int merge(int x, int y)
{
    if (!x || !y) return x | y;
    loc(y, 1);
    ls(y) = x;
    fa[x] = y;
    pu(y);
    return y;
}
void insert(int v)
{
    int x = rt, y = 0;
    while (x && val[x] != v) x = ch[y = x][v > val[x]];
    if (x)
        cnt[x]++, siz[x]++;
    else
    {
        x = ++id;
        val[x] = v;
        cnt[x] = siz[x] = 1;
        fa[x] = y;
        if (y) ch[y][v > val[y]] = x;
    }
    splay(rt, x);
}
bool remove(int v)
{
    find(rt, v);
    if (!rt || val[rt] != v) return false;
    cnt[rt]--;
    siz[rt]--;
    if (!cnt[rt])
    {
        int x = ls(rt), y = rs(rt);
        fa[x] = fa[y] = 0;
        rt = merge(x, y);
    }
    return true;
}
int findrank(int v)
{
    find(rt, v);
    return siz[ch[rt][0]] + (val[rt] < v) * cnt[rt] + 1;
}
int findkth(int k)
{
    if (k > siz[rt]) return -1;
    loc(rt, k);
    return val[rt];
}
int findprev(int v)
{
    find(rt, v);
    if (rt && val[rt] < v) return val[rt];
    int x = ls(rt);
    if (!x) return -1;
    while (rs(x)) x = rs(x);
    splay(rt, x);
    return val[rt];
}
int findnext(int v)
{
    find(rt, v);
    if (rt && val[rt] > v) return val[rt];
    int x = rs(rt);
    if (!x) return -1;
    while (ls(x)) x = ls(x);
    splay(rt, x);
    return val[rt];
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, op, x;
    cin >> n;
    while (n--)
    {
        cin >> op >> x;
        switch (op)
        {
            case 1:
                insert(x);
                break;
            case 2:
                remove(x);
                break;
            case 3:
                cout << findrank(x) << endl;
                break;
            case 4:
                cout << findkth(x) << endl;
                break;
            case 5:
                cout << findprev(x) << endl;
                break;
            case 6:
                cout << findnext(x) << endl;
                break;
        }
    }
    return 0;
}