int check(int l, int r)
{
    int res = 0;
    for (int i = 1; i <= n; i++) res += (l <= a[i] && a[i] <= r);
    return res;
}
void solve(int l, int r, vector<Query> q)
{
    int mid = (l + r) >> 1;
    if (l == r)
    {
        for (unsigned i = 0; i < q.size(); i++) ans[q[i].id] = l;
        return;
    }
    vector<Query> q1, q2;
    int t = check(l, mid);
    for (unsigned i = 0; i < q.size(); i++)
        if (q[i].k <= t)
            q1.push_back(q[i]);
        else
            q[i].k -= t, q2.push_back(q[i]);
    solve(l, mid, q1), solve(mid + 1, r, q2);
}