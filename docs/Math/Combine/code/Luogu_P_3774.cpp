#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 5e4 + 5;
int n, m, a[N], ans[N << 2];
struct node
{
    int k, id;
};
vector<node> q[N];
int T[N];
int lowbit(int x) { return x & (-x); }
void add(int x, int y)
{
    while (x <= n)
    {
        T[x] += y;
        x += lowbit(x);
    }
}
int query(int x)
{
    int ans = 0;
    while (x)
    {
        ans += T[x];
        x -= lowbit(x);
    }
    return ans;
}
struct tang
{
    int n, sg, s[505], t[505][N];
    void Ins(int x, int v)
    {
        if (x > n) return;
        int l = 1, r = s[x] + 1;
        while (l < r)
        {
            int mid = (l + r) >> 1;
            if (sg ^ (t[x][mid] < v))
                r = mid;
            else
                l = mid + 1;
        }
        swap(t[x][l], v), s[x] = max(s[x], l);
        if (v)
            Ins(x + 1, v);
        else
        {
            if (sg && l > n)
                add(l, 1);
            else if (!sg)
                add(x, 1);
        }
    }
} M1, M2;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    M2.sg = 1, M1.n = M2.n = sqrt(n);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= m; i++)
    {
        int x, k;
        cin >> x >> k;
        q[x].push_back(node{k, i});
    }
    for (int i = 1; i <= n; i++)
    {
        M1.Ins(1, a[i]), M2.Ins(1, a[i]);
        if (q[i].size())
            for (auto v : q[i])
                ans[v.id] = query(v.k);
    }
    for (int i = 1; i <= m; i++) cout << ans[i] << '\n';
    return 0;
}