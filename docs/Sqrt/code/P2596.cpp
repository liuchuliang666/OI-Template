#include <bits/stdc++.h>
using namespace std;
const int N = 405;
int n, m, k;
int a[N][N], sz[N], pool[N], nxt[N], book[N][80005];
void init()
{
    for (int i = 1; i <= N - 5; i++) pool[i] = i;
    nxt[0] = -1;
}
int new_block() { return pool[++k]; }
void del_block(int x)
{
    for (int i = 0; i < sz[x]; i++) book[x][a[x][i]] = 0; // 记得清空book
    pool[k--] = x;
}
void cpy(int *a, int *b, int len)
{
    for (int i = 0; i < len; i++) *(a + i) = *(b + i);
}
void merge(int x, int y)
{
    cpy(a[x] + sz[x], a[y], sz[y]);
    nxt[x] = nxt[y];
    sz[x] += sz[y];
    for (int i = 0; i < sz[y]; i++) book[x][a[y][i]] = 1;
    del_block(y);
}
void maintain()
{
    for (int x = 0, y = nxt[0]; x != -1; x = nxt[x], y = nxt[x])
        while (y != -1 && sz[x] + sz[y] <= 400)
        {
            merge(x, y);
            y = nxt[x];
        }
}
void update(int x, int y, int len, int *c)
{
    nxt[y] = nxt[x];
    nxt[x] = y;
    sz[y] = len;
    cpy(a[y], c, len);
    for (int i = 0; i < sz[y]; i++) book[y][a[y][i]] = 1;
}
void split(int x, int pos)
{
    if (x == -1 || pos == sz[x]) return;
    int y = new_block();
    update(x, y, sz[x] - pos, a[x] + pos);
    sz[x] = pos;
    for (int i = 0; i < sz[y]; i++) book[x][a[y][i]] = 0;
}
int get_pos(int &pos)
{
    int x = 0;
    while (x != -1 && pos > sz[x])
    {
        pos -= sz[x];
        x = nxt[x];
    }
    return x;
}
void insert(int pos, int num)
{
    int x = get_pos(pos);
    split(x, pos);
    int y = new_block();
    update(x, y, 1, &num);
    maintain();
}
void remove(int pos)
{
    int x = get_pos(pos);
    split(x, pos);
    int y = nxt[x];
    split(y, 1);
    nxt[x] = nxt[y];
    del_block(y);
    maintain();
}
int query(int pos)
{
    int x = get_pos(pos);
    return a[x][pos - 1];
}
int askk(int id)
{
    int x = 0, num = 0;
    while (!book[x][id])
    {
        num += sz[x];
        x = nxt[x];
    } // 跳到包含id的块
    for (int i = 0; i < sz[x]; i++, num++)
        if (a[x][i] == id) // 找到id具体位置
            return num;
}
void top(int id)
{
    if (askk(id) != 0) // 判断边界
    {
        remove(askk(id));
        insert(0, id);
    }
}
void bottom(int id)
{
    if (askk(id) != n - 1)
    {
        remove(askk(id));
        insert(n - 1, id);
    }
}
void step(int id, int t)
{
    if (!t) return;
    int pos = askk(id);
    if (t == 1)
        if (pos != n - 1)
        {
            remove(pos);
            insert(pos + 1, id);
        }
    if (t == -1)
        if (pos != 0)
        {
            remove(pos);
            insert(pos - 1, id);
        }
}
int main(void)
{
    scanf("%d%d", &n, &m);
    init();
    for (int i = 1; i <= n; i++)
    {
        int x;
        scanf("%d", &x);
        insert(i - 1, x);
    }
    for (int i = 1; i <= m; i++)
    {
        char c[10];
        int s, t;
        scanf("%s%d", c, &s);
        if (c[0] == 'T')
            top(s);
        else if (c[0] == 'B')
            bottom(s);
        else if (c[0] == 'I')
        {
            scanf("%d", &t);
            step(s, t);
        }
        else if (c[0] == 'A')
            printf("%d\n", askk(s));
        else if (c[0] == 'Q')
            printf("%d\n", query(s));
    }
    return 0;
}