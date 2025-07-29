#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define mid ((l + r) >> 1)
typedef long long ll;
typedef double db;
const int MAXN = 1e5 + 10;
const db eps = 1e-8;
db f[MAXN];
int n, q[MAXN];
struct node
{
    db a, b, r, x, y, k;
    int w, id;
    inline bool operator<(const node &b) { return k > b.k; }
} p[MAXN], t[MAXN];
db slope(int j, int k)
{
    if (fabs(p[j].x - p[k].x) < eps)
        return 1e15;
    return (p[j].y - p[k].y) / (p[j].x - p[k].x);
}
void cdq(int l, int r)
{
    if (l == r)
    {
        f[l] = max(f[l], f[l - 1]);
        p[l].y = f[l] / (p[l].a * p[l].r + p[l].b);
        p[l].x = p[l].y * p[l].r;
        return;
    }
    int cur1 = l, cur2 = mid + 1, cur;
    for (int i = l; i <= r; i++)
        if (p[i].id > mid)
            t[cur2++] = p[i];
        else
            t[cur1++] = p[i];
    for (int i = l; i <= r; i++)
        p[i] = t[i];
    cdq(l, mid);
    cur1 = 1, cur2 = 0;
    for (int i = l; i <= mid; i++)
    {
        while (cur1 < cur2 && slope(q[cur2 - 1], q[cur2]) < slope(q[cur2], i) + eps)
            cur2--;
        q[++cur2] = i;
    }
    for (int i = mid + 1; i <= r; i++)
    {
        while (cur1 < cur2 && slope(q[cur1], q[cur1 + 1]) + eps > p[i].k)
            cur1++;
        int t = q[cur1];
        f[p[i].id] = max(f[p[i].id], p[i].a * p[t].x + p[i].b * p[t].y);
    }
    cdq(mid + 1, r);
    cur = cur1 = l, cur2 = mid + 1;
    while (cur1 <= mid && cur2 <= r)
        if (p[cur1].x < p[cur2].x + eps)
            t[cur++] = p[cur1++];
        else
            t[cur++] = p[cur2++];
    while (cur1 <= mid)
        t[cur++] = p[cur1++];
    while (cur2 <= r)
        t[cur++] = p[cur2++];
    for (int i = l; i <= r; i++)
        p[i] = t[i];
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> f[0];
    for (int i = 1; i <= n; i++)
        cin >> p[i].a >> p[i].b >> p[i].r, p[i].k = -p[i].a / p[i].b, p[i].id = i;
    sort(p + 1, p + 1 + n);
    cdq(1, n);
    cout << fixed << setprecision(3) << f[n];
    return 0;
}