#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
const int MAXN = 1e5 + 10, MAXV = MAXN << 2, MAXM = 2e5 + 10;
#define mid (((l) + (r)) >> 1)
#define ls ((x) << 1)
#define rs ((x) << 1 | 1)
struct edge
{
    int u, v;
} e[MAXM];
// fy -> fx
struct node
{
    int fx, fy;
    bool added;
};
vector<int> tr[MAXV];
stack<node> stk;
int f[MAXN * 2], h[MAXN * 2], n, m, k;
inline int getf(int x)
{
    while (x != f[x]) x = f[x];
    return x;
}
inline void merge(int x, int y)
{
    x = getf(x), y = getf(y);
    if (h[x] < h[y]) swap(x, y);
    f[y] = f[x];
    stk.push({x, y, h[y] == h[x]});
    if (h[y] == h[x]) h[x]++;
}
inline void del()
{
    auto [fx, fy, added] = stk.top();
    stk.pop();
    h[fx] -= added;
    f[fy] = fy;
}
void update(int x, int l, int r, int pl, int pr, int v)
{
    if (pl <= l && r <= pr) return tr[x].push_back(v);
    if (pl <= mid) update(ls, l, mid, pl, pr, v);
    if (mid < pr) update(rs, mid + 1, r, pl, pr, v);
    return;
}
void solve(int x, int l, int r)
{
    for (int i = 0; i < tr[x].size(); i++)
    {
        int u = e[tr[x][i]].u, v = e[tr[x][i]].v;
        int fu = getf(u), fv = getf(v);
        if (fu == fv)
        {
            for (int j = i; j; j--) del(), del();
            for (int i = l; i <= r; i++) cout << "No\n";
            return;
        }
        merge(u, v + n);
        merge(v, u + n);
    }
    if (l >= r)
        cout << "Yes\n";
    else
        solve(ls, l, mid), solve(rs, mid + 1, r);
    for (int i = tr[x].size(); i; i--) del(), del();
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m >> k;
    for (int i = 1; i <= n * 2; i++) f[i] = i, h[i] = 1;
    for (int l, r, i = 1; i <= m; i++)
    {
        cin >> e[i].u >> e[i].v >> l >> r;
        update(1, 1, k, l + 1, r, i);
    }
    solve(1, 1, k);
    return 0;
}