#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const ll mod = 45989, MAXM = 70;
ll n, m, t, a, b, ans;
inline void add(ll &a, ll b)
{
    a = (a + b) % mod;
}
struct Matrix
{
    int lx, ly;
    ll val[MAXM << 1][MAXM << 1];
    inline void init()
    {
        for (int i = 1; i <= min(lx, ly); i++)
            val[i][i] = 1;
    }
    inline ll *operator[](const int i)
    {
        return val[i];
    }
} trans, vec, tvec;
Matrix operator*(Matrix a, Matrix b)
{
    Matrix c = {a.lx, b.ly, {}};
    for (int i = 1; i <= a.lx; i++)
        for (int k = 1; k <= a.ly; k++)
            for (int j = 1; j <= b.ly; j++)
                add(c[i][j], a[i][k] * b[k][j] % mod);
    return c;
}
Matrix qpow(Matrix a, ll b)
{
    Matrix c = {a.lx, a.ly, {}};
    for (c.init(); b; b >>= 1ll, a = a * a)
        if (b & 1ll)
            c = c * a;
    return c;
}
struct edge
{
    int v, nxt;
} e[MAXM << 1];
int head[MAXM << 1], ecnt = 1;
inline void addedge(int u, int v)
{
    e[++ecnt] = {v, head[u]};
    head[u] = ecnt;
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m >> t >> a >> b;
    if (!t)
        cout << 0, exit(0);
    a++, b++;
    for (int u, v, i = 1; i <= m; i++)
    {
        cin >> u >> v;
        u++, v++;
        addedge(u, v);
        addedge(v, u);
    }
    trans.lx = trans.ly = ecnt;
    for (int i = 2; i <= ecnt; i++)
        for (int j = head[e[i].v]; j; j = e[j].nxt)
            if (j != (i ^ 1))
                trans[j][i]++;
    vec.lx = ecnt, vec.ly = 1;
    for (int i = head[a]; i; i = e[i].nxt)
        vec[i][1]++;
    tvec = qpow(trans, t - 1) * vec;
    for (int i = head[b]; i; i = e[i].nxt)
        add(ans, tvec[i ^ 1][1]);
    cout << ans;
    return 0;
}