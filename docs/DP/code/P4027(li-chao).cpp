#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long double ld;
const int MAXN = 1e5 + 10;
#define mid ((l + r) >> 1)
#define ls ((x) << 1)
#define rs ((x) << 1 | 1)
inline void chkmx(ld &a, ld b) { a = a < b ? b : a; }
ld X[MAXN], Y[MAXN], a[MAXN], b[MAXN], r[MAXN], tx[MAXN], lsh[MAXN], f, g;
int tr[MAXN << 2], n, tot;
ld gety(int k, int v) { return X[k] * lsh[v] + Y[k]; }
void update(int x, int l, int r, int id1)
{
    int &id2 = tr[x];
    if (gety(id1, mid) > gety(id2, mid))
        swap(id1, id2);
    if (gety(id1, l) > gety(id2, l))
        update(ls, l, mid, id1);
    if (gety(id1, r) > gety(id2, r))
        update(rs, mid + 1, r, id1);
}
ld query(int x, int l, int r, int p)
{
    ld res = gety(tr[x], p);
    if (l == r)
        return res;
    if (p <= mid)
        chkmx(res, query(ls, l, mid, p));
    else
        chkmx(res, query(rs, mid + 1, r, p));
    return res;
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> f;
    for (int i = 1; i <= n; i++)
        cin >> a[i] >> b[i] >> r[i], lsh[i] = tx[i] = a[i] / b[i];
    sort(lsh + 1, lsh + 1 + n);
    tot = unique(lsh + 1, lsh + 1 + n) - lsh - 1;
    for (int i = 1; i <= n; i++)
    {
        int pos = lower_bound(lsh + 1, lsh + 1 + tot, tx[i]) - lsh;
        chkmx(f, b[i] * query(1, 1, tot, pos));
        g = a[i] * r[i] + b[i], X[i] = f * r[i] / g, Y[i] = f / g;
        update(1, 1, tot, i);
    }
    cout << fixed << setprecision(3) << f;
    return 0;
}