# datagenerator 库使用手册

> 本库修改自 [一扶苏一的数据生成库](https://www.luogu.com.cn/article/exdkjvcu)。

## 代码

??? code "实现"
    ```cpp
    --8<-- "docs/Lang/code/datagenerator.hpp"
    ```

## 快速开始

```cpp
#include "datagenerator.hpp"
using namespace util;

int main() {
    setSeed(time(0));  // 设置随机种子

    // 生成 10 个测试点
    DataGenerator::run("test", 10, 2, "std", "data", "sample",
        [](int testId) {
            int n = rangeRand(1, 100);
            println(n);
            auto arr = genArr(n, 100, mod1<int>);
            printArr(arr);
        }
    );
}
```

## 随机数生成

### `setSeed(seed)`
**用途**：设置随机数种子

**参数**：

- `seed`：随机种子，相同种子产生相同随机序列

```cpp
setSeed(123);        // 固定种子，用于对拍
setSeed(time(0));    // 时间种子，每次不同
```

### `modx(x)`
**用途**：生成 `[0, x-1]` 的随机整数

**参数**：

- `x`：上限（不包含）

```cpp
int idx = modx(5);   // 0,1,2,3,4 中的一个
char c = 'a' + modx(26);  // 随机小写字母
```

### `mod1(x)`
**用途**：生成 `[1, x]` 的随机整数

**参数**：

- `x`：上限（包含）

```cpp
int dice = mod1(6);  // 骰子：1~6
int n = mod1(100);   // 数据规模：1~100
```

### `rangeRand(l, r)`
**用途**：生成 `[l, r]` 的随机整数

**参数**：

- `l`：下限
- `r`：上限

```cpp
int x = rangeRand(-100, 100);  // -100~100
int len = rangeRand(5, 20);    // 字符串长度5~20
```

### `randRange(L, R)`
**用途**：生成 `[L, R]` 内的随机区间 `[l, r]`

**参数**：

- `L, R`：区间范围

**返回值**：`pair<l, r>`，保证 `l <= r`

```cpp
auto [l, r] = randRange(1, n);  // 生成查询区间
cout << l << " " << r << endl;
```

### `randChar()`
**用途**：生成随机小写字母

**返回值**：`'a'` ~ `'z'`

```cpp
char c = randChar();  // 随机字母
string s = genStr(10, randChar);  // 10个随机字母
```

## 数组与字符串

### `genArr(len, lim, genFunc)`
**用途**：生成指定长度的数组

**参数**：

- `len`：数组长度
- `lim`：传递给生成函数的参数
- `genFunc`：元素生成函数

```cpp
// 10个[1,100]的随机数
auto arr = genArr(10, 100, [](int x) {
    return rangeRand(1, x);
});

// 5个随机字符
auto chars = genArr(5, 'z', [](char lim) {
    return 'a' + modx(26);
});
```

### `genStr(len, genChar)`
**用途**：生成随机字符串

**参数**：

- `len`：字符串长度
- `genChar`：字符生成函数，默认小写字母

```cpp
string s1 = genStr(10);                    // 10个小写字母
string s2 = genStr(5, []() {               // 5个数字
    return '0' + modx(10);
});
string s3 = genStr(8, []() {               // 8个大写字母
    return 'A' + modx(26);
});
```

### `choice(container)`
**用途**：从容器中随机选择一个元素

**参数**：

- `container`：`vector` 或 `array`

```cpp
vector<int> v = {1,2,3,4,5};
int x = choice(v);  // 随机选一个

vector<string> ops = {"add", "del", "query"};
string op = choice(ops);  // 随机操作
```

### `shuffleVec(vec)`
**用途**：随机打乱 `vector`

**参数**：

- `vec`：要打乱的 `vector`

```cpp
vector<int> perm = {1,2,3,4,5};
shuffleVec(perm);  // 随机排列
```

### `printArr(arr, split, end)`
**用途**：输出数组

**参数**：

- `arr`：要输出的数组
- `split`：元素分隔符，默认空格
- `end`：结束符，默认换行

```cpp
vector<int> arr = {1,2,3,4,5};
printArr(arr);          // 输出: 1 2 3 4 5
printArr(arr, ", ");    // 输出: 1, 2, 3, 4, 5
```

### `println(args...)`
**用途**：输出多个值，空格分隔

**参数**：可变参数

```cpp
println(1, "hello", 3.14);  // 输出: 1 hello 3.14
println(n, m);              // 输出: n m
```

## 图论生成

### Graph 类基础

```cpp
using namespace util::graph;

Graph<int> g(5);        // 5个顶点的图
g.addEdge(1, 2, 10);    // 添加边1->2，权重10
g.addEdge(2, 3);        // 添加边2->3，权重1

// 输出格式
g.printWithInfo(true);  // 输出: n m 和所有边(带权重)
g.printTree(true);      // 输出: n 和所有边(带权重)
```

### `genTree(n, root, parentLess, weight, ...)`
**用途**：生成随机树

**参数**：

- `n`：顶点数
- `root`：根节点，默认1
- `parentLess`：是否要求父节点编号小于子节点
- `weight`：权重生成器，可以是一个 pair 表示范围，可以是一个固定的数，也可以是一个函数

```cpp
auto tree1 = genTree(10);                    // 随机树
auto tree2 = genTree(10, 1, true, {1,100}); // 父节点小于子节点，权重1~100

tree1.printTree(true);  // 输出树
```

### `genChain(n, weight, ...)`
**用途**：生成链

**参数**：

- `n`：顶点数
- `weight`：权重生成器，可以是一个 pair 表示范围，可以是一个固定的数，也可以是一个函数

```cpp
auto chain = genChain(10, {1,50});  // 10个顶点的链，权重1~50
chain.printWithInfo(true);
```

### `genStar(n, center, weight, ...)`
**用途**：生成菊花图（星图）

**参数**：

- `n`：顶点数
- `center`：中心节点，0 表示随机
- `weight`：权重生成器，可以是一个 pair 表示范围，可以是一个固定的数，也可以是一个函数

```cpp
auto star1 = genStar(10);           // 随机中心
auto star2 = genStar(10, 5);        // 中心为5
star1.printWithInfo(true);
```

### `genCycle(n, weight, ...)`
**用途**：生成环

**参数**：

- `n`：顶点数
- `weight`：权重生成器，可以是一个 pair 表示范围，可以是一个固定的数，也可以是一个函数

```cpp
auto cycle = genCycle(10, {1,100});  // 10个顶点的环
cycle.printWithInfo(true);
```

### `genCompleteGraph(n, weight, ...)`
**用途**：生成完全图

**参数**：

- `n`：顶点数
- `weight`：权重生成器，可以是一个 pair 表示范围，可以是一个固定的数，也可以是一个函数

```cpp
auto complete = genCompleteGraph(5);  // 5个顶点的完全图
complete.printWithInfo(true);
```

### `genBipartiteGraph(left, right, m, weight, ...)`
**用途**：生成二分图

**参数**：

- `left`：左部点数
- `right`：右部点数
- `m`：边数
- `weight`：权重生成器，可以是一个 pair 表示范围，可以是一个固定的数，也可以是一个函数

```cpp
// 5左5右10条边的二分图
auto bipartite = genBipartiteGraph(5, 5, 10, {1,100});
bipartite.printWithInfo(true);
```

### `genUndirectedGraph(n, m, weight, multi, selfLoop, connected)`
**用途**：生成无向图

**参数**：

- `n`：顶点数
- `m`：边数
- `weight`：权重生成器，可以是一个 pair 表示范围，可以是一个固定的数，也可以是一个函数
- `multi`：是否允许多重边
- `selfLoop`：是否允许自环
- `connected`：是否连通

```cpp
// 10顶点15边的连通无向图
auto graph = genUndirectedGraph(10, 15, {1,100}, false, false, true);
graph.printWithInfo(true);
```

### `genDirectedGraph(n, m, weight, ...)`
**用途**：生成有向图

**参数**：同无向图

```cpp
auto digraph = genDirectedGraph(10, 20, {1,50});  // 10顶点20边有向图
digraph.printWithInfo(true);
```

### `genDAG(n, m, weight, ...)`
**用途**：生成有向无环图

**参数**：同有向图

```cpp
auto dag = genDAG(10, 15, {1,100});  // 10顶点15边DAG
dag.printWithInfo(true);
```

### `genSpfaKiller(n, m, posWeight, negWeight, negRatio, ...)`
**用途**：生成卡 SPFA 的图

**参数**：

- `n, m`：顶点和边数
- `posWeight`：正权边权重
- `negWeight`：负权边权重
- `negRatio`：负权边比例

```cpp
// 100顶点200边，20%负权边
auto killer = genSpfaKiller(100, 200, {1,10}, []{ return -1; }, 0.2);
killer.printWithInfo(true);
```

### `printParentArray(parent, root)`
**用途**：输出父节点数组

**参数**：

- `parent`：父节点数组，`parent[i]` 是节点 `i+1` 的父节点
- `root`：根节点，默认1

```cpp
vector<int> parent = {0,1,1,2,2};  // 节点2~5的父节点
Graph<>::printParentArray(parent);  // 输出: 1 1 2 2
```

## 🚀 数据生成框架

### `DataGenerator::run(...)`
**用途**：运行完整数据生成流程

**参数**：
- `dataName`：数据文件名前缀
- `testCount`：测试数据数量
- `sampleCount`：样例数据数量
- `stdName`：标程名称
- `dataFolder`：测试数据目录
- `sampleFolder`：样例数据目录
- `makeDataFunc`：测试数据生成函数，默认啥也不做
- `makeSampleFunc`：样例数据生成函数，默认啥也不做
- `testGroupFunc`：测试数据组数函数，传入测试点编号，默认返回 0
- `sampleGroupFunc`：样例数据组数函数，传入测试点编号，默认返回 0
- `outputTestId`：是否输出测试点编号

```cpp
DataGenerator::run(
    "data", 10, 2, "std", "data", "sample",
    [](int testId) {
        int n = rangeRand(1, 100);
        println(n);
        // ... 生成数据
    },
    [](int testId) {
        // 样例数据，通常较小
        println(5);
        println(1, 2, 3, 4, 5);
    },
    [](int testId) { return 0; },  // 单组测试
    [](int testId) { return 0; },  // 单组样例
    false
);
```

## 综合实例

### 实例1：生成树相关问题数据

```cpp
void generateTreeProblem(int testId) {
    using namespace util::graph;

    // 根据测试点调整数据规模
    int n;
    if (testId <= 3) n = rangeRand(5, 10);
    else if (testId <= 6) n = rangeRand(50, 100);
    else n = rangeRand(500, 1000);

    // 生成随机树
    auto tree = genTree(n, 1, false, {1, 100});
    tree.printTree(true);  // 输出树

    // 生成查询
    int q = rangeRand(1, 10);
    println(q);
    for (int i = 0; i < q; i++) {
        int u = mod1(n), v = mod1(n);
        println(u, v);
    }
}

int main() {
    DataGenerator::run("tree", 10, 2, "sol_tree", "data", "sample", generateTreeProblem);
    return 0;
}
```

### 实例2：生成图论最短路径数据

```cpp
void generateShortestPath(int testId) {
    using namespace util::graph;

    int n, m;
    if (testId <= 3) {
        n = rangeRand(5, 10);
        m = rangeRand(5, 20);
    } else {
        n = rangeRand(100, 500);
        m = rangeRand(200, 1000);
    }

    // 生成连通无向图
    auto graph = genUndirectedGraph(n, m, {1, 1000}, false, false, true);
    graph.printWithInfo(true);

    // 起点终点
    int s = mod1(n), t = mod1(n);
    println(s, t);
}

int main() {
    DataGenerator::run("graph", 10, 2, "sol_graph", "data", "sample", generateShortestPath);
    return 0;
}
```

### 实例3：生成数组查询问题数据

```cpp
void generateArrayQuery(int testId) {
    int n, q;
    if (testId <= 3) {
        n = rangeRand(5, 10);
        q = rangeRand(3, 5);
    } else if (testId <= 6) {
        n = rangeRand(100, 500);
        q = rangeRand(10, 20);
    } else {
        n = rangeRand(1000, 10000);
        q = rangeRand(50, 100);
    }

    // 生成数组
    println(n, q);
    auto arr = genArr(n, 1000000, [](int lim) {
        return rangeRand(1, lim);
    });
    printArr(arr);

    // 生成查询
    for (int i = 0; i < q; i++) {
        int op = mod1(2);  // 操作类型
        if (op == 1) {
            // 修改操作
            int pos = mod1(n);
            int val = rangeRand(1, 1000000);
            println(1, pos, val);
        } else {
            // 查询操作
            auto [l, r] = randRange(1, n);
            println(2, l, r);
        }
    }
}

int main() {
    DataGenerator::run("array", 10, 2, "sol_array", "data", "sample", generateArrayQuery);
    return 0;
}
```

### 实例4：生成多组测试数据

```cpp
void generateSingleTestCase(int testId) {
    int n = rangeRand(1, 100);
    println(n);
    auto arr = genArr(n, 100, mod1<int>);
    printArr(arr);
}

int main() {
    DataGenerator::run(
        "multi", 10, 2, "std", "data", "sample",
        generateSingleTestCase,
        generateSingleTestCase,
        [](int testId) {
            // 动态决定每组数据的测试用例数量
            if (testId <= 5) return rangeRand(1, 3);
            else return rangeRand(5, 10);
        },
        [](int testId) { return 1; },  // 样例只有1组
        true  // 输出测试ID
    );
    return 0;
}
```

### 实例5：特殊构造数据

```cpp
void generateSpecialCases(int testId) {
    using namespace util::graph;

    switch (testId) {
        case 1:
            // 最小数据
            println(1);
            println(1);
            break;

        case 2:
            // 链状数据
            auto chain = genChain(1000, {1, 100});
            chain.printWithInfo(true);
            break;

        case 3:
            // 菊花图
            auto star = genStar(500, 1, {1, 1000});
            star.printWithInfo(true);
            break;

        case 4:
            // 完全图
            auto complete = genCompleteGraph(100, {1, 100});
            complete.printWithInfo(true);
            break;

        default:
            // 正常随机数据
            int n = rangeRand(100, 500);
            int m = rangeRand(n-1, min(5000, n*(n-1)/2));
            auto graph = genUndirectedGraph(n, m, {1, 1000});
            graph.printWithInfo(true);
    }
}

int main() {
    DataGenerator::run("special", 10, 0, "std", "data", "", generateSpecialCases);
    return 0;
}
```