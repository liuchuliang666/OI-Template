## 简介

> 沃尔什转换（Walsh Transform）是在频谱分析上作为离散傅立叶变换的替代方案的一种方法。——[维基百科](https://zh.wikipedia.org/zh-cn/%E6%B2%83%E7%88%BE%E4%BB%80%E8%BD%89%E6%8F%9B)

其实这个变换在信号处理中应用很广泛，FFT 是 double 类型的，但是 Walsh 把信号在不同震荡频率方波下拆解，因此所有的系数都是绝对值大小相同的整数，这使得不需要作浮点数的乘法运算，提高了运算速度。

所以，FWT 和 FFT 的核心思想应该是相同的，都是对数组的变换。我们记对数组 $A$ 进行快速沃尔什变换后得到的结果为 $FWT[A]$。

那么 FWT 核心思想就是：

我们需要一个新序列 $C$，由序列 $A$ 和序列 $B$ 经过某运算规则得到，即 $C = A \cdot B$；

我们先正向得到序列 $FWT[A], FWT[B]$，再根据 $FWT[C]=FWT[A] \cdot FWT[B]$ 在 $O(n)$ 的时间复杂度内求出 $FWT[C]$，其中 $\cdot$ 是序列对应位置相乘；

然后逆向运算得到原序列 $C$。时间复杂度为 $O(n \log{n})$。

在算法竞赛中，FWT 是用于解决对下标进行位运算卷积问题的方法。

公式：$C_{i} = \sum_{i=j \oplus k}A_{j} B_{k}$

（其中 $\oplus$ 是二元位运算中的某一种）

下面我们举 $\cup$（按位或）、$\cap$（按位与）和 $\oplus$（按位异或）为例。

## FWT 的运算

### 或运算

如果有 $k=i\cup j$，那么 $i$ 的二进制位为 $1$ 的位置和 $j$ 的二进制位为 $1$ 的位置肯定是 $k$ 的二进制位为 $1$ 的位置的子集。

现在要得到 $FWT[C] = FWT[A] \cdot FWT[B]$，我们就要构造这个 FWT 的规则。

我们按照定义，显然可以构造 $FWT[A]_i = A'_i = \sum_{i=i\cup j}A_{j}$，来表示 $j$ 满足二进制中 $1$ 为 $i$ 的子集。

那么有：

$$
\begin{aligned}
FWT[A]_i\cdot FWT[B]_i&=\left(\sum_{i\cup j=i} A_j\right)\left(\sum_{i\cup k=i} B_k\right) \\
&=\sum_{i\cup j=i}\sum_{i\cup k=i}A_jB_k \\
&=\sum_{i\cup(j\cup k)=i}A_jB_k \\
&= FWT[C]_i
\end{aligned}
$$

那么我们接下来看 $FWT[A]$ 怎么求。

首先肯定不能枚举了，复杂度为 $O(n^2)$。既然不能整体枚举，我们就考虑分治。

我们把整个区间二分，其实二分区间之后，下标写成二进制形式是有规律可循的。

我们令 $A_0$ 表示 $A$ 的前一半，$A_1$ 表示区间的后一半，那么 $A_0$ 就是 A 下标最大值的最高位为 $0$，他的子集就是他本身的子集（因为最高位为 $0$ 了），但是 $A_1$ 的最高位是 $1$，他满足条件的子集不仅仅是他本身，还包最高位为 $0$ 的子集，即

$$
FWT[A] = merge(FWT[A_0], FWT[A_0] + FWT[A_1])
$$

其中 merge 表示像字符串拼接一样把两个数组拼起来，$+$ 就是普通加法，表示对应二进制位相加。

这样我们就通过二分能在 $O(\log{n})$ 的时间复杂度内完成拼接，每次拼接的时候要完成一次运算，也就是说在 $O(n\log{n})$ 的时间复杂度得到了 $FWT[A]$。

接下来就是反演了，其实反演是很简单的，既然知道了 $A_0$ 的本身的子集是他自己（$A_0 = FWT[A_0]$），$A_1$ 的子集是 $FWT[A_0] + FWT[A_1]$，那就很简单的得出反演的递推式了：

$$
UFWT[A'] = merge(UFWT[A_0'], UFWT[A_1'] - UFWT[A_0'])
$$

