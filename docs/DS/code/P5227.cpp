#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 10, MAXM = 2e5 + 10;
#define mid ((l + r) >> 1)
#define ls ((x) << 1)
#define rs ((x) << 1 | 1)
struct edge
{
    int u, v;
} e[MAXM];
// x <- y
struct node
{
    int x, y;
    bool added;
} oper[MAXM];
vector<int> tr[MAXM << 2];
int f[MAXN], n, m, k, lst[MAXM], siz[MAXN], deep[MAXN], top, c;
inline int getf(int x)
{
    while (x != f[x]) x = f[x];
    return x;
}
inline void merge(int x, int y)
{
    x = getf(x), y = getf(y);
    if (x == y) return;
    if (deep[x] < deep[y]) swap(x, y);
    f[y] = x;
    siz[x] += siz[y];
    oper[++top] = {x, y, deep[x] == deep[y]};
    deep[x] += deep[x] == deep[y];
}
inline void backspace()
{
    auto [x, y, added] = oper[top--];
    f[y] = y;
    siz[x] -= siz[y];
    deep[x] -= added;
}
void update(int x, int l, int r, int pl, int pr, int v)
{
    if (pl <= l && r <= pr)
    {
        tr[x].push_back(v);
        return;
    }
    if (pl <= mid) update(ls, l, mid, pl, pr, v);
    if (mid < pr) update(rs, mid + 1, r, pl, pr, v);
}
void solve(int x, int l, int r)
{
    int ttop = top;
    bool yes = 0;
    for (int i : tr[x]) merge(e[i].u, e[i].v);
    if (siz[getf(1)] == n)
    {
        for (int i = l; i <= r; i++) cout << "Connected\n";
        yes = 1;
    }
    if (!yes)
        if (l == r)
            cout << "Disconnected\n";
        else
            solve(ls, l, mid), solve(rs, mid + 1, r);
    while (top != ttop) backspace();
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) deep[i] = siz[i] = 1, f[i] = i;
    for (int i = 1; i <= m; i++) cin >> e[i].u >> e[i].v;
    cin >> k;
    for (int i = 1; i <= k; i++)
    {
        int c, t;
        cin >> c;
        while (c--)
        {
            cin >> t;
            if (lst[t] != i - 1) update(1, 1, k, lst[t] + 1, i - 1, t);
            lst[t] = i;
        }
    }
    for (int i = 1; i <= m; i++)
        if (lst[i] != k) update(1, 1, k, lst[i] + 1, k, i);
    solve(1, 1, k);
    return 0;
}