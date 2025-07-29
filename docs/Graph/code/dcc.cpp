#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    int x = 0, f = 1;
    char ch;
    for (ch = getchar(); !isdigit(ch); ch = getchar())
        if (ch == '-') f = -1;
    for (; isdigit(ch); ch = getchar())
    {
        x = (x << 3) + (x << 1) + (ch - '0');
    }
    return f * x;
}
inline void write(int x)
{
    if (x < 0)
    {
        putchar('-');
        x = -x;
    }
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
    return;
}
const int MAXN = 5e5 + 10, MAXM = 2e6 + 10;
struct edge
{
    int u, v;
} E[MAXM << 1];
int n, m, head[MAXN], nex[MAXM << 1], edge_cnt, have_dcc, inde, dfn[MAXN],
    low[MAXN];
void add(int u, int v)
{
    if (u == v) return;
    edge_cnt++;
    E[edge_cnt] = (edge){u, v};
    nex[edge_cnt] = head[u];
    head[u] = edge_cnt;
    return;
}
stack<int> sta;
vector<int> dcc[MAXN];
void dfs(int u)
{
    dfn[u] = low[u] = inde++;
    if (!head[u])
    {
        have_dcc++;
        dcc[have_dcc].push_back(u);
        return;
    }
    sta.push(u);
    for (int i = head[u]; i; i = nex[i])
    {
        int v = E[i].v;
        if (!dfn[v])
        {
            dfs(v);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u])
            {
                int p;
                have_dcc++;
                do
                {
                    p = sta.top();
                    sta.pop();
                    dcc[have_dcc].push_back(p);
                } while (p != v);
                dcc[have_dcc].push_back(u);
            }
        }
        else
            low[u] = min(low[u], dfn[v]);
    }
    return;
}
int main()
{
    n = read(), m = read();
    while (m--)
    {
        int u = read(), v = read();
        add(u, v);
        add(v, u);
    }
    for (int i = 1; i <= n; i++)
    {
        if (!dfn[i])
        {
            sta = stack<int>();
            dfs(i);
        }
    }
    write(have_dcc);
    puts("");
    for (int i = 1; i <= have_dcc; i++)
    {
        write(dcc[i].size()), putchar(' ');
        for (auto p : dcc[i]) write(p), putchar(' ');
        puts("");
    }
    return 0;
}