下面我们给出代码实现。容易发现顺变换和逆变换可以合并为一个函数，顺变换时 $\text{type}=1$，逆变换时 $\text{type}=-1$。

???+ code "实现"
    ```cpp
    --8<-- "docs/Math/Poly/code/P4717.cpp:24:30"
    ```

### 与运算

与运算类比或运算可以得到类似结论

$$
FWT[A] = merge(FWT[A_0] + FWT[A_1], FWT[A_1])
$$

$$
UFWT[A'] = merge(UFWT[A_0'] - UFWT[A_1'], UFWT[A_1'])
$$

下面我们给出代码实现。顺变换时 $\text{type}=1$，逆变换时 $\text{type}=-1$。

???+ code "实现"
    ```cpp
    --8<-- "docs/Math/Poly/code/P4717.cpp:31:37"
    ```

### 异或运算

异或的卷积是基于如下原理：

若我们令 $x\circ y$ 表示 $x\cap y$ 中 $1$ 数量的奇偶性，即 $x\circ y=\text{popcnt}(x\cap y)\bmod 2$，那么容易有 $(x\circ y)\oplus (x\circ z)=x\circ(y\oplus z)$。

对于 $FWT[A]$ 的运算其实也很好得到。

设 $FWT[A]_i=\sum_{i\circ j=0}A_j-\sum_{i\circ j=1}A_j$。我们来证一下 $FWT[C] = FWT[A] \cdot FWT[B]$ 的正确性：

$$
\begin{aligned}
FWT[A]_iFWT[B]_i&=\left(\sum_{i\circ j=0}A_j-\sum_{i\circ j=1}A_j\right)\left(\sum_{i\circ k=0}B_k-\sum_{i\circ k=1}B_k\right) \\
&=\left(\sum_{i\circ j=0}A_j\sum_{i\circ k=0}B_k+\sum_{i\circ j=1}A_j\sum_{i\circ k=1}B_k\right)-\left(\sum_{i\circ j=0}A_j\sum_{i\circ k=1}B_k+\sum_{i\circ j=1}A_j\sum_{i\circ k=0}B_k\right) \\
&=\sum_{(j\oplus k)\circ i=0}A_jB_k-\sum_{(j\oplus k)\circ i=1}A_jB_k \\
&=FWT[C]_i
\end{aligned}
$$

来看看怎么快速计算 $A,B$ 的值，依旧是分治：

对于 $i$ 在当前位为 $0$ 的子数列 $FWT[A_0]$，进行 $\circ$ 运算时发现它和 $0$ 计算或和 $1$ 计算结果都不会变（因为 $0\cap 0=0,0\cap1=0$），所以 $FWT[A]=\sum_{i\circ j=0}A_j-\sum_{i\circ j=1}A_j$ 中的 $\sum_{i\circ j=1}A_j=0$。

对于 $i$ 在当前位为 $1$ 的子数列 $A_1$，进行 $\circ$ 运算时发现它和 $0$ 计算结果是 $0$，和 $1$ 计算结果是 $1$（因为 $1\cap 0=0,1\cap1=1$）。

综上，有：

$$
FWT[A]=merge((FWT[A_0]+FWT[A_1])-0, FWT[A_0]-FWT[A_1])
$$

也就是：

$$
FWT[A] = merge(FWT[A_0] + FWT[A_1], FWT[A_0] - FWT[A_1])
$$

逆变换易得：

