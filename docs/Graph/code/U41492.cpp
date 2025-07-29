int dep[N], son[N], siz[N];
void dfs()
{ // 重链剖分
    dep[x] = dep[f] + 1;
    siz[x] = 1;
    for (int i = head[x]; ~i; i = nxt[i])
    {
        int y = to[i];
        if (y ^ f)
        {
            dfs(y, x);
            siz[x] += siz[y];
            if (!son[x] || siz[son[x]] < siz[y]) son[x] = y;
        }
    }
}
void add(int x, int f, int s)
{ // 加入贡献(本节点，父节点，最初节点的重儿子)
    ct[a[x]]++;
    //<--- 一些判断操作（例如最大值判断，如果答案变得更大则更新答案）
    for (int i = head[x]; ~i; i = nxt[i])
    {
        int y = to[i];
        if (y ^ s && y ^ f)
            add(y, x, s); // 不进入（最初的节点的）重儿子和父节点
    }
}
void sub(int x, int f)
{
    ct[a[x]]--;
    for (int i = head[x]; ~i; i = nxt[i])
    {
        int y = to[i];
        if (y ^ f) sub(y, x);
    }
}
void dfs(int x, int f, bool W)
{
    for (int i = head[x]; ~i; i = nxt[i])
    { // 先轻儿子
        int y = to[i];
        if (y ^ f && y ^ son[x]) dfs(y, x, false);
    }
    if (son[x]) dfs(son[x], x, true); // 后重儿子
    add(x, f, son[x]);                // 计算轻子树贡献
    ans[x] = sum;                     // 记录答案
    if (!W)
        sub(x, f),
            sum = mx = 0; // 如果是轻儿子就减去贡献，同时将计算答案的变量清零
}