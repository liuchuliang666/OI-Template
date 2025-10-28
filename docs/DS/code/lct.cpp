#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long
const int N = 3e5 + 5;
struct node
{
    int fa, son[2], sum, val, tag;
} t[N];
#define ls t[x].son[0]
#define rs t[x].son[1]
bool isrt(int x)
{
    int g = t[x].fa;
    return t[g].son[0] != x && t[g].son[1] != x;
}
void pu(int x) { t[x].sum = t[x].val ^ t[ls].sum ^ t[rs].sum; }
void reverse(int x)
{
    if (!x) return;
    swap(ls, rs);
    t[x].tag ^= 1;
}
void pd(int x)
{
    if (t[x].tag)
    {
        reverse(ls);
        reverse(rs);
        t[x].tag = 0;
    }
}
void update(int x)
{
    if (!isrt(x)) update(t[x].fa);
    pd(x);
}
void rotate(int x)
{
    int y = t[x].fa;
    int z = t[y].fa;
    int k = (t[y].son[1] == x);
    if (!isrt(y)) t[z].son[t[z].son[1] == y] = x;
    t[x].fa = z;
    t[y].son[k] = t[x].son[k ^ 1];
    if (t[x].son[k ^ 1]) t[t[x].son[k ^ 1]].fa = y;
    t[y].fa = x;
    t[x].son[k ^ 1] = y;
    pu(y);
}
void splay(int x)
{
    int y, z;
    update(x);
    while (!isrt(x))
    {
        y = t[x].fa, z = t[y].fa;
        if (!isrt(y))
        {
            if ((t[z].son[0] == y) ^ (t[y].son[0] == x))
                rotate(x);
            else
                rotate(y);
        }
        rotate(x);
    }
    pu(x);
}
void access(int x)
{
    for (int s = 0; x; s = x, x = t[x].fa)
    {
        splay(x);
        rs = s;
        pu(x);
    }
}
void makert(int x)
{
    access(x);
    splay(x);
    reverse(x);
}
void split(int x, int y)
{
    makert(x);
    access(y);
    splay(y);
}
void link(int x, int y)
{
    makert(x);
    t[x].fa = y;
}
void cut(int x, int y)
{
    split(x, y);
    if (t[y].son[0] != x || rs) return;
    t[x].fa = t[y].son[0] = 0;
    pu(x);
}
int findrt(int x)
{
    access(x);
    splay(x);
    while (ls) update(x), x = ls;
    return x;
}
signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> t[i].val;
        t[i].sum = t[i].val;
    }
    while (m--)
    {
        int opt, a, b;
        cin >> opt >> a >> b;
        if (opt == 0)
        {
            split(a, b);
            cout << t[b].sum << endl;
        }
        if (opt == 1)
            if (findrt(a) != findrt(b)) link(a, b);
        if (opt == 2) cut(a, b);
        if (opt == 3) splay(a), t[a].val = b;
    }
    return 0;
}