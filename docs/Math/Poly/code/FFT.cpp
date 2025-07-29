#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const int MAXN = 4e6 + 10;
const double PI = acos(-1);
struct cmpx
{
    double x, y;
    cmpx operator+(cmpx t) { return {x + t.x, y + t.y}; }
    cmpx operator-(cmpx t) { return {x - t.x, y - t.y}; }
    cmpx operator*(cmpx t) { return {x * t.x - y * t.y, x * t.y + y * t.x}; }
} A[MAXN], B[MAXN];
int rev[MAXN], n, m;
void FFT(cmpx A[], int n, int op) // op = 1时，FFT；op = -1 时，IFFT
{
    // 位逆序变换
    for (int i = 0; i < n; i++)
        if (i < rev[i]) swap(A[i], A[rev[i]]);
    for (int i = 2; i <= n; i <<= 1) // 枚举块的长度
    {
        cmpx w1 = {cos(2 * PI / i),
                   sin(2 * PI / i) * op}; // 计算单位根(F2前面那个系数)
        for (int j = 0; j < n; j += i)    // 枚举块的起点
        {
            cmpx wk = {1, 0};                   // 从omega0开始
            for (int k = j; k < j + i / 2; k++) // 枚举每一个块内的前半部分元素
            {
                cmpx x = A[k], y = A[k + i / 2] * wk; // 计算F1, F2
                A[k] = x + y;                         // 求解前一半点值
                A[k + i / 2] = x - y;                 // 求解后一半点值
                wk = wk * w1;                         // 计算omegak
            }
        }
    }
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 0; i <= n; i++) cin >> A[i].x;
    for (int i = 0; i <= m; i++) cin >> B[i].x;
    for (m = n + m, n = 1; n <= m; n <<= 1); // 扩大n
    for (int i = 0; i < n; i++)
        rev[i] = (rev[i >> 1] >> 1) | ((n >> 1) * (i & 1)); // 位逆序变换预处理
    FFT(A, n, 1), FFT(B, n, 1);                             // 系数转点值
    for (int i = 0; i < n; i++) A[i] = A[i] * B[i];
    FFT(A, n, -1); // 点值相乘
    for (int i = 0; i <= m; i++)
        cout << (int)(A[i].x / n + 0.5) << ' '; // 四舍五入
    return 0;
}