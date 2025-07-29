#include <iostream>
constexpr int MOD1 = 39989;
constexpr int MOD2 = 1000000000;
constexpr int MAXT = 40000;
#define mid ((l + r) >> 1)
#define ls ((x) << 1)
#define rs ((x) << 1 | 1)
using namespace std;
using pdi = pair<double, int>;
constexpr double eps = 1e-9;
int cmp(double x, double y)
{
    if (x - y > eps)
        return 1;
    if (y - x > eps)
        return -1;
    return 0;
}
struct line
{
    double k, b;
} p[100005];
int s[160005];
int cnt;
double calc(int id, int d) { return p[id].b + p[id].k * d; }
void add(int x0, int y0, int x1, int y1)
{
    cnt++;
    if (x0 == x1)
        p[cnt].k = 0, p[cnt].b = max(y0, y1);
    else
        p[cnt].k = 1.0 * (y1 - y0) / (x1 - x0), p[cnt].b = y0 - p[cnt].k * x0;
}
void upd(int x, int l, int r, int u)
{
    int &v = s[x];
    int bmid = cmp(calc(u, mid), calc(v, mid));
    if (bmid == 1 || (!bmid && u < v))
        swap(u, v);
    int bl = cmp(calc(u, l), calc(v, l)), br = cmp(calc(u, r), calc(v, r));
    if (bl == 1 || (!bl && u < v))
        upd(ls, l, mid, u);
    if (br == 1 || (!br && u < v))
        upd(rs, mid + 1, r, u);
}
void update(int x, int l, int r, int pl, int pr, int u)
{
    if (pl <= l && r <= pr)
    {
        upd(x, l, r, u);
        return;
    }
    if (pl <= mid)
        update(ls, l, mid, pl, pr, u);
    if (mid < pr)
        update(rs, mid + 1, r, pl, pr, u);
}
pdi pmax(pdi x, pdi y)
{
    if (cmp(x.first, y.first) == -1)
        return y;
    else if (cmp(x.first, y.first) == 1)
        return x;
    else
        return x.second < y.second ? x : y;
}
pdi query(int x, int l, int r, int d)
{
    if (r < d || d < l)
        return {0, 0};
    double res = calc(s[x], d);
    if (l == r)
        return {res, s[x]};
    return pmax({res, s[x]}, pmax(query(ls, l, mid, d), query(rs, mid + 1, r, d)));
}
int main()
{
    ios::sync_with_stdio(false);
    int n, lastans = 0;
    cin >> n;
    while (n--)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int x0, y0, x1, y1;
            cin >> x0 >> y0 >> x1 >> y1;
            x0 = (x0 + lastans - 1 + MOD1) % MOD1 + 1, x1 = (x1 + lastans - 1 + MOD1) % MOD1 + 1;
            y0 = (y0 + lastans - 1 + MOD2) % MOD2 + 1, y1 = (y1 + lastans - 1 + MOD2) % MOD2 + 1;
            if (x0 > x1)
                swap(x0, x1), swap(y0, y1);
            add(x0, y0, x1, y1);
            update(1, 1, MOD1, x0, x1, cnt);
        }
        else
        {
            int x;
            cin >> x;
            x = (x + lastans - 1 + MOD1) % MOD1 + 1;
            cout << (lastans = query(1, 1, MOD1, x).second) << endl;
        }
    }
    return 0;
}