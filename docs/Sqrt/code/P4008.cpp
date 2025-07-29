#include <bits/stdc++.h>
using namespace std;
const int N = 1024 * 1024 + 5;
const int mxsize = 3000, mxnum = N * 2 / mxsize + 5; // 要开到N的两倍
int q;
int num, nxt[mxnum], sz[mxnum], pool[mxnum];
char dt[mxnum][mxsize], s[N];
void cpy(char *a, char *b, int len)
{
    for (int i = 0; i < len; i++) *(a + i) = *(b + i);
}
void gets(int len)
{
    for (int i = 0; i < len; i++)
    {
        s[i] = 0;
        while (s[i] < 32 || s[i] > 126) s[i] = getchar();
    }
}
void init()
{
    for (int i = 1; i <= mxnum; i++) // 初始化内存池
        pool[i] = i;
    sz[0] = 0;
    nxt[0] = -1; // 标记链表的结尾
}
int new_block()
{
    return pool[++num]; // 取出栈顶空节点
}
void del_block(int x)
{
    pool[num--] = x; // 将被删除的节点压入栈顶
}
void merge(int x, int y)
{
    cpy(dt[x] + sz[x], dt[y], sz[y]); // 手写的复制函数，与memcpy功能相同
    nxt[x] = nxt[y];
    sz[x] += sz[y];
    del_block(y); // 合并后，多出来的块要删掉
}
void maintain() // 遍历整个链表，合并所有可以合并的相邻块
{
    for (int x = 0, y = nxt[0]; x != -1; x = nxt[x], y = nxt[x])
        while (y != -1 && sz[x] + sz[y] <= mxsize)
        {
            merge(x, y);
            y = nxt[x];
        }
}
void update(int x, int y, int len, char *s)
{
    nxt[y] = nxt[x];
    nxt[x] = y;
    sz[y] = len;
    cpy(dt[y], s, len);
}
void split(int x, int pos)
{
    if (x == -1 || pos == sz[x]) return;
    int y = new_block();
    update(x, y, sz[x] - pos, dt[x] + pos); // 新建块
    sz[x] = pos;                            // 记得更新原块长
}
int get_pos(int &pos) // 将输入的位置转换成块上的位置
{
    int x = 0;
    while (x != -1 && pos > sz[x])
    {
        pos -= sz[x];
        x = nxt[x];
    }
    return x;
}
void insert(int pos, int len)
{
    int x = get_pos(pos), y, sum = 0;
    split(x, pos);
    while (sum + mxsize <= len)
    {
        y = new_block();
        update(x, y, mxsize, s + sum);
        sum += mxsize;
        x = y;
    }
    if (len > sum) // 如果切完后还有剩余，尾部自成一块
    {
        y = new_block();
        update(x, y, len - sum, s + sum);
    }
    maintain(); // 插入的左、右端点处可能可以合并，后面删除操作的maintain()同理
}
void erase(int pos, int len)
{
    int x = get_pos(pos), y;
    split(x, pos);
    y = nxt[x];
    while (y != -1 && len > 0)
    {
        if (sz[y] > len) split(y, len);
        len -= sz[y];
        del_block(y);
        y = nxt[y];
    }
    nxt[x] = y; // 记得指向下一块
    maintain();
}
void query(int pos, int len)
{
    int x = get_pos(pos), sum = sz[x] - pos;
    if (len < sum) sum = len;
    cpy(s, dt[x] + pos, sum);
    x = nxt[x];
    while (x != -1 && sum + sz[x] <= len)
    {
        cpy(s + sum, dt[x], sz[x]);
        sum += sz[x];
        x = nxt[x];
    }
    if (x != -1 && len > sum) cpy(s + sum, dt[x], len - sum);
    s[len] = 0; // 标记串的结尾
    printf("%s\n", s);
}
int main(void)
{
    scanf("%d", &q);
    init();
    int pos = 0;
    while (q--)
    {
        char rd[10];
        scanf("%s", rd);
        if (rd[0] == 'M')
            scanf("%d", &pos);
        else if (rd[0] == 'I')
        {
            int len;
            scanf("%d", &len);
            gets(len);
            insert(pos, len);
        }
        else if (rd[0] == 'D')
        {
            int len;
            scanf("%d", &len);
            erase(pos, len);
        }
        else if (rd[0] == 'G')
        {
            int len;
            scanf("%d", &len);
            query(pos, len);
        }
        else if (rd[0] == 'P')
            pos--;
        else if (rd[0] == 'N')
            pos++;
    }
    return 0;
}