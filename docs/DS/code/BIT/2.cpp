int getsum(int x)
{ // a[1]..a[x]的和
    static int ans;
    for (ans = 0; x; x -= lowbit(x)) ans += c[x];
    return ans;
}