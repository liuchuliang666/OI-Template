#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
typedef pair<int, int> pii;
const int MAXN = 2e6 + 10;
int n;
ll ans;
string s;
struct SAM
{
    array<int, 26> son[MAXN];
    int len[MAXN], fa[MAXN], tot;
    int newnode(const int l) { return len[++tot] = l, tot; }
    SAM() : len{}, fa{}, tot(0) { newnode(0); }
    int insert(const int c, const int lst)
    {
        int p = lst, np = son[lst][c];
        if (np) // 如果这个转移已经有了，检查是否符合要求
        {
            if (len[np] == len[p] + 1) // 符合则直接返回
                return np;
            int nq = newnode(len[p] + 1); // 否则分裂，新建节点
            son[nq] = son[np], fa[nq] = fa[np], fa[np] = nq;
            while (p && son[p][c] == np) son[p][c] = nq, p = fa[p];
            return nq; // 这里需要注意的是，新建的这个节点才代表我们新来的字符，因此返回 nq 并非 np
        }
        // 如果这个转移还没有，那就是正常的 SAM
        np = newnode(len[p] + 1);
        while (p && !son[p][c]) son[p][c] = np, p = fa[p];
        if (!p) return fa[np] = 1, np;
        int q = son[p][c];
        if (len[q] == len[p] + 1) return fa[np] = q, np;
        int nq = newnode(len[p] + 1);
        son[nq] = son[q], fa[nq] = fa[q], fa[q] = fa[np] = nq;
        while (p && son[p][c] == q) son[p][c] = nq, p = fa[p];
        return np;
    }
    void insertString(const string s)
    {
        int lst = 1;
        for (char c : s) lst = insert(c - 'a', lst); // 以上一个结点为基础建树
    }
} sam;
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    while (n--) cin >> s, sam.insertString(s);
    for (int i = 2; i <= sam.tot; i++) ans += sam.len[i] - sam.len[sam.fa[i]];
    cout << ans << endl
         << sam.tot;
    return 0;
}