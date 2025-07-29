#include <bits/stdc++.h>
using namespace std;
const int MAXN = 50005;
struct node
{
    int x, y, z;
    int dp;
    double f;
} a[MAXN];
int n;
int tr1[MAXN];
double tr2[MAXN];
int dp1[MAXN], dp2[MAXN];
double f1[MAXN], f2[MAXN];
bool cmp1(node i, node j)
{
    return i.x == j.x ? (i.y == j.y ? i.z < j.z : i.y > j.y) : i.x > j.x;
}
bool cmp2(node i, node j)
{
    return i.x == j.x ? (i.y == j.y ? i.z < j.z : i.y < j.y) : i.x < j.x;
}
bool cmp3(node i, node j)
{
    return i.y > j.y;
}
bool cmp4(node i, node j)
{
    return i.y < j.y;
}
int lowbit(int x)
{
    return x & -x;
}
void update(int x, int dp, double f)
{
    while (x <= n)
    {
        if (tr1[x] < dp)
        {
            tr1[x] = dp;
            tr2[x] = f;
        }
        else if (tr1[x] == dp)
            tr2[x] += f;
        x += lowbit(x);
    }
    return;
}
int query1(int x)
{
    int ans = 0;
    while (x)
    {
        ans = max(ans, tr1[x]);
        x -= lowbit(x);
    }
    return ans;
}
double query2(int x, int dp)
{
    double ans = 0;
    while (x)
    {
        if (tr1[x] == dp)
            ans += tr2[x];
        x -= lowbit(x);
    }
    return ans;
}
void del(int x)
{
    while (x <= n)
    {
        tr1[x] = tr2[x] = 0;
        x += lowbit(x);
    }
    return;
}
bool check(int p, int q, int opt)
{
    if (opt == 1)
        return a[p].y >= a[q].y;
    return a[p].y <= a[q].y;
}
void merge_sort(int l, int r, int opt)
{
    int mid = (l + r) >> 1;
    int p = l, q = mid + 1;
    while (p <= mid && q <= r)
    {
        if (check(p, q, opt))
        {
            update(a[p].z, a[p].dp, a[p].f);
            p++;
        }
        else
        {
            int val = query1(a[q].z) + 1;
            if (a[q].dp < val)
            {
                a[q].dp = val;
                a[q].f = query2(a[q].z, val - 1);
            }
            else if (a[q].dp == val)
                a[q].f += query2(a[q].z, val - 1);
            q++;
        }
    }
    while (q <= r)
    {
        int val = query1(a[q].z) + 1;
        if (a[q].dp < val)
        {
            a[q].dp = val;
            a[q].f = query2(a[q].z, val - 1);
        }
        else if (a[q].dp == val)
            a[q].f += query2(a[q].z, val - 1);
        q++;
    }
    for (int i = l; i < p; i++)
        del(a[i].z);
    return;
}
void solve(int l, int r, int opt)
{
    if (l == r)
        return;
    int mid = l + ((r - l) >> 1);
    solve(l, mid, opt);
    if (opt == 1)
    {
        sort(a + l, a + mid + 1, cmp3);
        sort(a + mid + 1, a + r + 1, cmp3);
    }
    else
    {
        sort(a + l, a + mid + 1, cmp4);
        sort(a + mid + 1, a + r + 1, cmp4);
    }
    merge_sort(l, r, opt);
    if (opt == 1)
        sort(a + mid + 1, a + r + 1, cmp1);
    else
        sort(a + mid + 1, a + r + 1, cmp2);
    solve(mid + 1, r, opt);
    return;
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i].x >> a[i].y;
        a[i].z = i;
        a[i].dp = 1;
        a[i].f = 1;
    }
    sort(a + 1, a + n + 1, cmp1);
    solve(1, n, 1);
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        dp1[a[i].z] = a[i].dp;
        f1[a[i].z] = a[i].f;
        ans = max(ans, dp1[a[i].z]);
    }
    cout << ans << endl;
    for (int i = 1; i <= n; i++)
    {
        a[i].z = n - a[i].z + 1;
        a[i].dp = 1;
        a[i].f = 1;
    }
    sort(a + 1, a + n + 1, cmp2);
    solve(1, n, 2);
    double k = 0;
    for (int i = 1; i <= n; i++)
    {
        dp2[n - a[i].z + 1] = a[i].dp;
        f2[n - a[i].z + 1] = a[i].f;
        if (dp2[n - a[i].z + 1] == ans)
            k += f2[n - a[i].z + 1];
    }
    cout << fixed << setprecision(5);
    for (int i = 1; i <= n; i++)
    {
        if (dp1[i] + dp2[i] == ans + 1)
            cout << f1[i] * f2[i] / k << ' ';
        else
            cout << 0 << " ";
    }
    return 0;
}