#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const int MAXN = 1e5 + 10;
class DSU
{
    int f[MAXN];
    int getf(const int x) { return f[x] = (f[x] == x ? x : getf(f[x])); }

public:
    void init(int n)
    {
        for (int i = 1; i <= n; i++) f[i] = i;
    }
    bool qry(const int x, const int y) { return getf(x) == getf(y); }
    void merge(int x, int y) { x = getf(x), y = getf(y), f[y] = x; }
} dsu;
struct edge
{
    int u, v, w, c;
} e[MAXN], e1[MAXN], e2[MAXN]; // e2 m2 -> c = 0
int ans, n, m, k, cnt, sum, m1, m2;
void kruskal()
{
    merge(e1 + 1, e1 + 1 + m1, e2 + 1, e2 + 1 + m2, e + 1, [](edge x, edge y)
          { return x.w == y.w ? x.c < y.c : x.w < y.w; });
    cnt = sum = 0;
    dsu.init(n);
    for (int now = 0, i = 1; i <= m && now < n - 1; i++)
    {
        auto [u, v, w, c] = e[i];
        if (dsu.qry(u, v)) continue;
        dsu.merge(u, v), now++, cnt += !c, sum += w;
    }
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m >> k;
    for (int u, v, w, c, i = 1; i <= m; i++) cin >> u >> v >> w >> c, (c ? e1[++m1] : e2[++m2]) = {u + 1, v + 1, w, c};
    sort(e1 + 1, e1 + 1 + m1, [](edge x, edge y)
         { return x.w < y.w; });
    sort(e2 + 1, e2 + 1 + m2, [](edge x, edge y)
         { return x.w < y.w; });
    int l = -114, r = 514, mid;
    while (l <= r)
    {
        mid = (l + r) >> 1;
        for (int i = 1; i <= m2; i++) e2[i].w -= mid;
        kruskal();
        if (cnt < k)
            l = mid + 1;
        else
            ans = sum + mid * k, r = mid - 1;
        for (int i = 1; i <= m2; i++) e2[i].w += mid;
    }
    cout << ans;
    return 0;
}