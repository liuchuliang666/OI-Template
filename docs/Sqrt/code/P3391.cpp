void rev(int x)
{
    if (tag[x]) reverse(a[x], a[x] + sz[x]);
    tag[x] = 0; // 翻转后取消标记
}
void rotate(int pos, int len)
{
    int x = get_pos(pos);
    split(x, pos);
    int y = nxt[x];
    top = 0;
    while (len > 0)
    {
        if (sz[y] > len) split(y, len);
        len -= sz[y];
        sta[++top] = y;
        tag[y] ^= 1; // 注意这里不能直接=1
        y = nxt[y];
    }
    sta[++top] = x;
    sta[0] = y;
    for (; top >= 1; top--) nxt[sta[top]] = sta[top - 1]; // 反着连接块
    maintain();
}