#include <bits/stdc++.h>
#define mid ((l) + (r) >> 1)
#define endl '\n'
using namespace std;
const int MAXN = 5e5 + 10;
int n, a[MAXN];
double f[MAXN], sqr[MAXN];
double w(int j, int i) { return 1.0 * a[j] + sqr[i - j]; }
void getdp(int l, int r, int kl, int kr)
{
    if (l > r) return;
    int k = kl;
    for (int i = kl + 1; i <= min(mid, kr); i++)
        if (w(i, mid) > w(k, mid)) k = i;
    f[mid] = max(f[mid], w(k, mid));
    getdp(l, mid - 1, kl, k), getdp(mid + 1, r, k, kr);
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], sqr[i] = sqrt(i);
    getdp(1, n, 1, n), reverse(f + 1, f + n + 1), reverse(a + 1, a + n + 1), getdp(1, n, 1, n);
    for (int i = n; i; i--) cout << (int)ceil(f[i]) - a[i] << endl;
    return 0;
}