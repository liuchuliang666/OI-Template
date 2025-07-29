#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 5e4 + 8;
int n;
bool vis[MAXN];
int que[MAXN], head, tail;
ll f[MAXN];
struct node
{
    int w, l;
    bool operator<(const node &x) const
    {
        if (w == x.w)
            return l < x.l;
        return w < x.w;
    }
} a[MAXN];
double X(int i) { return -a[i].l; }
double Y(int i) { return f[i - 1]; }
double K(int i) { return a[i].w; }
double slope(int i, int j) { return (Y(i) - Y(j)) / (X(i) - X(j)); }
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i].w >> a[i].l;
    sort(a + 1, a + 1 + n);
    int mx = 0;
    for (int i = n; i >= 1; i--)
    {
        if (a[i].l <= mx)
            vis[i] = 1;
        mx = max(mx, a[i].l);
    }
    int idx = 0;
    for (int i = 1; i <= n; i++)
        if (!vis[i])
            a[++idx] = a[i];
    n = idx;
    head = 1;
    tail = 0;
    que[++tail] = 1;
    for (int i = 1; i <= n; i++)
    {
        while (head < tail && slope(que[head], que[head + 1]) < K(i))
            ++head;
        int j = que[head];
        f[i] = f[j - 1] + 1ll * a[j].l * a[i].w;
        while (head < tail && slope(que[tail], que[tail - 1]) > slope(que[tail], i + 1))
            --tail;
        que[++tail] = i + 1;
    }
    cout << f[n];
    return 0;
}