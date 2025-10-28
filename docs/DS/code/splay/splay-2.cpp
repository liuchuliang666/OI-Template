#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ls(x) ch[x][0]
#define rs(x) ch[x][1]
const int MAXN = 1e5 + 10;
int id, rt;
int fa[MAXN], val[MAXN], siz[MAXN], lazy[MAXN], ch[MAXN][2];
bool dir(int x) { return x == rs(fa[x]); }
void pu(int x) { siz[x] = 1 + siz[ls(x)] + siz[rs(x)]; }
void lazyreverse(int x)
{
    swap(ls(x), rs(x));
    lazy[x] ^= 1;
}
void pd(int x)
{
    if (lazy[x])
    {
        if (ls(x)) lazyreverse(ls(x));
        if (rs(x)) lazyreverse(rs(x));
        lazy[x] = 0;
    }
}
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
void loc(int &z, int k)
{
    int x = z;
    for (pd(x); siz[ls(x)] != k - 1; pd(x))
    {
        if (siz[ls(x)] >= k)
            x = ls(x);
        else
        {
            k -= siz[ls(x)] + 1;
            x = rs(x);
        }
    }
    splay(z, x);
}
void build(int n)
{
    for (int i = 1; i <= n + 2; ++i)
    {
        ++id;
        ls(id) = rt;
        if (rt) fa[rt] = id;
        rt = id;
        val[id] = i - 1;
    }
    splay(rt, 1);
}
void reverse(int l, int r)
{
    loc(rt, l);
    loc(rs(rt), r - l + 2);
    int x = ls(rs(rt));
    lazyreverse(x);
    pd(x);
    splay(rt, x);
}
void print(int x)
{
    if (!x) return;
    pd(x);
    print(ls(x));
    cout << val[x] << ' ';
    print(rs(x));
}
void print()
{
    loc(rt, 1);
    loc(rs(rt), siz[rt] - 1);
    print(ch[rs(rt)][0]);
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, m;
    cin >> n >> m;
    build(n);
    while (m--)
    {
        int l, r;
        cin >> l >> r;
        reverse(l, r);
    }
    print();
    return 0;
}