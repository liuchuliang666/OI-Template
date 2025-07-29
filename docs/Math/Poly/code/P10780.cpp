#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll p = 10007, inv6 = 1668;
ll n;
char ch;
int main()
{
    while (isdigit(ch = getchar())) n = (n * 10 + ch - '0') % p;
    cout << ((n + 1) * (n + 2) * n * inv6) % p;
    return 0;
}