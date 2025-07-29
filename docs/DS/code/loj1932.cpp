#include <bits/stdc++.h>
using namespace std;
int rd()
{
    int x = 0, w = 1;
    char ch = 0;
    while (ch < '0' || ch > '9')
    {
        if (ch == '-') w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
    return x * w;
}
void wt(int x)
{
    static int sta[35];
    int f = 1;
    if (x < 0) f = -1, x *= f;
    int top = 0;
    do
    {
        sta[top++] = x % 10, x /= 10;
    } while (x);
    if (f == -1) putchar('-');
    while (top) putchar(sta[--top] + 48);
}
struct tag
{
    int x[7];
    void init()
    {
        x[1] = x[4] = x[6] = 1;
        x[2] = x[3] = x[5] = 0;
    }
    int &operator[](const int pos) { return x[pos]; }
    friend tag operator*(tag &A, tag &B)
    {
        tag c;
        c.init();
        c[2] = A[2] + B[2];
        c[3] = B[3] + A[2] * B[5] + A[3];
        c[5] = B[5] + A[5];
        return c;
    }
    friend bool operator!=(tag A, tag B)
    {
        for (int i = 0; i < 7; i++)
            if (A[i] != B[i]) return true;
        return false;
    }
    void print(string s)
    {
        cout << "test for " << s << "     matrix\n";
        cout << x[1] << ' ' << x[2] << ' ' << x[3] << '\n';
        cout << 0 << ' ' << x[4] << ' ' << x[5] << '\n';
        cout << 0 << ' ' << 0 << ' ' << x[6] << '\n';
    }
};
struct vet
{
    int y[4];
    void init() { y[1] = y[2] = y[3] = 0; }
    int &operator[](const int pos) { return y[pos]; }
    friend vet operator+(vet a, vet b)
    {
        vet c;
        c.init();
        c[1] = a[1] + b[1];
        c[2] = a[2] + b[2];
        c[3] = a[3] + b[3];
        return c;
    }
    void print(string s)
    {
        cout << '\n';
        cout << "test for " << s << "     vector\n";
        cout << y[1] << '\n';
        cout << y[2] << '\n';
        cout << y[3] << '\n';
        cout << '\n';
    }
};
vet operator*(tag A, vet B)
{
    vet c;
    c.init();
    c[1] = B[1] + B[2] * A[2] + B[3] * A[3];
    c[2] = B[2] + A[5] * B[3];
    c[3] = B[3];
    return c;
}
const int N = 1e5 + 5;
int n, m, a[N];
namespace sgt
{
#define ls (p << 1)
#define rs (ls | 1)
#define mid ((pl + pr) >> 1)
    tag T[N << 2];
    vet t[N << 2];
    void push_up(int p) { t[p] = t[ls] + t[rs]; }
    void addtag(int p, tag x)
    {
        T[p] = x * T[p];
        t[p] = x * t[p];
    }
    void push_down(int p)
    {
        tag c;
        c.init();
        if (T[p] != c)
        {
            addtag(ls, T[p]);
            addtag(rs, T[p]);
            T[p].init();
        }
    }
    void build(int p, int pl, int pr)
    {
        T[p].init();
        if (pl == pr)
        {
            t[p][2] = t[p][1] = a[pl];
            t[p][3] = 1;
            return;
        }
        build(ls, pl, mid);
        build(rs, mid + 1, pr);
        push_up(p);
    }
    void update(int p, int pl, int pr, int l, int r, tag x)
    {
        if (l <= pl && pr <= r)
        {
            addtag(p, x);
            // t[p].print("upd");
            // T[p].print("upd");
            return;
        }
        push_down(p);
        if (l <= mid) update(ls, pl, mid, l, r, x);
        if (r > mid) update(rs, mid + 1, pr, l, r, x);
        push_up(p);
    }
    int query(int p, int pl, int pr, int l, int r)
    {
        if (l <= pl && pr <= r) return t[p][1];
        push_down(p);
        if (r <= mid)
            return query(ls, pl, mid, l, r);
        else if (l > mid)
            return query(rs, mid + 1, pr, l, r);
        else
            return query(ls, pl, mid, l, r) + query(rs, mid + 1, pr, l, r);
    }
} // namespace sgt
signed main()
{
    n = rd(), m = rd();
    for (int i = 1; i <= n; i++) a[i] = rd();
    sgt::build(1, 1, n);
    while (m--)
    {
        int opt = rd();
        if (opt == 1)
        {
            int l = rd(), r = rd(), x = rd();
            tag c;
            c.init();
            c[5] = x;
            sgt::update(1, 1, n, l, r, c);
        }
        else
        {
            int l = rd(), r = rd();
            wt(sgt::query(1, 1, n, l, r));
            putchar('\n');
        }
        tag c;
        c.init();
        c[2] = 1;
        sgt::update(1, 1, n, 1, n, c);
    }
    return 0;
}