#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int MAXN = 2e5 + 5;
const int MAXM = 1e6 + 5;
int n, k, m, tot;
struct BIT
{
    int bit[MAXN];
    inline int lowbit(int x) { return x & (-x); }
    inline void add(int x, int d)
    {
        for (; x <= k; x += lowbit(x)) bit[x] += d;
    }
    inline int query(int x)
    {
        int res = 0;
        for (; x; x -= lowbit(x)) res += bit[x];
        return res;
    }
} bit;
struct Node
{
    int a, b, c, cnt, ans;
} ss[MAXN], s[MAXN];
int ans[MAXN];
bool cmpA(Node a, Node b)
{
    if (a.a == b.a) return a.b == b.b ? a.c < b.c : a.b < b.b;
    return a.a < b.a;
}
bool cmpB(Node a, Node b) { return a.b == b.b ? a.c < b.c : a.b < b.b; }
void cdq(int l, int r)
{
    if (l >= r) return;
    int mid = l + r >> 1;
    cdq(l, mid);
    cdq(mid + 1, r);
    int i, j = l;
    for (i = mid + 1; i <= r; i++)
    {
        while (s[i].b >= s[j].b && j <= mid)
        {
            bit.add(s[j].c, s[j].cnt);
            j++;
        }
        s[i].ans += bit.query(s[i].c);
    }
    for (i = l; i < j; i++) bit.add(s[i].c, -s[i].cnt);
    inplace_merge(s + l, s + mid + 1, s + r + 1, cmpB);
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> ss[i].a >> ss[i].b >> ss[i].c;
    sort(ss + 1, ss + n + 1, cmpA);
    for (int i = 1; i <= n; i++)
    {
        tot++;
        if (i == n || ss[i].a != ss[i + 1].a || ss[i].b != ss[i + 1].b ||
            ss[i].c != ss[i + 1].c)
        {
            s[++m] = ss[i];
            s[m].cnt = tot;
            tot = 0;
        }
    }
    cdq(1, m);
    for (int i = 1; i <= m; i++) ans[s[i].cnt + s[i].ans - 1] += s[i].cnt;
    for (int i = 0; i < n; i++) cout << ans[i] << '\n';
    return 0;
}