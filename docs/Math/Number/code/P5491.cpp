#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
mt19937 rnd(time(0));
ll n, p, imag2;
struct cmpx
{
    ll a, b;
    cmpx(ll a = 0, ll b = 0) : a(a % p), b(b % p) {}
};
cmpx operator+(const cmpx x, const cmpx y)
{
    return cmpx(x.a + y.a, x.b + y.b);
}
cmpx operator*(const cmpx x, const cmpx y)
{
    return cmpx(x.a * y.a + x.b * y.b % p * imag2, x.b * y.a + x.a * y.b);
}
ll qpow(ll a, ll b)
{
    static ll res;
    for (res = 1; b; b >>= 1, a = a * a % p)
        if (b & 1) res = res * a % p;
    return res;
}
cmpx qpow(cmpx a, ll b)
{
    static cmpx res;
    for (res = 1; b; b >>= 1, a = a * a)
        if (b & 1) res = res * a;
    return res;
}
bool eularchk(ll x) { return qpow(x, (p - 1) >> 1) == 1; }
bool cipolla(ll n, ll &x1, ll &x2)
{
    if (!eularchk(n)) return false;
    ll a = rnd() % p;
    while (!a || eularchk(imag2 = ((a * a % p - n) % p + p) % p)) a = rnd() % p;
    x1 = qpow(cmpx(a, 1), (p + 1) >> 1).a;
    x2 = p - x1;
    return true;
}
void solve()
{
    ll x1, x2;
    cin >> n >> p;
    if (!n)
        cout << 0 << endl;
    else if (!cipolla(n, x1, x2))
        cout << "Hola!" << endl;
    else
    {
        if (x1 > x2) swap(x1, x2);
        cout << x1 << " " << x2 << endl;
    }
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}