$$
UFWT[A'] = merge(\frac{UFWT[A_0'] + UFWT[A_1']}{2}, \frac{UFWT[A_0'] - UFWT[A_1']}{2})
$$

给出代码，顺变换时 $\text{type}=1$，逆变换时 $\text{type}=\frac{1}{2}$。

???+ code "实现"
    ```cpp
    --8<-- "docs/Math/Poly/code/P4717.cpp:38:49"
    ```

下面是模板题：

???+ question "[P4717 【模板】快速莫比乌斯/沃尔什变换 (FMT/FWT)](https://www.luogu.com.cn/problem/P4717)"
    给定长度为 $2^n$ 两个序列 $A,B$，设 

    $$C_i=\sum_{j\oplus k = i}A_j \times B_k$$

    分别当 $\oplus$ 是 $\text{or}$, $\text{and}$, $\text{xor}$ 时求出 $C$，结果对 $998244353$ 取模。

    $1 \le n \le 17$。

??? code "实现"
    ```cpp
    --8<-- "docs/Math/Poly/code/P4717.cpp"
    ```


### 同或运算

类比异或运算给出公式：

$FWT[A]_{i} = \sum_{C_1}A_{j} - \sum_{C_2}A_{j}$（$C_1$ 表示 $\text{popcnt}(x\cup y)\bmod 2$ 为 $0$，$C_2$ 表示 $\text{popcnt}(x\cup y)\bmod 2$ 为 $1$）

$$
FWT[A] = merge(FWT[A_1] - FWT[A_0], FWT[A_1] + FWT[A_0])
$$

$$
UFWT[A'] = merge(\frac{UFWT[A_1'] - UFWT[A_0']}{2}, \frac{UFWT[A_1'] + UFWT[A_0']}{2})
$$

## 另一个角度的 FWT

我们设 $c(i,j)$ 是 $A_j$ 对 $FWT[A]_i$ 的贡献系数。我们可以重新描述 FWT 变换的过程：

$$
FWT[A]_i = \sum_{j=0}^{n-1} c(i,j) A_j
$$

因为有：

$$
FWT[A]_i\cdot FWT[B]_i=FWT[C]_i
$$

所以我们可以通过简单的证明得到：$c(i,j)c(i,k)=c(i,j\odot k)$。其中 $\odot$ 是任意一种位运算。

同时，$c$ 函数还有一个重要的性质，它可以按位处理。

举个例子，我们变换的时候：

$$
FWT[A]_i = \sum_{j=0}^{n-1} c(i,j) A_j
$$

这么做是比较劣的，我们将其拆分：

$$
FWT[A]_i = \sum_{j=0}^{n/2-1} c(i,j) A_j+\sum_{j=n/2}^{n-1} c(i,j) A_j
$$

考虑前面的式子和后面的式子 $i,j$ 的区别，发现只有最高位不同。

所以我们将 $i,j$ 去除最高位的值为 $i',j'$，并记 $i_0$ 为 $i$ 的最高位。有：

$$
FWT[A]_i = c(i_0,0)\sum_{j=0}^{n/2-1} c(i',j') A_j+c(i_0,1)\sum_{j=n/2}^{n-1} c(i',j') A_j
$$

如果 $i_0=0$，则有：

$$
FWT[A]_i = c(0,0)\sum_{j=0}^{n/2-1} c(i',j') A_j+c(0,1)\sum_{j=n/2}^{n-1} c(i',j') A_j
$$

$i_0=1$ 则有：

$$
FWT[A]_i = c(1,0)\sum_{j=0}^{n/2-1} c(i',j') A_j+c(1,1)\sum_{j=n/2}^{n-1} c(i',j') A_j
$$

也就是说，我们只需要：

$$
\begin{bmatrix}
c(0,0) & c(0,1) \\
c(1,0) & c(1,1)
\end{bmatrix}
$$

四个数就可以完成变换了。我们称这个矩阵为位矩阵。

***

如果我们要进行逆变换，则需要上面的位矩阵的逆矩阵。

若逆矩阵为 $c^{-1}$，可以通过类似操作得到原数：

$$
A_i = \sum_{j=0}^n c^{-1}(i,j) FWT[A]_j
$$

逆矩阵不一定存在，比如如果有一排 $0$ 或者一列 $0$ 那么这个矩阵就没有逆，我们在构造时需要格外小心。

### 按位或

我们可以构造：

$$
\begin{bmatrix}
1 & 0 \\
1 & 1
\end{bmatrix}
$$

这样满足 $c(i,j)c(i,k)=c(i,j\cup k)$。我们发现，这和我们前面推出的 $FWT[A]=\text{merge}(FWT[A_0], FWT[A_0]+FWT[A_1])$ 一模一样！同理，下面也是一个满足这个条件的矩阵，但我们一般使用上面这个：

$$
\begin{bmatrix}
1 & 1 \\
1 & 0
\end{bmatrix}
$$

虽然下面这个矩阵也满足 $c(i,j)c(i,k)=c(i,j\cup k)$，但这个矩阵存在一排 $0$，不存在逆，所以不合法：

$$
\begin{bmatrix}
0 & 0 \\
1 & 1
\end{bmatrix}
$$

如果我们要进行逆变换，则需要对矩阵求逆，以 **最上面** 这个矩阵为例，得：

$$
\begin{bmatrix}
1 & 0 \\
-1 & 1
\end{bmatrix}
$$

然后按照顺变换的方法，把逆变换矩阵代入即可。

### 按位与

我们可以构造：

$$
\begin{bmatrix}
1 & 1 \\
0 & 1
\end{bmatrix}
$$

这样满足 $c(i,j)c(i,k)=c(i,j\cap k)$。

逆矩阵：

$$
\begin{bmatrix}
1 & -1 \\
0 & 1
\end{bmatrix}
$$

### 按位异或

我们可以构造：

$$
\begin{bmatrix}
1 & 1 \\
1 & -1
\end{bmatrix}
$$

这样满足 $c(i,j)c(i,k)=c(i,j\oplus k)$。

逆矩阵：

$$
\begin{bmatrix}
0.5 & 0.5 \\
0.5 & -0.5
\end{bmatrix}
$$

## FWT 是线性变换

FWT 是线性变换。也就是说，它满足：

$$
FWT[A+B]=FWT[A]+FWT[B]
$$

以及：

$$
FWT[c\cdot A]=c\cdot FWT[A]
$$

## K 维 FWT

其实位运算的本质是对一个 $n$ 维 $\{0,1\}$ 向量的运算。或运算就是每一维取 $\max$。且运算就是每一维取 $\min$。异或运算则是每一维对应相加再 $\bmod 2$。

位运算有个特点：向量的每一位都是独立的。

我们把 $\{0,1\}$ 扩展到 $[0,K)\cap \mathbf{Z}$ 也就是扩展到 $K$ 进制，看看会得到什么？

### max 运算

我们将 $\cup$ 运算拓展到 $K$ 进制，定义 $i\cup j$ 表示按位取 $\max$，有：

$$
c(i,j)c(i,k)=c(i,j\cup k)
$$

若 $j=k$，那么上式又是：

$$
c(i,j)c(i,j)=c(i,j)
$$

也就是说，每一行的 $1$ 必定只能在 $0$ 的前面，如果在后面则不合法了。手玩一下可以发现一组合法构造：

$$
\begin{bmatrix}
1 & 0 & 0 & 0 \\
1 & 1 & 0 & 0 \\
1 & 1 & 1 & 0 \\
1 & 1 & 1 & 1
\end{bmatrix}
$$

求逆可得：

$$
\begin{bmatrix}
1 & 0 & 0 & 0 \\
-1 & 1 & 0 & 0 \\
0 & -1 & 1 & 0 \\
0 & 0 & -1 & 1
\end{bmatrix}
$$

### min 运算

我们将 $\cap$ 运算拓展到 $K$ 进制，定义 $i\cap j$ 表示按位取 $\min$，有：

$$
c(i,j)c(i,k)=c(i,j\cap k)
$$

若 $j=k$，那么上式又是：

$$
c(i,j)c(i,j)=c(i,j)
$$

也就是说，每一行的 $1$ 必定只能在 $0$ 的后面，如果在前面则不合法了。手玩一下可以发现一组合法构造：

$$
\begin{bmatrix}
1 & 1 & 1 & 1 \\
0 & 1 & 1 & 1 \\
0 & 0 & 1 & 1 \\
0 & 0 & 0 & 1
\end{bmatrix}
$$

求逆可得：

$$
\begin{bmatrix}
1 & -1 & 0 & 0 \\
0 & 1 & -1 & 0 \\
0 & 0 & 1 & -1 \\
0 & 0 & 0 & 1
\end{bmatrix}
$$

前两者用得比较少，用得比较多的是：

### 不进位加法

我们将 $\oplus$ 运算拓展到 $K$ 进制，定义 $i\oplus j$ 表示按位相加再 $\bmod K$，有：

$$
c(i,j)c(i,k)=c(i,j\oplus k)
$$

我们构造 $c(i,j)=\omega_{K}^j$，就可以满足要求了：

$$
\omega_{K}^j\omega_{K}^k=\omega_{K}^{j\oplus k}
$$

但是每一行都一样矩阵也没有逆，所以我们可以构造 $c(i,j)=\omega_{K}^{(i-1)j}$ 即可。

有下面这个矩阵：

$$
\begin{bmatrix}
1 & 1 & 1 & \cdots & 1 \\
1 & \omega_{K}^1 & \omega_{K}^2 & \cdots & \omega_{K}^{k-1} \\
1 & \omega_{K}^2 & \omega_{K}^4 & \cdots & \omega_{K}^{2(k-1)} \\
1 & \omega_{K}^3 & \omega_{K}^6 & \cdots & \omega_{K}^{3(k-1)} \\
\vdots & \vdots & \vdots & \ddots & \vdots \\
1 & \omega_{K}^{k-1} & \omega_{K}^{2(k-1)} & \cdots & \omega_{K}^{(k-1)(k-1)}
\end{bmatrix}
$$

此即为 [范德蒙德矩阵](https://en.wikipedia.org/wiki/Vandermonde_matrix)，求逆可得：

$$
\frac{1}{K}\begin{bmatrix}
1 & 1 & 1 & \cdots & 1 \\
1 & \omega_{K}^{-1} & \omega_{K}^{-2} & \cdots & \omega_{K}^{-(k-1)} \\
1 & \omega_{K}^{-2} & \omega_{K}^{-4} & \cdots & \omega_{K}^{-2(k-1)} \\
1 & \omega_{K}^{-3} & \omega_{K}^{-6} & \cdots & \omega_{K}^{-3(k-1)} \\
\vdots & \vdots & \vdots & \ddots & \vdots \\
1 & \omega_{K}^{-(k-1)} & \omega_{K}^{-2(k-1)} & \cdots & \omega_{K}^{-(k-1)(k-1)}
\end{bmatrix}
$$

如果我们题目给出的模数是存在单位根的，我们就可以简单实现。

但是 **单位根在模意义下可能不存在**，所以我们考虑扩域，就是人为地定义一个 $x$，满足 $x^K=1$，然后直接把 $x$ 代入计算，这样每个数都是一个关于 $x$ 的 $k-1$ 次多项式。我们只需要在 $\bmod {x^K-1}$ 下计算即可。那么矩阵可以这么表示：

$$
\begin{bmatrix}
1 & 1 & 1 & \cdots & 1 \\
1 & x^1 & x^2 & \cdots & x^{k-1} \\
1 & x^2 & x^4 & \cdots & x^{2(k-1)} \\
1 & x^3 & x^6 & \cdots & x^{3(k-1)} \\
\vdots & \vdots & \vdots & \ddots & \vdots \\
1 & x^{k-1} & x^{2(k-1)} & \cdots & x^{(k-1)(k-1)}
\end{bmatrix}
$$

但是这么做可能会存在零因子，也就是 **一个数有多种表示方法**，我们无法确定一个数的真实值。

我们考虑不 $\bmod {x^K-1}$ 了，我们 $\bmod$ 分圆多项式 $\Phi_{K}(x)$，他满足 $x$ 的阶为 $k$，且在 $\mathbb{Q}$ 上不可约。所以我们定义上面的计算是在 $\bmod {\Phi_{K}(x)}$ 下进行即可。

还有一个问题是，$\bmod \Phi_{K}(x)$ 常数大（因为 $\Phi$ 本身就是一个多项式）。但是因为 $\Phi_{K}(x)\mid x^k-1$，我们只需要在计算时 $\bmod x^k -1$，最后再 $\bmod \Phi_{K}(x)$ 即可。

## 参考资料

-   [桃酱的算法笔记](https://zhuanlan.zhihu.com/p/41867199)
-   [ZnPdCo 的博客](https://znpdco.github.io/%E7%AE%97%E6%B3%95/2024/05/07/FWT.html)
