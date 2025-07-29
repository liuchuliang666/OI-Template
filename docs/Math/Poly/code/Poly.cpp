#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const int MAXN = 6e5 + 10;
const ll p = 998244353, g = 3;
inline ll qpow(ll a, ll b)
{
    static ll res;
    for (res = 1; b; b >>= 1, a = a * a % p)
        if (b & 1) res = res * a % p;
    return res;
}
inline ll getinv(const ll x) { return qpow(x, p - 2); }
const ll gi = getinv(g), img = qpow(g, (p - 1) / 4), inv2 = getinv(2), inv2img = getinv(img * 2);
int rev[MAXN];
ll inv[MAXN];
inline void initinv(const int n)
{
    inv[1] = 1;
    for (int i = 2; i <= n; i++) inv[i] = (p - p / i) * inv[p % i] % p;
}
inline int getrev(const int n)
{
    int lim = 1;
    while (lim <= n) lim <<= 1;
    for (int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * (lim >> 1));
    return lim;
}
struct Poly : public vector<ll>
{
    using vector<ll>::vector; // 继承 vector<ll> 的所有构造函数
    static inline void read(const int n, Poly &F)
    {
        F.resize(n);
        for (ll &x : F) cin >> x, x %= p;
    }
    static inline void write(const Poly F)
    {
        for (ll x : F) cout << x << ' ';
        cout << endl;
    }
    friend inline Poly operator+(Poly F, Poly G)
    {
        if (F.size() > G.size()) std::swap(F, G);
        for (int i = 0; i < F.size(); i++) G[i] = (G[i] + F[i]) % p;
        return G;
    }
    friend inline Poly operator-(Poly F, const Poly G)
    {
        if (F.size() < G.size()) F.resize(G.size());
        for (int i = 0; i < G.size(); i++) F[i] = (F[i] - G[i] + p) % p;
        return F;
    }
    friend inline Poly operator*(Poly F, ll x)
    {
        x = (x + p) % p;
        for (ll &y : F) y = x * y % p;
        return F;
    }
    friend inline Poly operator*(const ll x, const Poly F) { return F * x; }
    static inline Poly NTT(const Poly F, const int n, const int op)
    {
        Poly A(F);
        A.resize(n);
        for (int i = 0; i < n; i++)
            if (i < rev[i]) std::swap(A[i], A[rev[i]]);
        for (int i = 2; i <= n; i <<= 1)
        {
            ll g1 = qpow(op == 1 ? g : gi, p / i);
            for (int j = 0; j < n; j += i)
            {
                ll gk = 1;
                for (int k = j; k < j + i / 2; k++)
                {
                    ll x = A[k], y = A[k + i / 2] * gk % p;
                    A[k] = (x + y) % p;
                    A[k + i / 2] = (x - y + p) % p;
                    gk = gk * g1 % p;
                }
            }
        }
        if (op == 1) return A;
        const ll ni = getinv(n);
        for (int i = 0; i < n; i++) A[i] = A[i] * ni % p;
        return A;
    }
    friend inline Poly operator*(Poly F, Poly G)
    {
        const int n = F.size(), m = G.size(), len = n + m - 1, lim = getrev(len);
        F = NTT(F, lim, 1), G = NTT(G, lim, 1);
        for (int i = 0; i < lim; i++) F[i] = F[i] * G[i] % p;
        return F = NTT(F, lim, -1), F.resize(len), F;
    }
    static inline Poly Dert(const Poly F)
    {
        const int n = F.size();
        Poly G(n - 1);
        for (int i = 1; i < n; i++) G[i - 1] = F[i] * i % p;
        return G;
    }
    static inline Poly Int(const Poly F)
    {
        const int n = F.size();
        Poly G(n + 1);
        for (int i = 0; i < n; i++) G[i + 1] = F[i] * inv[i + 1] % p;
        return G;
    }
    static inline Poly Inv(Poly F)
    {
        int n = F.size(), len, lim = getrev(n);
        Poly G{getinv(F[0])};
        F.resize(lim);
        for (len = 1; len < (n << 1); len <<= 1)
        {
            G.resize(lim = getrev(len << 1));
            Poly A(F.begin(), F.begin() + len), B(G.begin(), G.begin() + len);
            A = NTT(A, lim, 1), B = NTT(B, lim, 1);
            for (int i = 0; i < lim; i++) G[i] = ((2 - B[i] * A[i] % p) % p * B[i] % p + p) % p;
            G = NTT(G, lim, -1), G.resize(len);
        }
        return G.resize(n), G;
    }
    static inline void Div(Poly F, Poly G, Poly &Q, Poly &R)
    {
        const int n = F.size(), m = G.size(), len = n - m + 1;
        Poly A(F), B(G);
        reverse(A.begin(), A.end()), reverse(B.begin(), B.end()), A.resize(len), B.resize(len), Q = A * Inv(B), Q.resize(len), reverse(Q.begin(), Q.end()), R = F - G * Q, R.resize(m - 1);
    }
    static inline Poly Ln(const Poly F)
    {
        Poly G = Dert(F) * Inv(F);
        return G.resize(F.size() - 1), Int(G);
    }
    static inline Poly Exp(Poly F)
    {
        int n = F.size(), len, lim = getrev(n);
        Poly G{1};
        F.resize(lim);
        for (len = 1; len < (n << 1); len <<= 1)
        {
            G.resize(lim = getrev(len << 1));
            Poly A(F.begin(), F.begin() + len), B(G.begin(), G.begin() + len);
            G = B * (Poly({1}) - Ln(B) + A), G.resize(len);
        }
        return G.resize(n), G;
    }
    static inline Poly Sqrt(Poly F)
    {
        int n = F.size(), len, lim = getrev(n);
        Poly G{1};
        F.resize(lim);
        for (len = 1; len < (n << 1); len <<= 1)
        {
            G.resize(lim = getrev(len << 1));
            Poly A(F.begin(), F.begin() + len), B(G.begin(), G.begin() + len), I = Inv(B);
            A = NTT(A, lim, 1), B = NTT(B, lim, 1), I = NTT(I, lim, 1);
            for (int i = 0; i < lim; i++) G[i] = (B[i] * B[i] % p + A[i]) % p * inv2 % p * I[i] % p;
            G = NTT(G, lim, -1), G.resize(len);
        }
        return G.resize(n), G;
    }
    static inline Poly Pow(const Poly F, const ll k) { return Exp(Ln(F) * k); }
    static inline Poly Sin(const Poly F) { return (Exp(img * F) - Exp((p - img) * F)) * inv2img; }
    static inline Poly Cos(const Poly F) { return (Exp(img * F) + Exp((p - img) * F)) * inv2; }
    static inline Poly Asin(const Poly F)
    {
        Poly G = Poly({1}) - F * F;
        return G.resize(F.size()), G = (Int(Dert(F) * Inv(Sqrt(G)))), G.resize(F.size()), G;
    }
    static inline Poly Atan(const Poly F)
    {
        Poly G = Poly({1}) + F * F;
        return G.resize(F.size()), G = (Int(Dert(F) * Inv(G))), G.resize(F.size()), G;
    }
};
int n, m;
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    // Usage:
    initinv(6e5);
    cin >> n >> m;
    Poly F, G, Q, R;
    Poly::read(n, F), Poly::read(m, G);
    Poly::write(F * G);
    Poly::write(Poly::Inv(F));
    Poly::write(Poly::Sqrt(F));
    Poly::Div(F, G, Q, R), Poly::write(Q), Poly::write(R);
    Poly::write(Poly::Ln(F));
    Poly::write(Poly::Exp(F));
    Poly::write(Poly::Sin(F));
    Poly::write(Poly::Cos(F));
    Poly::write(Poly::Asin(F));
    Poly::write(Poly::Atan(F));
    return 0;
}