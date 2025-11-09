> 本文转载（或修改）自 [奇技淫巧](https://www.luogu.com.cn/article/rjjgz4ng)

> **任何奇技淫巧以能在比赛时使用为标准。**

任何颠覆了传统**且对比赛有帮助**的东西统称奇技淫巧。奇技淫巧抑或是能减少码量，抑或是能优化时空，抑或是能乱搞，~~抑或只是为了装逼~~。目前主要分为如下几个类别：

- **语法类**：新标准中的语法，目前支持到 C++14。也会包含一些冷门语法。
- **STL 类**：包括但不限于 STL、exSTL（如 `pb_ds`、`rope` 等）。~~其实 STL 也算语法。~~
- **随机化类**：随机化函数、随机化算法。
- **卡常类**：顾名思义。
- **位运算类**：顾名思义。~~其实位运算也算卡常。~~

更广义的奇技淫巧包括但不限于：

- 搜索相关。包括但不限于最优化、剪枝。
- 压行相关。这一点人各有志。
- ……

这些限于篇幅，且不完全符合对奇技淫巧的定义，不做讲解。

# 语法类

参考[这篇专栏](./candy.md)以及网上各路博客。

**请注意，任何自带的函数常数都不如手写的，特殊标明除外。**

## C++98

### 库函数

- `find(bg, ed, val)`：返回第一个等于 $\mathit{val}$ 的元素指针。复杂度 $O(N)$。
- **`fill(bg, ed, val)`**：将 $[\mathit{bg},\mathit{ed})$ 的所有元素赋值为 $\mathit{val}$。复杂度 $O(N)$。
  > 当只需对 $n$ 范围的数组初始化而非对整个数组初始化时，笔者常用于替代常数较大的 `memset`。其余部分与 `memset` 相差不大。
- `copy(bg1, ed1, bg2)`：将 $[\mathit{bg}_1,\mathit{ed}_1)$ 的元素复制到 $\mathit{bg}_2$。复杂度 $O(N)$。
  > 与 `memcpy` 作用疑似差别不大。
- **`nth_element(bg, md, ed, cmp = less<>())`**：将 $[\mathit{bg},\mathit{ed})$ 重新排序，将小于等于 $\mathit{md}$ 的元素排在其之前，大于等于的元素排在其之后。复杂度 $O(N)$。第四个参数为比较函数。
- **`max_element/min_element(bg, ed, cmp = less<>())`**：返回指向 $[\mathit{bg},\mathit{ed})$ 中最大/最小元素的指针。复杂度 $O(N)$。第三个参数为比较函数。
  > 求数组最大值就可以直接写：`mx = *max_element(a + 1, a + n + 1)`。
- **`next_permutation/prev_permutation(bg, ed, cmp = less<>())`**：下一个/上一个排列。第三个参数为比较函数。
- **`count(bg, ed, val)`**：返回 $[\mathit{bg},\mathit{ed})$ 中元素 $\mathit{val}$ 的个数，复杂度 $O(N)$。
- `replace(bg, ed, val1, val2)`：将 $[\mathit{bg},\mathit{ed})$ 中所有等于 $\mathit{val}_1$ 的元素替换为 $\mathit{val}_2$，复杂度 $O(N)$。

#### GNU 私货

不在 C++ 标准中，是 GNU 的私货，比赛时可以使用。

- `__lg(x)`：返回 $\lfloor\log_2 x\rfloor$。复杂度 $O(1)$。
  > 与 C++11 中的 `log2(x)` 函数作用相同。
- **`__gcd(x, y)`**：返回 $\gcd(x,y)$。复杂度是小常数的 $O(\log N)$。注意，返回值的符号**不一定**是正。

#### numeric 库

有人说它很好用，个人觉得一般。

- `accumulate(bg, ed, val)`：求区间和与 $\mathit{val}$ 相加的值，但注意返回值的类型和 $\mathit{val}$ 的类型相同，使用时需注意溢出问题。复杂度 $O(N)$。
- `partial_sum(bg1, ed1, bg2)`：对 $[\mathit{bg}_1,\mathit{ed}_1)$ 做前缀和并存入 $\mathit{bg}_2$。复杂度 $O(N)$。
  > 用于原地求前缀和。但一般求前缀和都是边读边求的，所以个人认为作用一般。
- `adjacent_difference(bg1, ed1, bg2)`：与 `partial_sum` 同理，用于原地差分。复杂度 $O(N)$。

#### functional 库

常用的：**`less<>/greater<>`**。简单排序再也不用写 cmp 了。

实际上还有类似的：

- `equal_to<>`：返回 `x == y`。
- `not_equal_to<>`：返回 `x != y`。
- `less_equal<>/greater_equal<>`：返回 `x <= y` 和 `x >= y`。

剩下的个人感觉不常用了，可以自己打开头文件看。

#### cmath 库

- **`abs(x)/fabs(x)`**：返回整型/浮点型的 $|x|$。注意对应清楚类型，避免造成惨案。
- **`fmod(x, y)`**：可以用于浮点数的模运算。**关键时刻有大用。**
- `exp(x)`：返回 $\mathrm e^x$。
- `log(x)`：返回 $\ln x$。注意 $\lg x$ 是 `log10(x)`，请不要对号入座。
- `floor/ceil(x)`：大家都会用，但注意返回值为浮点型。

此外，cmath 库中定义了很多常量，使用方法：

1. 代码开头**在引用头文件前**必须写一句 `#define _USE_MATH_DEFINES`，不写是用不了的，也可以写头文件里剩下的那几个；
2. 然后就可以使用里面的各种常量了。下面直接放头文件，注意有第二个下划线的是除以的意思，如 `M_PI_2` 就是 $\pi/2$，`M_1_PI` 就是 $1/\pi$。比较常用的就是一个 $\pi$ 和一个 $\mathrm e$。

```cpp
#if !defined(__STRICT_ANSI__) || defined(_XOPEN_SOURCE) || defined(_GNU_SOURCE) || defined(_BSD_SOURCE) || defined(_USE_MATH_DEFINES)
#define M_E		2.7182818284590452354
#define M_LOG2E		1.4426950408889634074
#define M_LOG10E	0.43429448190325182765
#define M_LN2		0.69314718055994530942
#define M_LN10		2.30258509299404568402
#define M_PI		3.14159265358979323846
#define M_PI_2		1.57079632679489661923
#define M_PI_4		0.78539816339744830962
#define M_1_PI		0.31830988618379067154
#define M_2_PI		0.63661977236758134308
#define M_2_SQRTPI	1.12837916709551257390
#define M_SQRT2		1.41421356237309504880
#define M_SQRT1_2	0.70710678118654752440
#endif
```

#### __builtin 家族

全都是 GNU 私货，**复杂度 $\boldsymbol{O(\log\log n)}$ 且常数很小，一定比手写快。**

**如果 $\boldsymbol x$ 的类型是 long long，请务必使用 `__builtin_xxxll(x)`。**

- **`__builtin_popcount(x)`**：返回 $x$ 在二进制下 $1$ 的个数。
- `__builtin_parity(x)`：返回 $x$ 在二进制下 $1$ 的个数的奇偶性，快于 `__builtin_popcount(x) & 1`。
- `__builtin_ffs(x)`：返回二进制下最后一个 $1$ 是从右往左第几位。
- `__builtin_ctz(x)`：返回二进制下后导零的个数，$x=0$ 时未定义。
- `__builtin_clz(x)`：返回二进制下前导零的个数，$x=0$ 时未定义。

## C++11

> 从 C++98 到 C++11 是一次重大的飞跃，许许多多非常实用的函数与语法如雨后春笋般出现。

### 新语法

#### nullptr

以后所有的 `NULL` 都写成 `nullptr`。

因为 `NULL` 实际上被实现成了含糊不清的 `#define NULL 0`，`nullptr` 彻底做出了区分。

#### using 替代 typedef

```cpp
// Before
typedef long long ll;
typedef pair<int, int> pii; // CE，模板不是类型

// Now
using pii = pair<int, int>; // 编译成功，与 typedef 有一样的效果
```

#### constexpr 关键字

与 const 的区别：**const 意义为 “只读”，constexpr 意义为 “常量”。**

被 constexpr 修饰的变量/函数在编译时就被计算，效率更高。所以请尽量使用 constexpr。剩余更高深的应用自行 BDFS。

#### auto 关键字

- 用于自动声明变量类型，但注意必须初始化。
- 也可用于函数自动推导返回值类型。（C++14）
- 也可在 Lambda 的形参中出现，但**不能在普通函数的形参中出现**。（C++14）

#### Lambda 表达式

- 语法自行 BDFS，用于快速写一些小函数，自带 inline。
- 捕获列表方面，全局 Lambda 自动为 `&`，局部 Lambda 不会捕获。
- **捕获外部变量尽量使用 `&`，避免无谓的变量拷贝耗费时间。**

#### 基于范围的 for 循环

```cpp
// Before
for (int i = 0; i < g[u].size(); ++i) ... // 好麻烦，常数大（不断调用 size 函数）
for (vector<int>::iterator it = g[u].begin(); it != g[u].end(); ++it) ... // 常数小，但更麻烦

// Now
for (auto v : g[u]) // 舒服
```

- 极其常用于图的遍历等。
- 如果 for 循环内要修改，写成 `for(auto &v : g[u])`。
- 遍历范围为整个数组。

#### emplace

许多 STL 的容器中出现的新函数：

- 对于 set 等容器，`s.insert(x)` 等于 `s.emplace(x)`；
- 对于 stack 和 queue 等容器，`q.push(x)` 等于 `q.emplace(x)`；
- 对于 vector 等容器，`v.push_back(x)` 等于 `v.emplace_back(x)`；
- 以此类推。

几乎所有的 “插入、添加” 型成员函数都有 emplace 的版本。emplace 通过调用构造函数来插入，相较于原来的拷贝方式**效率更优**。所以它的用法也有不一样：

```cpp
vector<pair<int, int>> v; // 以前两个>中间要加个空格，现在也不需要了
// Before
v.push_back(make_pair(a, b));
v.push_back({a, b});
// Now
v.emplace_back(a, b);
```

只要有构造函数，类似的写法同样可应用于结构体。

#### advance 函数

语法：`advance(it, num)`，其中 $\mathit{it}$ 是一个迭代器，$\mathit{num}$ 是一个整数。

作用是将迭代器 $\mathit{it}$ 前进 $\mathit{num}$ 位。**时间复杂度是线性的。**

它有什么用，相信不需要我再多说。

#### shrink_to_fit

- 首先请 BDFS 一下 STL 容器的容量（capacity）和大小（size）的区别。
- 作用就是使其 capacity 调整为 size 的大小。在空间不紧张的情况下用途不大。
- **在空间紧张的情况下用途巨大。——2024/10/6 upd.**

#### decltype 关键字

用于推导返回值类型并将其作为新变量的类型，如：

```cpp
int a = 1953615, b = 198964;
decltype(a + b) c; // 此时 c 是 int 类型
```

除非你真的不知道应该给新变量什么类型，否则可能没用。

### 库函数

#### algorithm 库

- **`shuffle(bg, ed, gen)`**：随机打乱，其中 `gen` 是一个 mt19937。请不要再使用 `random_shuffle`。如果不知道什么是 mt19937 请参阅随机化部分。
- `is_sorted(bg, ed)`：判断 $[\mathit{bg},\mathit{ed})$ 是否升序排序，复杂度 $O(N)$。
- `minmax(a, b)`：返回一个 pair，其 first 为二者较小值，second 为二者较大值。
- `minmax(l)`：$l$ 是一个列表，返回一个 pair，前者为列表最小值，后者为列表最大值。复杂度 $O(|l|)$。
- `minmax_element(bg, ed)`：返回一个 pair，前者为 $[\mathit{bg},\mathit{ed})$ 中最小值，后者为最大值。
- **`max/min(l)`**：其中 $l$ 是一个用大括号括起来的列表，返回 $l$ 中最大/最小的元素。复杂度 $O(|l|)$。
  > 再也不用 max 套 max 了。

#### numeric 库

- **`iota(bg, ed, val)`**：将 $[\mathit{bg},\mathit{ed})$ 中的元素依次赋值为 $\mathit{val},\mathit{val}+1,\mathit{val}+2,\cdots$，复杂度 $O(N)$。
  > 用于原地初始化并查集。

#### iterator 库

- **`prev/next(it)`**：返回迭代器 $\mathit{it}$ 的前驱/后继。
  > 再也不用担心某些迭代器不能 +1-1 的问题了。
- `begin/end(container)`：其中 $\text{container}$ 是一个 STL 容器，作用等于容器自带的 `begin()` 和 `end()` 函数。除了短一个字符没什么区别。

#### functional 库

一句话作用：**把一个函数当作一个变量存起来，可保存为单个变量或数组，可正常遍历。**

个人认为功能不强，语法请自行 BDFS。

#### random 库

详见随机化部分。

#### cmath 库

- `exp2(x)`：返回 $2^x$。
  > 如果 $x$ 是整数，不如用 `1 << x`。
- **`log2(x)`**：返回 $\log_2(x)$。
- **`hypot(x, y)`**：返回 $\sqrt{x^2+y^2}$。
  > 欧氏距离从此一步得。

剩下的还有 STL 中的 tuple、构造函数等，它们要么是作用不大，要么是早已融入我们的代码中，在此不提。

> 这里所说的 “构造函数” 指的是更高级的构造函数，普通的构造函数相信大家都会，更高级的咱也用不着。

## C++14

### 字符串带转义字符

以前的字符串中出现转义字符都需要反斜杠 `\` 来修饰。

现在：`char * str = R"(abc\db'\t")";`。这样声明的字符串 $\mathit{str}=\texttt{abc\\db'\\t"}$。

