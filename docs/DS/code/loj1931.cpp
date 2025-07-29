#include <bits/stdc++.h>
using namespace std;
#define int long long
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
template <int N, int M, class T = long long>
struct matrix
{
    int m[N][M];
    matrix() { memset(m, 0, sizeof(m)); }
    void init()
    {
        for (int i = 0; i < N; i++) m[i][i] = 1;
    }
    friend bool operator!=(matrix<N, M> x, matrix<N, M> y)
    {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                if (x[i][j] != y[i][j]) return true;
        return false;
    }
    int *operator[](const int pos) { return m[pos]; }
    void print(string s)
    {
        cout << '\n';
        string t = "test for " + s + "  matrix:";
        cout << t << '\n';
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++) cout << m[i][j] << " \n"[j == M - 1];
        cout << '\n';
    }
};
template <int N, int M, int R, class T = long long>
matrix<N, R, T> operator*(matrix<N, M, T> a, matrix<M, R, T> b)
{
    matrix<N, R, T> c;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            for (int k = 0; k < R; k++) c[i][k] = c[i][k] + a[i][j] * b[j][k];
    return c;
}
template <int N, int M, class T = long long>
matrix<N, M, T> operator+(matrix<N, M, T> a, matrix<N, M, T> b)
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++) a[i][j] += b[i][j];
    return a;
}
const int N = 1e5 + 5;
int n, m, a[N];
namespace sgt
{
    matrix<3, 1> h[N << 2];
    matrix<3, 3> tag[N << 2];
#define ls (p << 1)
#define rs (ls | 1)
#define mid ((pl + pr) >> 1)
    void push_up(int p) { h[p] = h[ls] + h[rs]; }
    void addtag(int p, matrix<3, 3> c)
    {
        h[p] = c * h[p];
        tag[p] = c * tag[p];
    }
    void push_down(int p)
    {
        matrix<3, 3> c;
        c.init();
        if (tag[p] != c)
        {
            addtag(ls, tag[p]);
            addtag(rs, tag[p]);
            tag[p] = c;
        }
    }
    void build(int p, int pl, int pr)
    {
        matrix<3, 3> c;
        c.init();
        tag[p] = c;
        if (pl == pr)
        {
            h[p][0][0] = h[p][1][0] = a[pl];
            h[p][2][0] = 1;
            return;
        }
        build(ls, pl, mid);
        build(rs, mid + 1, pr);
        push_up(p);
    }
    void update(int p, int pl, int pr, int l, int r, matrix<3, 3> v)
    {
        if (l <= pl && pr <= r)
        {
            addtag(p, v);
            return;
        }
        push_down(p);
        if (l <= mid) update(ls, pl, mid, l, r, v);
        if (r > mid) update(rs, mid + 1, pr, l, r, v);
        push_up(p);
    }
    int query(int p, int pl, int pr, int l, int r)
    {
        if (l <= pl && pr <= r) return h[p][0][0];
        push_down(p);
        int ans = 0;
        if (l <= mid) ans += query(ls, pl, mid, l, r);
        if (r > mid) ans += query(rs, mid + 1, pr, l, r);
        return ans;
    }
} // namespace sgt
signed main()
{
    n = rd(), m = rd();
    for (int i = 1; i <= n; i++) a[i] = rd();
    sgt::build(1, 1, n);
    auto upd = [&]() -> void
    {
        int l = rd(), r = rd(), x = rd();
        matrix<3, 3> c;
        c.init();
        c[1][2] = x;
        sgt::update(1, 1, n, l, r, c);
    };
    auto qry = [&]() -> void
    {
        int l = rd(), r = rd();
        wt(sgt::query(1, 1, n, l, r));
        putchar('\n');
    };
    while (m--)
    {
        int opt = rd();
        switch (opt)
        {
        case 1:
            upd();
            break;
        case 2:
            qry();
            break;
        default:
            puts("Error");
            exit(0);
            break;
        }
        matrix<3, 3> v;
        v.init();
        v[0][1] = 1;
        sgt::update(1, 1, n, 1, n, v);
    }
    return 0;
}