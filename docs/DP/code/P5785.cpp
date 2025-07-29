#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define mid ((l + r) >> 1)
const int MAXN = 3e5 + 10;
int head = 1, tail, q[MAXN], n;
ll s, t[MAXN], c[MAXN], f[MAXN];
int find(int l, int r, ll s)
{
    int ans = tail;
    while (l <= r)
        if (f[q[mid + 1]] - f[q[mid]] > s * (c[q[mid + 1]] - c[q[mid]]))
            ans = mid, r = mid - 1;
        else
            l = mid + 1;
    return q[ans];
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> s;
    for (int i = 1; i <= n; i++)
        cin >> t[i] >> c[i], t[i] += t[i - 1], c[i] += c[i - 1];
    q[++tail] = 0;
    for (int i = 1; i <= n; i++)
    {
        int p = find(head, tail, s + t[i]);
        f[i] = f[p] + s * (c[n] - c[p]) + t[i] * (c[i] - c[p]);
        while (head < tail && (f[q[tail]] - f[q[tail - 1]]) * (c[i] - c[q[tail]]) >= (f[i] - f[q[tail]]) * (c[q[tail]] - c[q[tail - 1]]))
            tail--;
        q[++tail] = i;
    }
    cout << f[n];
    return 0;
}