语法就是 `R"(...)"`，括号内随便写什么都不会被转义。

### 整型字面量分隔符

1. 在整型前面输入 `0b` 代表是二进制，与八进制的 `0`、十六进制的 `0x` 类似。例：`int a = 0b1101101001`。
2. 在整型中插入 `'` 作为分隔符，作用是方便阅读而不影响编译。例：

```cpp
int wdz = 0b1'000'001'000;
int xx = 0x2'0'9; // 都是可以正常编译的
```

比较鸡肋是吧，因为有用的前面或多或少都提了。

# STL 类

STL 是 C++ 独有的最庞大的奇技淫巧。

## STL

### vector

设 $v$ 是一个 vector。

- 便利的初始化：构造函数的第一个参数是长度，第二个参数是初始化的值。相信大家都会。但是如果 $v_1$ 是一个 vector，还可以这么写：`vector<int> v2(v1)`，表示把 $v_1$ 中的元素拷贝到 $v_2$。也可以利用迭代器拷贝一部分。

- 调用 `v.front()` 和 `v.back()` 可以获取到首尾元素的引用。更优雅。

- `v.begin()` 和 `v.end()` 是前闭后开的正序迭代器。`v.rbegin()` 和 `v.rend()` 是前开后闭的逆序迭代器。

- `v.insert()` 可以向 vector 中的某个位置插入元素。**第一个参数永远是一个迭代器**。后面的参数可以是一个元素，可以是一个大括号列表，可以是别的容器的首尾指针/迭代器，甚至可以是一个数 $n$ 加一个元素（表示插入 $n$ 个这样的元素），表示在迭代器前面的位置插入元素。注意**复杂度是线性的**。

