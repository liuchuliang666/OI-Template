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
    int len[MAXN], son[MAXN][26], fa[MAXN], tot;
    int newnode(int l) { return len[++tot] = l, tot; }
    SAM() : len{}, fa{}, son{}, tot(0) { newnode(0); }
    int insertSAM(int c, int f)
    {
        int np = son[f][c];
        if (len[np]) return np;
        len[np] = len[f] + 1;
        int p = fa[f];
        while (p && !son[p][c]) son[p][c] = np, p = fa[p];
        if (!p) return fa[np] = 1, np;
        int q = son[p][c];
        if (len[q] == len[p] + 1) return fa[np] = q, np;
        int nq = newnode(len[p] + 1);
        for (int i = 0; i < 26; i++)
            if (len[son[q][i]]) son[nq][i] = son[q][i];
        fa[nq] = fa[q], fa[q] = fa[np] = nq;
        while (p && son[p][c] == q) son[p][c] = nq, p = fa[p];
        return np;
    }
    void insertTrie(string s)
    {
        int u = 1;
        for (char c : s)
        {
            int &v = son[u][c - 'a'];
            if (!v) v = newnode(0);
            u = v;
        }
    }
    void buildSAM()
    {
        queue<pii> q;
        for (int i = 0; i < 26; i++)
            if (son[1][i]) q.push({i, 1});
        while (!q.empty())
        {
            auto [c, f] = q.front();
            q.pop();
            int u = insertSAM(c, f);
            for (int i = 0; i < 26; i++)
                if (son[u][i]) q.push({i, u});
        }
    }
} sam;
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    while (n--) cin >> s, sam.insertTrie(s);
    sam.buildSAM();
    for (int i = 2; i <= sam.tot; i++) ans += sam.len[i] - sam.len[sam.fa[i]];
    cout << ans << endl
         << sam.tot;
    return 0;
}