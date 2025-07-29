struct SAM
{
    array<int, 26> son[MAXN];          // 每个状态通过字符转移到的状态
    int tot, lst, fa[MAXN], len[MAXN]; // 状态总数，最后添加的状态，后缀链接，状态对应的最大子串长度
    // 创建新节点，长度为p，后缀链接初始化为0
    int newnode(const int p) { return len[++tot] = p, tot; }
    // 构造函数：初始化SAM，创建根节点（对应空字符串）
    SAM() : tot(0), son({}), fa({}), len({}) { lst = newnode(0); }
    void insert(const int c)
    {
        int p = lst;
        // 创建新状态np，对应新添加字符后的最长子串，长度为lst的长度+1
        int np = lst = newnode(len[p] + 1); // 更新最后状态为np
        // 从p开始沿后缀链接回溯，将路径上未指向c的状态指向np
        while (p && !son[p][c]) son[p][c] = np, p = fa[p];
        if (!p) // 回溯到根仍未找到c转移，np的后缀链接指向根（1）
            return fa[np] = 1, void();
        int q = son[p][c];        // 找到已存在的c转移目标q
        if (len[q] == len[p] + 1) // 若q的长度是p+1，说明np的后缀链接可直接指向q
            return fa[np] = q, void();
        // 否则需要分裂q：创建nq作为q的副本，但长度为len[p]+1
        int nq = newnode(len[p] + 1);
        son[nq] = son[q];    // 复制q的转移
        fa[nq] = fa[q];      // 复制q的后缀链接
        fa[np] = fa[q] = nq; // 将q和np的后缀链接指向nq
        // 回溯修改原指向q的转移，将其重定向到nq
        while (p && son[p][c] == q) son[p][c] = nq, p = fa[p];
    }
};