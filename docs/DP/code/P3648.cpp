#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const int MAXN = 1e5 + 10;
ll f[2][MAXN], pre[210][MAXN];
int head, tail, n, k, a[MAXN];
struct vec
{
    int id, x;
    ll y;
    ll operator()(int v) { return (ll)x * v + y; }
} q[MAXN];
ll cross(vec a, vec b, vec c)
{
    a.x -= b.x;
    a.y -= b.y;
    b.x -= c.x;
    b.y -= c.y;
    return b.x * a.y - a.x * b.y;
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i], a[i] += a[i - 1];
    for (int t = 1; t <= k; t++)
    {
        head = tail = 0;
        q[0] = {0, 0, 0};
        for (int i = 1; i <= n; i++)
        {
            while (head < tail && q[head](a[i]) <= q[head + 1](a[i]))
                head++;
            f[t & 1][i] = q[head](a[i]);
            pre[t][i] = q[head].id;
            vec x = {i, a[i], f[t & 1 ^ 1][i] - (ll)a[i] * a[i]};
            while (head < tail && cross(q[tail - 1], q[tail], x) <= 0)
                tail--;
            q[++tail] = x;
        }
    }
    cout << f[k & 1][n] << endl;
    int now = n;
    for (int i = k; i >= 1; i--)
        cout << pre[i][now] << " ", now = pre[i][now];
    return 0;
}