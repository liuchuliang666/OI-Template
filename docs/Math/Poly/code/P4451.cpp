#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const ll p = 1e9 + 7, x = 485071604, y = 940286408, a = 514928404, b = 59713601;
ll qpow(ll a, ll b)
{
    static ll res;
    for (res = 1; b; b >>= 1, a = a * a % p)
        if (b & 1) res = res * a % p;
    return res;
}
ll read()
{
    static ll x;
    char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    for (x = 0; isdigit(ch); ch = getchar()) x = (x * 10 + ch - '0') % (p - 1);
    return x;
}
ll n;
int main()
{
    n = read() - 1;
    cout << (x * qpow(y, n) % p + a * qpow(b, n) % p) % p;
    return 0;
}