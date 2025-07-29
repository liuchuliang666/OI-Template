#include <bits/stdc++.h>
using namespace std;
const int MAXN = 6e5 + 10;
typedef long long ll;
#define endl '\n'
string s;
int n, q, tot;
struct line
{
    int l, r;
    line(int a = 0, int b = 0) : l(a), r(b) {}
    inline bool operator<(const line &tmp) const { return l < tmp.l; }
};
set<line> odt;
set<line>::iterator ita, itb;
struct node
{
    int x, y, id, v;
    node(int a = 0, int b = 0, int c = 0, int d = 0) : x(a), y(b), id(c), v(d) {}
} d[MAXN << 2];
int t[MAXN];
inline int lowbit(const int x) { return x & (-x); }
inline void add(int x, int v)
{
    while (x <= n + 1) t[x] += v, x += lowbit(x);
}
inline int ask(int x)
{
    int res = 0;
    while (x) res += t[x], x -= lowbit(x);
    return res;
}
inline bool cmp(node a, node b)
{
    if (a.x != b.x) return a.x < b.x;
    return a.y != b.y ? a.y < b.y : a.id < b.id;
}
int ans[MAXN];
void solve(int l, int r)
{
    if (l == r) return;
    int mid = (l + r) >> 1;
    solve(l, mid);
    solve(mid + 1, r);
    int i = l, j = mid + 1, p = l - 1;
    while (i <= mid && j <= r)
    {
        if (cmp(d[i], d[j]))
        {
            if (!d[i].id) add(d[i].y, d[i].v);
            i++;
            continue;
        }
        if (d[j].id) ans[d[j].id] += ask(d[j].y);
        j++;
    }
    for (; j <= r; j++)
        if (d[j].id) ans[d[j].id] += ask(d[j].y);
    for (int k = l; k < i; k++)
        if (!d[k].id) add(d[k].y, -d[k].v);
    inplace_merge(d + l, d + mid + 1, d + r + 1, cmp);
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> q;
    cin >> s;
    s = " " + s;
    odt.insert(line(0, 0));
    odt.insert(line(n + 1, n + 1));
    for (int i = 1; i <= n; i++)
    {
        if (s[i] == '0') continue;
        int R = i;
        while (s[R + 1] == '1') R++;
        odt.insert(line(i, R));
        i = R;
    }
    string ch;
    int a, b, cnt = 0;
    for (int i = 1; i <= q; i++)
    {
        cin >> ch >> a;
        if (ch[0] == 'q')
        {
            cin >> b;
            d[++tot] = node(a, b, ++cnt, 0);
            ita = prev(odt.lower_bound(line(a + 1, 0)));
            itb = prev(odt.lower_bound(line(b, 0)));
            if (ita == itb && ita->r >= b - 1) ans[cnt] += i;
            continue;
        }
        if (s[a] == '0')
        {
            ita = odt.lower_bound(line(a + 1, 0));
            itb = prev(ita);
            line A = (*ita), B = (*itb);
            int l = a, r = a;
            if (B.r == l - 1 && B.l >= 1) l = B.l, odt.erase(B);
            if (A.l == r + 1 && A.r <= n) r = A.r, odt.erase(A);
            odt.insert(line(l, r));
            d[++tot] = node(l, a + 1, 0, -i);
            d[++tot] = node(a + 1, r + 2, 0, -i);
            d[++tot] = node(l, r + 2, 0, i);
            d[++tot] = node(a + 1, a, 0, i);
            s[a] = '1';
            continue;
        }
        ita = prev(odt.lower_bound(line(a + 1, 0)));
        line A = (*ita);
        odt.erase(A);
        if (A.l < a) odt.insert(line(A.l, a - 1));
        if (A.r > a) odt.insert(line(a + 1, A.r));
        d[++tot] = node(A.l, a + 1, 0, i);
        d[++tot] = node(a + 1, A.r + 2, 0, i);
        d[++tot] = node(A.l, A.r + 2, 0, -i);
        d[++tot] = node(a + 1, a, 0, -i);
        s[a] = '0';
    }
    solve(1, tot);
    for (int i = 1; i <= cnt; i++) cout << ans[i] << endl;
    return 0;
}