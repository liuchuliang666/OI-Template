> 前置知识：[CDQ分治](../../DivideAndDouble/CDQ分治.md)

分治FFT描述的是一类半在线DP方程的卷积优化。

???+ question "[P4721 【模板】分治 FFT](https://www.luogu.com.cn/problem/P4721)"
    ???+ note "注意"
        本题也可用[多项式求逆](./多项式初等函数.md#多项式求逆)解决。

    给定序列 $g_{1\dots n - 1}$，求序列 $f_{0\dots n - 1}$。

    其中 $f_i=\sum_{j=1}^if_{i-j}g_j$，边界为 $f_0=1$。

    答案对 $998244353$ 取模。

    $2\leq n\leq 10^5$，$0\leq g_i<998244353$。

我们应用CDQ分治，先求出 $f_{[l,mid)}$，再求对 $f_{[mid, r)}$ 的贡献。

由题中公式可以发现，多项式 $f_{[l,mid)} * g_{[0, r-l)}$ 正好就是对 $f_{[mid, r)}$ 的贡献。

??? code "实现"
    ```cpp
    --8<-- "docs/Math/Poly/code/P4721.cpp"
    ```