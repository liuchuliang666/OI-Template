> author: [C0C](https://www.cnblogs.com/C0Cnotes/articles/18756826)

假如你需要使用两种颜色给一个正四面体的四个顶点着色，试问存在多少种不同的着色方案？正四面体有 $4$ 个顶点，每个顶点的颜色都有 $2$ 种不同选择，于是可以得出一个答案是 $2^4=16$。这是在四面体在空间中固定的前提下得出的结论。

现在这个正四面体可以在空间中转动，那么由于正四面体有非常好的对称性质，因此只有每种颜色的顶点数可以用来区分不同着色方案。此时可以给出 $5$ 种着色方案，分别为其中一种颜色着 $0,1,2,3,4$ 个顶点。

又假如使用两种颜色给正方形的四个顶点着色，显然在正方形固定的情况下有 $16$ 种着色方案。

现在允许正方形转动，由于正方形的对称性虽不如正四面体但依然很强，我们可以有以下 $6$ 种情况，以二阶矩阵的形式展现：

$$
\begin{bmatrix}
    1 & 1\\
    1 & 1\\
\end{bmatrix}
\begin{bmatrix}
    0 & 0\\
    0 & 0\\
\end{bmatrix}
\begin{bmatrix}
    0 & 1\\
    1 & 1\\
\end{bmatrix}
\begin{bmatrix}
    0 & 0\\
    0 & 1\\
\end{bmatrix}
\begin{bmatrix}
    0 & 0\\
    1 & 1\\
\end{bmatrix}
\begin{bmatrix}
    1 & 0\\
    0 & 1\\
\end{bmatrix}
$$

如果允许四面体和正方形自由转动，那么给顶点着色的 $2^4=16$ 种方法被分成一些部分，使得统一部分钟的两种着色视为相同（着色是*等价的*），而不同部分中的两种着色为不同的（着色是*不等价的*）。因此，不等价的着色个数就是不同部分的个数。本文的目的就在于建立和阐明在对称情形下计算不等价着色的技术。

## 置换群与着色

### 置换

设 $X$ 为有限集。不失一般性，我们取 $X$ 的为由前 $n$ 个正整数组成的集合 $\{1,2,\cdots ,n\}$。

$X$ 的**置换** $i_1,i_2,\cdots ,i_n$ 可以看成是 $X$ 到其自身的一对一函数，其定义为

$$
f:X \rightarrow X
$$

其中

$$
f(1)=i_1,f(2)=i_2,\cdots ,f(n)=i_n
$$

根据[**鸽巢原理**]()，一对一的函数 $f:X \rightarrow X$ 是满射。为了强调置换可视为函数，我们也用 $2 \times n$ 阵列

$$
\begin{pmatrix}
    1 & 2 & \cdots & n\\
    i_1 & i_2 & \cdots & i_n\\
\end{pmatrix}
$$

来表示这个置换。*在本文中，这个函数在整数 $k$ 处的值 $i_k$ 写在 $k$ 的下面*。

我们把 $\{1,2,\cdots ,n\}$ 的所有 $n!$ 个置换构成的集合记为 $S_n$。

现在我们已经视置换为函数，那么它们就可以合成。若

$$
f =
\begin{pmatrix}
    1 & 2 & \cdots & n\\
    i_1 & i_2 & \cdots & i_n\\
\end{pmatrix}
$$

和

$$
g =
\begin{pmatrix}
    1 & 2 & \cdots & n\\
    j_1 & j_2 & \cdots & j_n\\
\end{pmatrix}
$$

是 $\{1,2,\cdots ,n\}$ 的两个置换，则它们的**合成**按照先 $f$ 后 $g$ 的顺序防止得到一个新的置换

$$
g \circ f =
\begin{pmatrix}
    1 & 2 & \cdots & n\\
    i_1 & i_2 & \cdots & i_n\\
\end{pmatrix}
\circ
\begin{pmatrix}
    1 & 2 & \cdots & n\\
    j_1 & j_2 & \cdots & j_n\\
\end{pmatrix}
$$

其中

$$
(g\circ f)(k)=g(f(k))=j_{i_k}
$$

函数的合成定义了 $S_n$ 上的一个**二元运算：如果 $f,g \in S_n$，则 $g \circ f \in S_n$**。

此二元运算满足**结合律**。

我们通常用幂符号表示一个置换与它自己的合成：

$$
f^k=f \circ f \circ \cdots \circ f\;(k\;个\;f)
$$

**恒等置换**就是各整数对应到它自身的 $\{1,2,\cdots ,n\}$ 的置换 $\iota$：

$$
\iota(k)=k,对所有的\;k=1,2,\cdots ,n\\
\Leftrightarrow \\
\iota = \begin{pmatrix}
    1 & 2 & \cdots & n\\
    1 & 2 & \cdots & n\\
\end{pmatrix}
$$

显然有

$$
\iota \circ f=f \circ \iota = f
$$

对于 $S_n$ 中的所有置换 $f$ 成立。

**逆函数**

$$
f^{-1} \in S_n
$$

满足

$$
如果\;f(s)=k，那么\;f^{-1}(k)=s
$$

我们可以通过交换 $f$ 的 $2 \times n$ 矩阵的第一行与第二行，并重新排列各列使得第一行的整数以自然顺序 $1,2, \cdots ,n$ 出现，便得到了 $f^{-1}$ 的 $2 \times n$ 矩阵。

对于每个置换 $f$，定义 $f^0=\iota$。显然有 $\iota ^{-1}=\iota$。

### 置换群

如果 $S_n$ 中的置换的非空子集 $G$ 满足如下三条性质，则定义它为 $X$ 的置换的群（简称**置换群**）：

1. *合成运算的封闭性*：对 $G$ 中所有的置换 $f$ 与 $g$，$f \circ g$ 也属于 $G$。
2. *单位元*：$S_n$ 中的恒等置换 $\iota$ 属于 $G$。
3. *逆元的封闭性*：对 $G$ 中的每一个置换 $f$，它的逆 $f^{-1}$ 也属于 $G$。

$X=\{1,2, \cdots ,n\}$ 的所有置换的集合 $S_n$ 是一个置换群，称它为 *$n$ 阶对称群*。特别地，仅含恒等置换的集合 $G-\{ \iota \}$ 是一个置换群。

每一个置换群满足*消去律*：

$$
f \circ g = f \circ h\;意味着\;g = h
$$

设 $\Omega$ 是一个几何图形，$\Omega$ 到它自身的一个几何运动或全等称为 $\Omega$ 的一个对称。每个对称可以看作是顶点、边及三维情形下的面上的一个置换。于是我们可以推出 $\Omega$ 的堆成就是它的角点上的置换群 $G_c$、边上的置换群 $G_E$ 和三维情形下的面上的置换群 $G_F$。

我们可以得到对于任意的 $n \geq 3$ 的正 $n$ 角形的对称群。除 $n$ 个旋转 $\rho _n^0 = \iota,\rho _n, \cdots ,\rho _n^n$，还有 $n$ 个反射 $\tau _1,\tau _2, \cdots ,\tau _n$。
+ 如果 $n$ 为偶数，则有 $\frac{n}{2}$ 个关于对角点的反射和 $\frac{n}{2}$ 个关于对边中点连线的反射。
+ 如果 $n$ 为奇数，则有 $n$ 个关于对角点与其对边的反射。

关于 $\{1,2,\cdots ,n\}$ 的 $2n$ 个置换形成的群

$$
D_n = \{\rho _n^0 = \iota,\rho _n,\cdots ,\rho _n^{n-1},\tau _1,\tau _2, \cdots ,\tau _n\}
$$

即为一个阶为 $2n$ 的二面体群的一个实例。

### 着色

$X$ 的一种*着色*是给 $X$ 的每个元素指定一种颜色的分配方案。设 $\mathcal{C}$ 是 $X$ 的一个着色集合。集合 $\mathcal{C}$ 可以使 $X$ 的任意着色集合，只要求 $G$ 按下面所描述的方式把 $\mathcal{C}$ 中的一种着色对应到 $\mathcal{C}$ 的另一种着色。

设 $c$ 是 $X$ 的一种着色，$1,2,\cdots ,n$ 的颜色分别记为 $c(1),c(2),\cdots ,c(n)$ 。令

$$
f =
\begin{pmatrix}
    1 & 2 & \cdots & n\\
    i_1 & i_2 & \cdots & i_n\\
\end{pmatrix}
$$

是 $G$ 中的一个置换，那么定义 $f * c$ 为使得 $i_k$ 具有颜色 $c(k)$ 的着色，即

$$
(f * \textbf{c})(i_k) = c(k) (k = 1,2,\cdots ,n)\\
也可以写成\\
(f * \textbf{c})(l) = c(f^{-1}(l)) (l = 1,2,\cdots ,n)
$$

有性质

$$
(g \circ f) * \textbf{c} = g * (f * \textbf{c})
$$

给出着色等价的一般定义。令 $G$ 是作用在集合 $X$ 上的置换群。令 $\mathcal{C}$ 是 $X$ 的一个着色集合，使得对于 $G$ 中任意元 $f$ 和 $\mathcal{C}$ 中任意元 $\textbf{c}$，$X$ 的着色 $f * \textbf{c}$ 仍属于 $\mathcal{C}$。如果存在 $G$ 中的置换 $f$ 和 $\mathcal{C}$ 中的着色 $\textbf{c}_1,\textbf{c}_2$，使得

$$
f * \textbf{c}_1 = \textbf{c}_2\\
$$

则 $\textbf{c}_1$（在G的作用下）等价于 $\textbf{c}_2$，写作

$$
\textbf{c}_1 \sim \textbf{c}_2
$$

等价具有 **自反性、对称性、传递性**。

## Burnside 定理

设 $G$ 是 $X$ 的置换群，$\mathcal{C}$ 是 $X$ 的着色集合，且 $G$ 作用在 $\mathcal{C}$ 上。适当选取 $f$ 与 $\textbf{c}$，可使得

$$
f * \textbf{c} = \textbf{c}
$$

我们可以得到使着色 $\textbf{c}$ 保持不变的 $G$ 中的所有置换的集合

$$
G(\textbf{c})=\{f:f \in G,f * \textbf{c} = \textbf{c}\}
$$

以及在 $f$ 的中用下使着色 $\textbf{c}$ 保持不变的 $\mathcal{C}$ 中所有着色的集合

$$
\mathcal{C}(f)=\{\textbf{c}:\textbf{c} \in \mathcal{C},f * \textbf{c} = \textbf{c}\}
$$

我们称 $G(\textbf{c})$ 为 $\textbf{c}$ 的*稳定核*。任何着色的稳定核也形成一个置换群。

***定理 1**：对于每一种着色 $\textbf{c}$，$\textbf{c}$ 的稳定核 $G(\textbf{c})$ 是置换群，而且对 $G$ 中的人一直换 $f$ 与 $g$，$g * \textbf{c} = f * \textbf{c}$ 当且仅当 $f^{-1} \circ g$ 属于 $G(\textbf{c})$。*

***推论 1**： 设 $\textbf{c}$ 为 $\mathcal(C)$ 中的一种着色，那么与 $\textbf{c}$ 等价的着色数*

$$
|\{f*\textbf{c}：f \in G\}|
$$

*等于 $G$ 中的置换个数除以 $\textbf{c}$ 的稳定核中的置换个数，即*

$$
\frac{|G|}{|G(\textbf{c})|}
$$

***定理 2（Burnside）**：设 $G$ 是 $X$ 的置换群，而 $\mathcal{C}$ 是 $X$ 中非等价着色数 $N(G,\mathcal{C})$ 由下式给出：*

$$
N(G,\mathcal{C}) = \frac{1}{|G|} \sum_{f \in G} |\mathcal{C}(f)|
$$

*换言之，$\mathcal{C}$ 中非等价的着色数等于在 $G$ 中的置换作用下保持不变的着色的平均数。*

## Pólya 计数公式

Burnside定理可以成功地计算置换群 $G$ 作用在着色集 $\mathcal{C}$ 中颜色不变的着色数 $|\mathcal{C}(f)|$。通过考虑循环结构，这一计算会变得容易进行。

设 $f$ 是 $X$ 的一个置换， $D_f = (X,A_f)$ 是顶点集为 $X$ 且弧集为 $A_f=\{(i,f(i)):i \in X\}$ 的有向图。$A_f$ 可以划分成若干有向圈，且每个顶点恰好只属于一个有向圈。

如果在一个置换中某些元素以循环的方式置换且余下的元素保持不变，则称其为**循环置换**，简称**循环**。我们称有 $k$ 个元素的循环为 $k$ 循环。

于是对应于合成运算，$f$ 有唯一的循环因子分解

$$
f = [i_1,i_2, \cdots,i_p] \circ [j_1,j_2, \cdots,j_p] \circ \cdots \circ [l_1,l_2, \cdots,l_p]
$$

记置换 $f$ 的循环分解中的循环个数为 $\#(f)$。

***定理 3**：设 $f$ 是集合 $X$ 的置换。假如我们用 $k$ 种颜色对 $X$ 的元素进行着色。$\mathcal{C}$ 是 $X$ 的所有着色的集合。则 $f$ 中保持着色不变的着色数为*

$$
|\mathcal{C(f)}|=k^{\#(f)}
$$

---

实际上到这一步，我们利用

$$
N(G,\mathcal{C}) = \frac{1}{|G|} \sum_{f \in G}{\#(f)}
$$

就可以解决大部分实际在题目中遇到的问题。

---

设 $f$ 是含有 $n$ 个元素的集合 $X$ 的置换。设 $f$ 的循环因子分解有 $e_i$ 个 $i$ 循环。称 $(e_1,e_2, \cdots,e_n)$ 为 $f$ 的类型记为 $type(f) = (e_1,e_2, \cdots,e_n)$。

我们现在想仅通过类型来区分置换，所以引进 $n$ 个未定元 $z_1,z_2, \cdots,z_n$。定义 $f$ 的**单项式**为 $mon(f) = z_1^{e_1}z_2^{e_2} \cdots z_n^{e_n}$。

得到关于 $G$ 中的置换按照类型的生成函数

$$
\sum_{f \in G}mon(f) = \sum _{f\in G}z_1^{e_1}z_2^{e_2} \cdots z_n^{e_n}
$$

$G$ 的 **循环指数**定义为该生成函数除以 $|G|$，即

$$
P_G(z_1,z_2, \cdots,z_n) = \frac{1}{|G|} \sum _{f\in G}z_1^{e_1}z_2^{e_2} \cdots z_n^{e_n}
$$

***定理 4**：设 $X$ 是有 $n$ 个元素的集合，假设我们用 $k$ 种可用的颜色对 $X$ 的元素进行着色。令 $\mathcal{C}$ 是 $X$ 的所有 $k^n$ 中着色的集合，$G$ 是 $X$ 的置换群。则非等价的着色数是用 $z_i=k(i=1,2, \cdots,n)$ 带入 $G$ 的循环指数中而得到的值，即*

$$
N(G,\mathcal{C}) = P_G(k,k, \cdots,k)
$$

现在我们看看怎么利用 $G$ 的循环指数，来确定当个颜色使用特定次数时非等价的着色数。

我们给出每种颜色有指定元素个数的非等价着色数的生层函数。将颜色看成变量 $u_1,u_2, \cdots,u_k$。

***定理 5**：设 $X$ 是元素集合， $G$ 是 $X$ 的置换群，$\{u_1,u_2, \cdots,u_k\}$ 是 $k$ 中颜色的集合 $\mathcal{C}$ 是 $X$ 的任意着色集。这时，针对各颜色的数目的 $\mathcal{C}$ 的非等价着色数的生成函数是*

$$
P_G(z_1,z_2, \cdots,z_n)
$$

*这一表达式是对循环指数 $P_G(z_1,z_2, \cdots,z_n)$ 通过变量代换*

$$
z_j=u_1^j+ \cdots + u_k^j (j=1,2, \cdots ,n)
$$

*而得到的。换言之，$P_G(z_1,z_2, \cdots,z_n)$ 中*

$$
u_1^{p_1}u_2^{p_2} \cdots u_n^{p_n}
$$

*的系数等于 $\mathcal{C}$ 中把 $X$ 的 $p_1$ 个元素着色成颜色 $u_1$，$p_2$ 个元素着色成颜色 $u_2$，$\cdots \, \cdots$，$p_n$ 个元素着色成颜色 $u_n$ 的非等价的着色数。*