#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1e5 + 10;
int val[MAXN], siz[MAXN], ls[MAXN], rs[MAXN], rt, n, m, lazy[MAXN], rd[MAXN],
    idx;
mt19937 rnd(time(0));
inline void update(int x) { siz[x] = siz[ls[x]] + siz[rs[x]] + 1; }
inline void addtag(int x) { swap(ls[x], rs[x]), lazy[x] ^= 1; }
inline void pd(int x)
{
    if (lazy[x]) addtag(ls[x]), addtag(rs[x]), lazy[x] = 0;
}
inline int newnode(int v)
{
    val[++idx] = v;
    rd[idx] = rnd();
    siz[idx] = 1;
    return idx;
}
void split(int u, int v, int &x, int &y)
{
    if (!u)
    {
        x = y = 0;
        return;
    }
    pd(u);
    if (v < siz[ls[u]] + 1)
    {
        y = u;
        split(ls[u], v, x, ls[u]);
    }
    else
    {
        x = u;
        split(rs[u], v - siz[ls[u]] - 1, rs[u], y);
    }
    update(u);
}
int merge(int x, int y)
{
    if (!x || !y) return x | y;
    if (rd[x] <= rd[y])
    {
        pd(x);
        rs[x] = merge(rs[x], y);
        update(x);
        return x;
    }
    else
    {
        pd(y);
        ls[y] = merge(x, ls[y]);
        update(y);
        return y;
    }
}
void display(int x)
{
    if (!x) return;
    pd(x);
    display(ls[x]);
    cout << val[x] << " ";
    display(rs[x]);
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) rt = merge(rt, newnode(i));
    while (m--)
    {
        int x, y, z, l, r;
        cin >> l >> r;
        split(rt, r, y, z);
        split(y, l - 1, x, y);
        addtag(y);
        rt = merge(merge(x, y), z);
    }
    display(rt);
    return 0;
}