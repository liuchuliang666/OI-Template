#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define mid ((l + r) >> 1)
typedef long long ll;
const int MAXN = 5e5 + 10;
inline void chkmx(int &a, int b) { a = a < b ? b : a; }
inline void chkmn(int &a, int b) { a = a > b ? b : a; }
inline void chkmx(ll &a, ll b) { a = a < b ? b : a; }
inline void chkmn(ll &a, ll b) { a = a > b ? b : a; }
int lstans, tr[MAXN][2], sum[MAXN], val[MAXN], lst[MAXN][2], rst[MAXN][2],
    b[MAXN], rt[MAXN], cnt, ls[MAXN], rs[MAXN], n, pl[2], pr[2];
void upd(int x)
{
    sum[x] = sum[ls[x]] + sum[rs[x]] + val[x];
    for (int k : {0, 1})
    {
        lst[x][k] = rst[x][k] = tr[x][k];
        if (ls[x])
        {
            chkmn(lst[x][k], lst[ls[x]][k]);
            chkmx(rst[x][k], rst[ls[x]][k]);
        }
        if (rs[x])
        {
            chkmn(lst[x][k], lst[rs[x]][k]);
            chkmx(rst[x][k], rst[rs[x]][k]);
        }
    }
}
int build(int l, int r, int k)
{
    nth_element(b + l, b + mid, b + r + 1,
                [&](int x, int y)
                { return tr[x][k] < tr[y][k]; });
    int x = b[mid];
    if (l < mid) ls[x] = build(l, mid - 1, k ^ 1);
    if (mid < r) rs[x] = build(mid + 1, r, k ^ 1);
    upd(x);
    return x;
}
void append(int &x)
{
    if (!x) return;
    b[++cnt] = x;
    append(ls[x]);
    append(rs[x]);
    x = 0;
}
bool covered(int x)
{
    for (int k : {0, 1})
        if (!(pl[k] <= lst[x][k] && rst[x][k] <= pr[k])) return false;
    return true;
}
bool check(int x)
{
    for (int k : {0, 1})
        if (pr[k] < lst[x][k] || rst[x][k] < pl[k]) return false;
    return true;
}
bool valid(int x)
{
    for (int k : {0, 1})
        if (!(pl[k] <= tr[x][k] && tr[x][k] <= pr[k])) return false;
    return true;
}
int qry(int x)
{
    if (!x || !check(x)) return 0;
    if (covered(x)) return sum[x];
    int res = 0;
    if (valid(x)) res += val[x];
    return res + qry(ls[x]) + qry(rs[x]);
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, op, x, y, a;
    cin >> n;
    n = 0;
    while (1)
    {
        cin >> op;
        switch (op)
        {
        case 1:
            cin >> x >> y >> a;
            x ^= lstans, y ^= lstans, a ^= lstans;
            val[++n] = a;
            tr[n][0] = x, tr[n][1] = y;
            b[cnt = 1] = n;
            for (int sz = 0;; sz++)
                if (!rt[sz])
                {
                    rt[sz] = build(1, cnt, 0);
                    break;
                }
                else
                    append(rt[sz]);
            break;
        case 2:
            cin >> pl[0] >> pl[1] >> pr[0] >> pr[1];
            pl[0] ^= lstans, pl[1] ^= lstans, pr[0] ^= lstans, pr[1] ^= lstans;
            lstans = 0;
            for (int i = 0; i < 25; i++) lstans += qry(rt[i]);
            cout << lstans << endl;
            break;
        case 3:
            return 0;
        }
    }
    return 0;
}