- `v.erase()` 与 `insert()` 同理，可以删除某个迭代器或区间的元素，**复杂度也是线性的**。

- `swap()` 函数支持交换两个 vector，**常数复杂度**。

- `v.assign()` 可以将 vector 清空并重新赋值，**线性复杂度，容量只增不减，之前的所有迭代器全部失效**，分三种用法：
 1. `v.assign(count,value)`，用 $\mathit{count}$ 份 $\mathit{value}$ 填充 $v$；
 2. `v.assign(first,last)`，其中 $\mathit{first}$ 和 $\mathit{last}$ 都是指针或迭代器，意为用 $[\mathit{first},\mathit{last})$ 填充 $v$；
 3. `v.assign({})`，意为用一个列表中的元素填充 $v$。

#### 容量相关（2024/10/6 upd.）

vector 真正占空间的是容量，请务必在毒瘤题中注意 vector 的容量问题，及时释放不必要的容量。

- `capacity()`：返回当前 vector 的容量。

- `resize(x)`：将 vector 的**大小**改为 $x$。若：
把大小修改到大于当前容量，会把大小和容量都改到 $x$；
把大小修改但不超过当前容量，只动大小不动容量。
如果把大小改大，会在其之后加入 $0$；如果把大小改小，会删掉多余的元素。

