int tot = -1, lst; // endpos编号，最后加入的节点（状态）
struct node
{
    int son[26], fa, len; // 加字符后指向的endpos，后缀链，此等价类中最大字串长度
} sam[N];
void newnode(int len, int fa)
{
    sam[++tot].len = len; // 新增一个endpos
    sam[tot].fa = fa;     // 后缀链指向未知
}
void insert(int c)
{
    newnode(sam[lst].len + 1, -1); // 新加入一个字符，得到的字符串为最后状态的长度 + 1
    int p = lst, np = tot;
    while (p != -1 && !sam[p].son[c]) // 如果p跳到未知或者字符串p + c的endpos已经出现过即跳出
    {
        sam[p].son[c] = np; // p + c的endpos即为np
        p = sam[p].fa;      // 跳fa找到第一个出现过的子串
    }
    if (p == -1)
        sam[np].fa = 0; // 若p跳到未知则不存在出现过的字串，即c是新字符，则字符串np的后缀链指向根
    else
    {
        int q = sam[p].son[c]; // 字符串p + c所在的endpos
        if (sam[q].len == sam[p].len + 1)
            sam[np].fa = q; // 字符串p + c为其所在的endpos中最长的字串，则字符串np的后缀链指向q
        else                // 字符串p + c不为其所在的endpos中最长的字串，则分裂endpos为长度较长的后缀和长度较短的后缀，其中较长的部分后缀endpos不变，较短的另一部分后缀endpos增加np
        {
            newnode(sam[p].len + 1, sam[q].fa); // 复制一个点名为nq
            int nq = tot;
            memcpy(sam[nq].son, sam[q].son, sizeof sam[q].son);
            sam[np].fa = sam[q].fa = nq;
            // 复制的点nq为长度较短的部分后缀所在的endpos
            // 原本的点q为长度较长的部分后缀所在的endpos
            sam[np].fa = sam[q].fa = nq;          // 字符串np和q的后缀链指向nq
            while (p != -1 && sam[p].son[c] == q) // 如果p未跳到未知或者字符串p + c的endpos原本指向q
            {
                sam[p].son[c] = nq; // 将其指向nq
                p = sam[p].fa;      // 跳fa找其他指向q并且需要修改的点
            }
        }
    }
    lst = np;
}
signed main()
{
    newnode(0, -1); // 空子串组成的根节点
    //...
    return 0;
}