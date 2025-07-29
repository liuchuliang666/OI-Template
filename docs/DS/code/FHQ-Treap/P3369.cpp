#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    int x = 0, f = 1;
    char ch;
    for (ch = getchar(); !isdigit(ch); ch = getchar())
        if (ch == '-')
            f = -1;
    for (; isdigit(ch); ch = getchar())
    {
        x = (x << 3) + (x << 1) + (ch - '0');
    }
    return f * x;
}
inline void write(int x)
{
    if (x < 0)
    {
        putchar('-');
        x = -x;
    }
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
    return;
}
const int MAXN = 1e5 + 10;
mt19937 rnd(time(0));
class FHQ_Treap
{
    int rt, idx, siz[MAXN], ls[MAXN], rs[MAXN], rd[MAXN], val[MAXN];
    inline int newnode(int v = 0)
    {
        siz[++idx] = 1;
        ls[idx] = rs[idx] = 0;
        rd[idx] = rnd();
        val[idx] = v;
        return idx;
    }
    inline void update(int x) { siz[x] = siz[ls[x]] + siz[rs[x]] + 1; }
    void split(int u, int v, int &x, int &y)
    {
        if (!u)
        {
            x = y = 0;
            return;
        }
        if (v < val[u])
        {
            y = u;
            split(ls[u], v, x, ls[y]);
        }
        else
        {
            x = u;
            split(rs[u], v, rs[x], y);
        }
        update(u);
    }
    int merge(int x, int y)
    {
        if (!x || !y)
            return x + y;
        if (rd[x] <= rd[y])
        {
            rs[x] = merge(rs[x], y);
            update(x);
            return x;
        }
        else
        {
            ls[y] = merge(x, ls[y]);
            update(y);
            return y;
        }
        return 0;
    }
    int qry_by_rnk(int u, int rk)
    {
        while (siz[ls[u]] + 1 != rk)
            if (rk <= siz[ls[u]])
                u = ls[u];
            else
                rk -= siz[ls[u]] + 1, u = rs[u];
        return u;
    }

public:
    FHQ_Treap() : idx(0), rt(0) {}
    inline void insert(int v)
    {
        int x, y;
        split(rt, v - 1, x, y);
        rt = merge(merge(x, newnode(v)), y);
    }
    inline void remove(int v)
    {
        int x, y, z;
        split(rt, v - 1, x, y);
        split(y, v, y, z);
        rt = merge(merge(x, merge(ls[y], rs[y])), z);
    }
    inline int rank(int v)
    {
        int x, y;
        split(rt, v - 1, x, y);
        int ret = siz[x] + 1;
        rt = merge(x, y);
        return ret;
    }
    inline int query_rank(int rk) { return val[qry_by_rnk(rt, rk)]; }
    inline int less(int v)
    {
        int x, y;
        split(rt, v - 1, x, y);
        int ret = qry_by_rnk(x, siz[x]);
        rt = merge(x, y);
        return val[ret];
    }
    inline int more(int v)
    {
        int x, y;
        split(rt, v, x, y);
        int ret = qry_by_rnk(y, 1);
        rt = merge(x, y);
        return val[ret];
    }
} treap;
int main()
{
    int n = read();
    while (n--)
    {
        switch (read())
        {
        case 1:
            treap.insert(read());
            break;
        case 2:
            treap.remove(read());
            break;
        case 3:
            write(treap.rank(read()));
            puts("");
            break;
        case 4:
            write(treap.query_rank(read()));
            puts("");
            break;
        case 5:
            write(treap.less(read()));
            puts("");
            break;
        case 6:
            write(treap.more(read()));
            puts("");
            break;
        }
    }
    return 0;
}