- `reserve(x)`：将 vector 的**容量**增加到 $x$。**如果 $\boldsymbol x$ 小于当前容量，则什么都不做。**

- `shrink_to_fit()`：将当前 vector 的容量修改到和大小相同。

综上所述，在[这道题](https://www.gxyzoj.com/d/hzoj/p/4079)中，我们需要把当前 vector 的容量清空，我们该怎么做呢？设当前 vector 为 $x$。

1. `vector<int>().swap(x)`，意思是构造一个空 vector，将它和 $x$ 交换。因为 `swap()` 可以同时交换大小和容量，且这个构造的 vector 会在使用后就被销毁，所以我们便达到了目的。
2. `x.clear(), x.shrink_to_fit()` 意思是先清空大小，再将容量调整至和大小相同。这样我们也达到了目的。

错误示范：

1. `x.resize(0)`：由于 `resize()` 只改大小不改容量，所以这样写和 `x.clear()` 没有区别。
2. `x.reserve(0)`：由于 `reserve()` 只能增加容量，所以这样写等于没写。

### deque / list

deque 也是**支持常数级别随机访问**的，但增删元素为线性。list 支持常数增删元素，但随机访问为线性。函数与 vector 差不多，但又有差异。

### set / multiset / unordered_set / unordered_multiset

- 大家都会用的对数复杂度的 `insert()` 和 `erase()`。这俩函数其实都是有返回值的，`insert()` 函数返回一个 `pair<iterator, bool>` 其中前者为指向所插入元素（或原本就在容器里的元素）的迭代器，后者表示是否插入成功（set 中若已有元素会失败）。如果传的是元素，`erase()` 函数返回**删除元素的个数**；如果传的是迭代器，返回**下一个元素的迭代器**。

- 注意 multiset 的 `erase()` 函数会删除当前键值的**所有**元素。

- 首尾迭代器方面和 vector 相同。

- `count(x)`、`find(x)`、`lower_bound(x)`、`upper_bound(x)` 大家都会用，注意除 `count(x)` 返回的是 $x$ 的数量外，剩下的返回的都是迭代器。

- unordered 内部是用哈希表实现的，理论插入、删除、查询复杂度 $O(1)$，但容易被卡，详见后文。

#### 求交集/并集/差集/对称差集（2024/10/16 upd.）

用法：前四个参数都是两个集合首尾的迭代器，最后一个参数为 `inserter(c,c.begin())` 的形式，其中 $c$ 是输出结果的 set。

**注意，这些函数只能用于 STL，且使用前提是 STL 容器有序，所以它可以用于有序的 vector，但不能用于 unordered_set。**

- `set_intersection(a.begin(),a.end(),b.begin(),b.end(),inserter(c,c.begin())`：求 $a$ 和 $b$ 的交集。
- `set_union(...)`：求并集。
- `set_difference(...)`：求差集。
- `set_symmetric_difference(...)`：求对称差集。

### map / unordered_map

- 其实也有 multimap 的，但是不常用。

- 与 set 同理，相当于给每个元素附带一个别的值。其实用 map 最常用的就是像数组一样的映射，也就是 `[]` 运算符。但注意，**查询一个元素是否存在不要用 `[]`，而是要用 `count()` 函数。因为用 `[]` 如果不存在会新建一个元素反复使用会造成 TLE。**

- 重载比较运算符（对于 set、multiset、map）：

```cpp
struct cc {
	bool operator () (const int &a, const int &b) const {
		return a > b;
	}
};
set<int, cc> st;
map<int, int, cc> mp;
```

- 重载哈希函数（对于 unordered_set、unordered_multiset、unordered_map）：

> 先要说一下 unordered 系列容器的被卡问题，因为它们底层都是基于哈希表实现的，而 STL 自带的哈希函数很史（优点是**效率高**），所以只需要频繁插入一个特定素数的倍数就能制造哈希冲突，把哈希表卡到 $O(N)$。这个素数在 GCC 6 以前的编译器上是 $126271$，在以后的编译器上是 $107897$。
> 想要解决这个问题就是自己写哈希函数。可以利用与时间有关的库函数生成当前时间，然后把该值加入到哈希函数中，可以 100% 防止被卡。

```cpp
struct hh {
	int operator () (const int &x) const {
		// 你的哈希函数
	}
};
unordered_set<int, hh> st;
unordered_map<int, int, hh> mp;
```

有某些更好的哈希函数，比如：

```cpp
const auto RAND = chrono::high_resolution_clock::now().time_since_epoch().count();
struct hh {
	int operator () (const int &x) const {
		return x ^ RAND;
	}
};
```

这是防止某些处心积虑的人卡 unordered_map 的，如果是 long long 类型，就写成 `return (x >> 32) ^ x ^ RAND;`。但是，它无法使 pb_ds 中的哈希表走出困境。

更强的哈希函数（Codeforces 大佬推荐）：
```cpp
const auto RAND = chrono::steady_clock::now().time_since_epoch().count();
struct hh {
    static int splitmix64(int x) {
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}
	int operator () (const int &x) const {
		return splitmix64(x + RAND);
	}
};
```

~~实测 gp_hash_table 加这个哈希函数跑到飞起。~~

> 2024/11/28 upd.
>
> 写这句话的人完全是在胡扯。实际上在不卡哈希的情况下，**手写哈希函数的效率会慢 1.2 倍左右**。除非你是在 CF 这种毒瘤云集的地方做题，否则不建议手写哈希函数，**甚至不建议用 pb_ds**，一是没有必要，二是可能有副作用。STL 中的东西能应付八成以上的情况，且 pb_ds 从来都不是一道题的必须。如果你非用 pb_ds 不可，只能说明你在乱搞。（逃

如果给 pair 写哈希函数，只需给 first 和 second 都按你的哈希函数哈希一下，**把后者的哈希值右移一位**（看网上博客说的，不知道有什么意义），最后返回二者异或的值。

### stack / queue / priority_queue

- stack 已不建议使用，建议**使用数组模拟栈**，常数小、灵活，关键是清空方便（stack 没有自带的 `clear()` 函数）。
- queue 的用途比 stack 广，比用数组模拟好写。笔者目前遇到的用数组模拟队列只有在某些斜率优化 DP 中。
- priority_queue 直接用，自动排序还是方便。
- 它们的成员函数都是很朴素的一些 `push()`（C++11 后建议改为 `emplace()`）、`pop()`、`empty()`、`size()` 等，以及 `top()` 或 `front()` 访问元素。

### bitset

bitset 严格来说不属于 STL，但它是包含在 `#include <bits/stdc++.h>` 中的。

首先要注意的是，**随机的、跳跃的访问会拖慢 bitset 的效率，使之不如 bool 数组**。所以图论里常见的 $\mathit{vis}$ 数组最好还是写成 bool 数组的形式。

其余情况下，bitset 理论能把复杂度优化到 $O(\frac nw)$，其中 $w$ 是计算机位数，一般是 $32$ 或 $64$。关于 bitset 的详细用法请自行 BDFS。

## exSTL 之 pb_ds

大杀器。引用头文件如下：
```cpp
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp> // 用哈希表
#include <ext/pb_ds/tree_policy.hpp> // 用平衡树
#include <ext/pb_ds/priority_queue.hpp> // 用堆
using namespace __gnu_pbds;
```

### cc_hash_table / gp_hash_table

pb_ds 中的哈希表，实测后者比前者快。**一般用于代码卡常，以笔者当前经验来看，拿 gp_hash_table 代替 unordered_map 准不会慢，前提是手写哈希函数。**

语法与 unordered_map 无异。

裸的 pb_ds 哈希表也是能被卡的（频繁插入 $2^{16}$ 的倍数），具体防卡方法上文有述。

### tree

平衡树，pb_ds 最为强悍之处。[这篇博客](https://www.cnblogs.com/laoshan-plus/p/18370203)讲了其中一部分，下面再补充一些。

语法和 set 无异，可以实现 set / map 所有功能外加

- **`order_of_key(x)`**：返回 $x$ 在平衡树中的排名。
- **`find_by_order(x)`**：返回平衡树中排名 $x$ 的元素。
- **`join(b)`**：将平衡树 $b$ 合并到当前平衡树，重新按照给定的比较函数排序。**要求 $\boldsymbol b$ 中的元素值域和 $\boldsymbol a$ 中的元素值域不能重合。**
  > 不仅仅是不能有相同元素。譬如，若 $a=\{1,2,4\},b=\{3,5\}$，则 $a$ 和 $b$ 同样不能 `join`。
- **`split(v, b)`**：将当前平衡树中 $\le a$ 的元素保留到当前平衡树，$>a$ 的元素分裂到平衡树 $b$。**注意 $\boldsymbol b$ 中原本的元素会被清空。**

可以看出，pb_ds 中的平衡树几乎可以解决所有**按键值分裂**的平衡树题目。

### priority_queue

与 STL 中的 priority_queue 类似，但目前还没有发现它有什么更好的地方，先咕着。

pb_ds 里面有用的也就这么多了。

## exSTL 之 rope

二杀器。不过目前还没有使用它的实例，先咕着。

# 随机化类

既是造数据的帮手，又是骗分的利器。

## 时间函数

一般用于初始化随机种子，也用于对拍求程序运行时间、卡时、手写哈希函数等。

### clock 函数

用法：`clock()`，返回当前程序运行的毫秒数（Windows 下）。注意，**不同系统得到的返回值单位不同**，因此统一成秒的方法是：`(double)clock() / CLOCKS_PER_SEC`。大家都会用，不赘述了。

一般用于卡时、对拍。

### time 函数

用法 `time(0)`，返回从 1970 年 1 月 1 日到现在的秒数，一般用于初始化随机种子。但因为是秒级别的，所以一秒内生成的随机数相同，会影响效率。

### chrono 类

chrono 是 C++11 新增的一个时间类，功能强大，不过我目前只用它的两个函数：

- `chrono::steady_clock::now().time_since_epoch().count()`
- `chrono::high_resolution_clock::now().time_since_epoch().count()`

网上很多文章都说后者是精度最高的时钟，但实际上精度都能到纳秒，根本不用追求二者的精度差异。何况这玩意还是看实现的，在我的电脑上，high_resolution_clock 直接被定义成了 system_clock 的别名。更多时候还是建议使用前者，因为前者产生 $10^{14}$ 级别，而后者产生 $10^{19}$ 级别，前者不太会产生溢出问题。具体还是看用途来决定使用哪个。

### timeb 类

另一种初始化毫秒级别随机种子的方法，**注意在 Linux 下不能使用。**

```cpp
struct _timeb T;
_ftime(&T);
mt19937 wdz(T.millitm);
```

## 随机化函数

大家都会使用 `rand()`，但是 Windows 下 `rand()` 的值域只有 $32767$。如果使用 `rand() * rand()` 的手法生成更大的随机数，这样生成的随机数极不均匀。且众所周知的种种原因，`rand()` 不再推荐使用。

### mt19937

推荐使用的是 mt19937，它的优点无需更多赘述。直接定义 `mt19937` 能生成 unsigned int 范围内的随机数，定义 `mt19937_64` 能生成 unsigned long long 类型的随机数。例：

```cpp
mt19937 wdz;
cout << wdz() << '\n';
```

然而，你会发现这样每次输出的随机数是相同的，因此需要初始化随机种子。初始化方法：`mt19937 wdz(1953615)`，这样就将 `1953615` 作为随机化种子。和上面的时间函数结合，就是毫秒级别的随机数种子。

### uniform_int_distribution

众所周知，用 `wdz() % 1000000000` 这样的方法生成的随机数是不均匀的，会偏小。这个函数可以生成真正均匀的随机数。

用法：`uniform_int_distribution<>(1, 1e9)(wdz)`，可以生成均匀分布于 $[1,10^9]$ 的随机整数。其中尖括号里不填表示 int 类型，需要 long long 就填成 `long long` 即可。中间的就填范围，后面的 `wdz` 是一个 mt19937。

**经过实测，这个函数的常数比较大，如果用在代码里，请注意它的效率。**

### uniform_real_distribution

用法类似，给定的两个边界用于生成 $[a,b)$ 的随机数，尖括号里填浮点数类型。一般用于模拟退火。

以 `uniform` 开头的其他函数可以生成非均匀分布的随机数，如正态分布等，用途不大。

## 随机化算法

用于求解**最优解问题**的大杀器，也是求解部分**期望题**的最有效骗分手段。针对很逊的出题人，这种方法可以骗取极高的分数。随机化算法的准确性依赖数据范围，针对规模小的数据准确率很高。如果是用于求解期望题，则需要最终输出的答案**不超过两位小数**，准确率就非常高了。

首先是最常见的随机化 + 卡时，这种无需多言，按照题意模拟，最后取最优解即可。

然后是高级一些的模拟退火，参见洛谷上的[一篇专栏](https://www.luogu.com.cn/article/2mnd34y4)。

# 卡常类

收录一些也不知有没有用的卡常小寄巧。其中**大多数应该都可以靠 O2 优化**，按个人喜好。不按照效果排序。

- 输入输出优化，不再赘述。cout 时 `endl` 写成 `'\n'`。

- 所有的 `i++` 改为 `++i`。据说是因为前者的底层实现不好，但 O2 应该能优化。

- 将简单的 if 语句改为三目运算符或逻辑表达式，据说是因为 if 的常数大。这里重点说一下后者，我们知道 C++ 的逻辑运算符 `&&` 和 `||` 是由执行的先后顺序的，即从左到右执行。也就是说，如果前者已经足以让这个表达式为真或假，就不会执行后面的语句。利用这个特性，我们就有：
  1. 所有的 `if (a) b;` 可以改为 `a && b`。
  2. 所有的 `if (!a) b;` 可以改为 `a || b`。
  这样理论上能优化一些常数的，也可以用来压行。需要注意的是，**表达式 b 的返回值必须能转为 bool 类型**，所以我们可以用逗号分隔开，利用逗号表达式返回值为最后一项的特性即可。

- 尽量减少局部变量的定义，比如在循环内定义变量可以移到循环外面。

- 用 constexpr 关键字定义常量，可以促使该常量在编译时计算。

- 各种 size 类函数尽量不要重复调用，比如尽量不要写 `for (int i = 0; i < s.size(); ++i)`，因为它们的常数一般都不小，有些的复杂度甚至是线性的。

- 计数类题目的加法取模优化，即：`a = (a + b) % p` 改为 `a = a + b >= p ? a + b - p : a + b`。因为取模的效率很低，对于这种加法直接判断会好很多。减法也是类似的，如 `a = (a - b + p) % p` 改为 `a = a - b < 0 ? a - b + p : a - b`。

- vector 的容量优化。前文提到过 vector 容量和大小的区别，vector 看似是动态的，实际上它每次加入元素时，如果当前容器的大小超过了容量，它就会重新申请内存，而这个申请内存的过程是很浪费时间的。所以对于已知的需要大量插入的 vector，合理地使用 `reserve()` 函数可以极大地优化它的常数。

# 位运算类

直接看[这里](https://www.cnblogs.com/laoshan-plus/p/18365118)。