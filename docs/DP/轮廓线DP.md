轮廓线DP是状态压缩DP的一种。

???+ question "[UVA11270 Tiling Dominoes](https://www.luogu.com.cn/problem/UVA11270)"
    给定一个 $m \times n$ 的矩形网格，用 $1 \times 2$ 多米诺骨牌完全平铺。 请注意，即使一个平铺的旋转与另一个平铺相匹配，它们仍算作不同的平铺。

??? code "实现"
    ```cpp
    --8<-- "docs/DP/code/brick.cpp"
    ```
