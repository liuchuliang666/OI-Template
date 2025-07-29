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
template <int N, class T = long long>
matrix<N, N, T> qpow(matrix<N, N, T> x, int k)
{
    matrix<N, N, T> re;
    re.init();
    while (k)
    {
        if (k & 1) re = re * x;
        x = x * x;
        k >>= 1;
    }
    return re;
}
matrix<3, 3> re, b;
signed main()
{
    re.init();
    while (1)
    {
        int c = rd();
        if (c == 0) return 0;
        if (c == 1)
        {
            b.init();
            int x = rd();
            b[1][2] = x;
            re = b * re;
            re.print("result:");
        }
        else if (c == 2)
        {
            b.init();
            b[0][1] = 1;
            re = b * re;
            re.print("result:");
        }
    }
    return 0;
}