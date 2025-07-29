#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
const int MAXN = 100010;
int n, m, op, x, y;
int ls[MAXN], rs[MAXN], dist[MAXN], rt[MAXN];
bitset<MAXN> deled;
struct node
{
    int id, val;
    bool operator<(node x) const { return val == x.val ? id < x.id : val < x.val; }
} val[MAXN];
int getf(int x) { return rt[x] == x ? x : rt[x] = getf(rt[x]); }
int merge(int x, int y)
{
    if (!x || !y) return x | y;
    if (val[y] < val[x]) swap(x, y);
    rs[x] = merge(rs[x], y);
    if (dist[ls[x]] < dist[rs[x]]) swap(ls[x], rs[x]);
    dist[x] = dist[rs[x]] + 1;
    return x;
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> val[i].val, rt[i] = i, val[i].id = i;
    while (m--)
    {
        cin >> op >> x;
        if (op == 1)
        {
            cin >> y;
            if (deled[x] || deled[y]) continue;
            x = getf(x);
            y = getf(y);
            if (x != y) rt[x] = rt[y] = merge(x, y);
        }
        if (op == 2)
        {
            if (deled[x])
            {
                cout << -1 << endl;
                continue;
            }
            x = getf(x);
            cout << val[x].val << endl;
            deled[x] = true;
            rt[ls[x]] = rt[rs[x]] = rt[x] = merge(ls[x], rs[x]);
            ls[x] = rs[x] = dist[x] = 0;
        }
    }
    return 0;
}
void addtag(int x, int v);
void pushdown(int x);
void pushup(int x);
int mergeWithTag(int x, int y)
{
    if (!x || !y) return x | y;
    pushdown(x);
    if (val[y] < val[x]) swap(x, y);
    rs[x] = mergeWithTag(rs[x], y);
    if (dist[ls[x]] < dist[rs[x]]) swap(ls[x], rs[x]);
    pushup(x);
    dist[x] = dist[rs[x]] + 1;
    return x;
}
int pop(int x) { return pushdown(x), pushup(x = mergeWithTag(ls[x], rs[x])), x; }