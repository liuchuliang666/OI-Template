#pragma once
#include <bits/stdc++.h>
namespace util {
    using ll = long long;
    /// Random number generator
    inline std::mt19937_64 rnd(std::random_device{}());
    /**
     * @brief Set random seed
     * @param seed Random seed
     */
    inline void setSeed(unsigned long long seed) {
        rnd.seed(seed);
    }
    /**
     * @brief Generate random number in [0, x-1]
     * @tparam T Integer type
     * @param x Upper bound (exclusive)
     * @return Random number in [0, x-1]
     */
    template <typename T>
    inline T modx(T x) {
        assert(x > 0);
        return rnd() % x;
    }
    /**
     * @brief Generate random number in [1, x]
     * @tparam T Integer type
     * @param x Upper bound (inclusive)
     * @return Random number in [1, x]
     */
    template <typename T>
    inline T mod1(T x) { return modx(x) + 1; }
    /**
     * @brief Generate random number in [l, r]
     * @tparam T Integer type
     * @param l Lower bound (inclusive)
     * @param r Upper bound (inclusive)
     * @return Random number in [l, r]
     */
    template <typename T>
    inline T rangeRand(T l, T r) { return l + modx(r - l + 1); }
    /**
     * @brief Generate random range [l, r] within [L, R]
     * @tparam T Integer type
     * @param L Lower bound of range
     * @param R Upper bound of range
     * @return Pair of (l, r) where l <= r and both in [L, R]
     */
    template <typename T>
    inline std::pair<T, T> randRange(T L, T r) {
        T l = rangeRand(L, r);
        T rVal = rangeRand(L, r);
        if (l > rVal) std::swap(l, rVal);
        return std::make_pair(l, rVal);
    }
    /**
     * @brief Generate random lowercase character
     * @return Random character in 'a'~'z'
     */
    inline char randChar() { return 'a' + modx(26); }
    /**
     * @brief Generate array with given length and generation function
     * @tparam T Element type
     * @param len Array length
     * @param lim Limit parameter for generation function
     * @param genFunc Generation function
     * @return Generated array
     */
    template <typename T>
    inline std::vector<T> genArr(int len, T lim, std::function<T(T)> genFunc) {
        std::vector<T> ret;
        for (int i = 0; i < len; ++i) ret.push_back(genFunc(lim));
        return ret;
    }
    /**
     * @brief Generate random string
     * @param len String length
     * @param genChar Character generation function
     * @return Generated string
     */
    inline std::string genStr(int len, std::function<char()> genChar = randChar) {
        std::string ret;
        for (int i = 0; i < len; ++i) ret += genChar();
        return ret;
    }
    /**
     * @brief Randomly choose element from vector
     * @tparam T Element type
     * @param a Input vector
     * @return Randomly chosen element
     */
    template <typename T>
    T choice(const std::vector<T> &a) { return a[modx(a.size())]; }
    /**
     * @brief Randomly choose element from array
     * @tparam T Element type
     * @tparam N Array size
     * @param a Input array
     * @return Randomly chosen element
     */
    template <typename T, size_t N>
    T choice(const std::array<T, N> &a) { return a[modx(a.size())]; }
    /**
     * @brief Shuffle vector randomly
     * @tparam T Element type
     * @param a Vector to shuffle
     */
    template <typename T>
    void shuffleVec(std::vector<T> &a) {
        std::shuffle(a.begin(), a.end(), rnd);
    }
    /**
     * @brief Print array with given separator and ending
     * @tparam T Element type
     * @param arr Array to print
     * @param split Separator between elements
     * @param end Ending string
     */
    template <typename T>
    void printArr(const std::vector<T> &arr, const std::string &split = " ", const std::string &end = "\n") {
        for (auto it = arr.begin(); it != arr.end(); ++it) {
            std::cout << *it;
            if (std::next(it) != arr.end()) std::cout << split;
        }
        std::cout << end;
    }
    /**
     * @brief Print multiple values with space separation
     * @tparam First First argument type
     * @tparam Args Other arguments types
     * @param first First argument
     * @param args Other arguments
     */
    template <typename First, typename... Args>
    void println(const First &first, Args &&...args) {
        std::cout << first;
        using expander = int[];
        (void)expander{0, (void(std::cout << " " << std::forward<Args>(args)), 0)...};
        std::cout << '\n';
    }
    /**
     * @brief Create directory if not exists
     * @param dirName Directory name
     */
    inline void mkdir(const std::string &dirName) {
        namespace fs = std::filesystem;
        if (!fs::exists(dirName) || !fs::is_directory(dirName)) {
            fs::create_directory(dirName);
            std::cerr << "Created directory: " << dirName << "\n";
        }
    }
    // 图论模块放在子命名空间 graph 中
    namespace graph {
        /**
         * @brief Helper to check if type is a pair of integers
         */
        template <typename T>
        struct IsIntegerPair : std::false_type {};
        template <>
        struct IsIntegerPair<std::pair<int, int>> : std::true_type {};
        /**
         * @brief Graph class for storing and generating various types of graphs
         * @tparam WeightType Weight type (use int for unweighted graphs)
         */
        template <typename WeightType = int>
        class Graph {
        private:
            int vertexCount;                                        ///< Number of vertices
            int edgeCount;                                          ///< Number of edges
            std::vector<std::tuple<int, int, WeightType>> edgeList; ///< Edge list (u, v, w)
        public:
            /**
             * @brief Construct a new Graph object
             * @param n Number of vertices
             */
            Graph(int n = 0) : vertexCount(n), edgeCount(0) {}
            /**
             * @brief Add an edge to the graph
             * @param fromVertex From vertex (1-indexed)
             * @param toVertex To vertex (1-indexed)
             * @param weight Edge weight
             */
            void addEdge(int fromVertex, int toVertex, WeightType weight = WeightType{1}) {
                edgeList.emplace_back(fromVertex, toVertex, weight);
                ++edgeCount;
            }
            /**
             * @brief Get number of vertices
             * @return int Number of vertices
             */
            int getVertexCount() const { return vertexCount; }
            /**
             * @brief Get number of edges
             * @return int Number of edges
             */
            int getEdgeCount() const { return edgeCount; }
            /**
             * @brief Get edge list
             * @return const std::vector<std::tuple<int, int, WeightType>>& Edge list
             */
            const std::vector<std::tuple<int, int, WeightType>> &getEdgeList() const { return edgeList; }
            /**
             * @brief Print the graph edges only (without vertex and edge counts)
             * @param printWeights Whether to print edge weights
             */
            void print(bool printWeights = true) const {
                for (const auto &edge : edgeList) {
                    int u = std::get<0>(edge), v = std::get<1>(edge);
                    WeightType w = std::get<2>(edge);
                    if (printWeights) {
                        println(u, v, w);
                    } else {
                        println(u, v);
                    }
                }
            }
            /**
             * @brief Print the graph with vertex and edge counts
             * @param printWeights Whether to print edge weights
             */
            void printWithInfo(bool printWeights = true) const {
                println(vertexCount, edgeCount);
                print(printWeights);
            }
            /**
             * @brief Print the tree with only vertex count (no edge count for trees)
             * @param printWeights Whether to print edge weights
             */
            void printTree(bool printWeights = true) const {
                // For trees, we only print the vertex count, not the edge count
                std::cout << vertexCount << "\n";
                print(printWeights);
            }
            /**
             * @brief Print parent array for trees (f2, f3, ..., fn)
             * @param parentArray Parent array where parentArray[i] is the parent of vertex i+1
             * @param rootVertex Root vertex (default: 1)
             */
            static void printParentArray(const std::vector<int> &parentArray, int rootVertex = 1) {
                for (int i = 2; i <= (int)parentArray.size(); ++i) {
                    std::cout << parentArray[i - 1];
                    if (i < (int)parentArray.size()) std::cout << " ";
                }
                std::cout << "\n";
            }
        };
        /**
         * @brief Helper function to generate weight based on input type
         * @tparam WeightType Weight type
         * @param weightGenerator Weight generator (function, pair, or value)
         * @param u From vertex (for functions that need it)
         * @param v To vertex (for functions that need it)
         * @return Generated weight
         */
        template <typename WeightType, typename Func>
        WeightType generateWeight(Func &&weightGenerator, int u = 0, int v = 0) {
            if constexpr (IsIntegerPair<std::decay_t<Func>>::value) {
                // If weightGenerator is a pair, treat it as [min, max] range
                return rangeRand(weightGenerator.first, weightGenerator.second);
            } else if constexpr (std::is_invocable_r<WeightType, Func, int, int>::value) {
                // If weightGenerator is a function taking two vertices
                return weightGenerator(u, v);
            } else if constexpr (std::is_invocable_r<WeightType, Func>::value) {
                // If weightGenerator is a function taking no arguments
                return weightGenerator();
            } else {
                // If weightGenerator is a constant value
                return weightGenerator;
            }
        }
        /**
         * @brief Generate a random tree
         * @param vertexCount Number of vertices
         * @param rootVertex Root vertex (1-indexed)
         * @param requireParentLess Whether to require parent < child
         * @param weightGenerator Weight generation function, pair, or constant value
         * @param allowMultiEdges Whether to allow multiple edges (not used for trees)
         * @param allowSelfLoop Whether to allow self loops (not used for trees)
         * @param ensureConnected Whether to ensure graph is connected (always true for trees)
         * @return Graph<WeightType> Generated tree
         */
        template <typename WeightType = int, typename Func>
        Graph<WeightType> genTree(int vertexCount, int rootVertex = 1, bool requireParentLess = false,
                                  Func &&weightGenerator = WeightType{1},
                                  bool allowMultiEdges = false, bool allowSelfLoop = false, bool ensureConnected = true) {
            Graph<WeightType> tree(vertexCount);
            std::vector<int> parentArray(vertexCount + 1, 0);
            if (requireParentLess) {
                // Each vertex i has parent in [1, i-1]
                for (int i = 2; i <= vertexCount; ++i) {
                    int parent = rangeRand(1, i - 1);
                    parentArray[i] = parent;
                    WeightType weight = generateWeight<WeightType>(weightGenerator, parent, i);
                    tree.addEdge(parent, i, weight);
                }
            } else {
                // Random tree construction using random parent assignment
                std::vector<int> vertices(vertexCount);
                for (int i = 0; i < vertexCount; ++i) vertices[i] = i + 1;
                shuffleVec(vertices);
                // Remove root from available vertices
                vertices.erase(std::find(vertices.begin(), vertices.end(), rootVertex));
                std::vector<int> connectedVertices = {rootVertex};
                for (int currentVertex : vertices) {
                    int parentVertex = choice(connectedVertices);
                    parentArray[currentVertex] = parentVertex;
                    WeightType weight = generateWeight<WeightType>(weightGenerator, parentVertex, currentVertex);
                    tree.addEdge(parentVertex, currentVertex, weight);
                    connectedVertices.push_back(currentVertex);
                }
            }
            return tree;
        }
        /**
         * @brief Generate a chain (path graph)
         * @param vertexCount Number of vertices
         * @param weightGenerator Weight generation function, pair, or constant value
         * @param allowMultiEdges Whether to allow multiple edges (not used for chains)
         * @param allowSelfLoop Whether to allow self loops (not used for chains)
         * @param ensureConnected Whether to ensure graph is connected (always true for chains)
         * @return Graph<WeightType> Generated chain
         */
        template <typename WeightType = int, typename Func>
        Graph<WeightType> genChain(int vertexCount, Func &&weightGenerator = WeightType{1},
                                   bool allowMultiEdges = false, bool allowSelfLoop = false, bool ensureConnected = true) {
            Graph<WeightType> chain(vertexCount);
            for (int i = 1; i < vertexCount; ++i) {
                WeightType weight = generateWeight<WeightType>(weightGenerator, i, i + 1);
                chain.addEdge(i, i + 1, weight);
            }
            return chain;
        }
        /**
         * @brief Generate a star graph
         * @param vertexCount Number of vertices
         * @param centerVertex Center vertex (1-indexed), 0 for random
         * @param weightGenerator Weight generation function, pair, or constant value
         * @param allowMultiEdges Whether to allow multiple edges (not used for stars)
         * @param allowSelfLoop Whether to allow self loops (not used for stars)
         * @param ensureConnected Whether to ensure graph is connected (always true for stars)
         * @return Graph<WeightType> Generated star
         */
        template <typename WeightType = int, typename Func>
        Graph<WeightType> genStar(int vertexCount, int centerVertex = 0,
                                  Func &&weightGenerator = WeightType{1},
                                  bool allowMultiEdges = false, bool allowSelfLoop = false, bool ensureConnected = true) {
            if (centerVertex == 0) centerVertex = mod1(vertexCount);
            Graph<WeightType> star(vertexCount);
            for (int i = 1; i <= vertexCount; ++i) {
                if (i != centerVertex) {
                    WeightType weight = generateWeight<WeightType>(weightGenerator, centerVertex, i);
                    star.addEdge(centerVertex, i, weight);
                }
            }
            return star;
        }
        /**
         * @brief Generate a cycle graph (single cycle)
         * @param vertexCount Number of vertices
         * @param weightGenerator Weight generation function, pair, or constant value
         * @param allowMultiEdges Whether to allow multiple edges (not used for cycles)
         * @param allowSelfLoop Whether to allow self loops (not used for cycles)
         * @param ensureConnected Whether to ensure graph is connected (always true for cycles)
         * @return Graph<WeightType> Generated cycle
         */
        template <typename WeightType = int, typename Func>
        Graph<WeightType> genCycle(int vertexCount, Func &&weightGenerator = WeightType{1},
                                   bool allowMultiEdges = false, bool allowSelfLoop = false, bool ensureConnected = true) {
            Graph<WeightType> cycle(vertexCount);
            for (int i = 1; i < vertexCount; ++i) {
                WeightType weight = generateWeight<WeightType>(weightGenerator, i, i + 1);
                cycle.addEdge(i, i + 1, weight);
            }
            // Close the cycle
            WeightType weight = generateWeight<WeightType>(weightGenerator, vertexCount, 1);
            cycle.addEdge(vertexCount, 1, weight);
            return cycle;
        }
        /**
         * @brief Generate a complete graph
         * @param vertexCount Number of vertices
         * @param weightGenerator Weight generation function, pair, or constant value
         * @param allowMultiEdges Whether to allow multiple edges (not used for complete graphs)
         * @param allowSelfLoop Whether to allow self loops
         * @param ensureConnected Whether to ensure graph is connected (always true for complete graphs)
         * @return Graph<WeightType> Generated complete graph
         */
        template <typename WeightType = int, typename Func>
        Graph<WeightType> genCompleteGraph(int vertexCount, Func &&weightGenerator = WeightType{1},
                                           bool allowMultiEdges = false, bool allowSelfLoop = false, bool ensureConnected = true) {
            Graph<WeightType> complete(vertexCount);
            for (int i = 1; i <= vertexCount; ++i) {
                for (int j = i + 1; j <= vertexCount; ++j) {
                    WeightType weight = generateWeight<WeightType>(weightGenerator, i, j);
                    complete.addEdge(i, j, weight);
                }
            }
            return complete;
        }
        /**
         * @brief Generate a bipartite graph
         * @param leftCount Number of vertices in left partition
         * @param rightCount Number of vertices in right partition
         * @param edgeCount Number of edges between partitions
         * @param weightGenerator Weight generation function, pair, or constant value
         * @param allowMultiEdges Whether to allow multiple edges
         * @param allowSelfLoop Whether to allow self loops
         * @param ensureConnected Whether to ensure graph is connected
         * @return Graph<WeightType> Generated bipartite graph
         */
        template <typename WeightType = int, typename Func>
        Graph<WeightType> genBipartiteGraph(int leftCount, int rightCount, int edgeCount,
                                            Func &&weightGenerator = WeightType{1},
                                            bool allowMultiEdges = false, bool allowSelfLoop = false, bool ensureConnected = false) {
            int vertexCount = leftCount + rightCount;
            Graph<WeightType> bipartite(vertexCount);
            std::set<std::pair<int, int>> existingEdges;
            // If ensureConnected is true, first ensure connectivity between partitions
            if (ensureConnected) {
                // Connect each vertex in left partition to at least one vertex in right partition
                for (int i = 1; i <= leftCount; ++i) {
                    int v = leftCount + mod1(rightCount);
                    existingEdges.insert({i, v});
                    WeightType weight = generateWeight<WeightType>(weightGenerator, i, v);
                    bipartite.addEdge(i, v, weight);
                }
                // Connect each vertex in right partition to at least one vertex in left partition
                for (int i = leftCount + 1; i <= vertexCount; ++i) {
                    int u = mod1(leftCount);
                    if (!allowMultiEdges && existingEdges.count({u, i})) continue;
                    existingEdges.insert({u, i});
                    WeightType weight = generateWeight<WeightType>(weightGenerator, u, i);
                    bipartite.addEdge(u, i, weight);
                }
            }
            // Add remaining edges
            while (bipartite.getEdgeCount() < edgeCount) {
                int u = mod1(leftCount);              // Left partition: 1..leftCount
                int v = leftCount + mod1(rightCount); // Right partition: leftCount+1..leftCount+rightCount
                if (!allowMultiEdges && existingEdges.count({u, v})) continue;
                existingEdges.insert({u, v});
                WeightType weight = generateWeight<WeightType>(weightGenerator, u, v);
                bipartite.addEdge(u, v, weight);
            }
            return bipartite;
        }
        /**
         * @brief Generate a random undirected graph
         * @param vertexCount Number of vertices
         * @param edgeCount Number of edges
         * @param weightGenerator Weight generation function, pair, or constant value
         * @param allowMultiEdges Whether to allow multiple edges
         * @param allowSelfLoop Whether to allow self loops
         * @param ensureConnected Whether to ensure graph is connected
         * @return Graph<WeightType> Generated undirected graph
         */
        template <typename WeightType = int, typename Func>
        Graph<WeightType> genUndirectedGraph(int vertexCount, int edgeCount,
                                             Func &&weightGenerator = WeightType{1},
                                             bool allowMultiEdges = false, bool allowSelfLoop = false, bool ensureConnected = false) {
            Graph<WeightType> graph(vertexCount);
            std::set<std::pair<int, int>> existingEdges;
            // If ensureConnected is true, first generate a spanning tree
            if (ensureConnected) {
                auto spanningTree = genTree<WeightType>(vertexCount, 1, false, weightGenerator);
                for (const auto &edge : spanningTree.getEdgeList()) {
                    int u = std::get<0>(edge), v = std::get<1>(edge);
                    WeightType w = std::get<2>(edge);
                    graph.addEdge(u, v, w);
                    if (!allowMultiEdges) {
                        existingEdges.insert({std::min(u, v), std::max(u, v)});
                    }
                }
            }
            // Add remaining edges
            while (graph.getEdgeCount() < edgeCount) {
                int u = mod1(vertexCount), v = mod1(vertexCount);
                // Check self loop
                if (!allowSelfLoop && u == v) continue;
                // For undirected graph, consider edge as unordered pair
                int minVertex = std::min(u, v);
                int maxVertex = std::max(u, v);
                // Check multi edges
                if (!allowMultiEdges) {
                    if (existingEdges.count({minVertex, maxVertex})) continue;
                    existingEdges.insert({minVertex, maxVertex});
                }
                WeightType weight = generateWeight<WeightType>(weightGenerator, u, v);
                graph.addEdge(u, v, weight);
            }
            return graph;
        }
        /**
         * @brief Generate a random directed graph
         * @param vertexCount Number of vertices
         * @param edgeCount Number of edges
         * @param weightGenerator Weight generation function, pair, or constant value
         * @param allowMultiEdges Whether to allow multiple edges
         * @param allowSelfLoop Whether to allow self loops
         * @param ensureConnected Whether to ensure graph is connected
         * @return Graph<WeightType> Generated directed graph
         */
        template <typename WeightType = int, typename Func>
        Graph<WeightType> genDirectedGraph(int vertexCount, int edgeCount,
                                           Func &&weightGenerator = WeightType{1},
                                           bool allowMultiEdges = false, bool allowSelfLoop = false, bool ensureConnected = false) {
            Graph<WeightType> graph(vertexCount);
            std::set<std::pair<int, int>> existingEdges;
            // If ensureConnected is true, first generate a spanning tree (as directed edges)
            if (ensureConnected) {
                auto spanningTree = genTree<WeightType>(vertexCount, 1, false, weightGenerator);
                for (const auto &edge : spanningTree.getEdgeList()) {
                    int u = std::get<0>(edge), v = std::get<1>(edge);
                    WeightType w = std::get<2>(edge);
                    graph.addEdge(u, v, w);
                    if (!allowMultiEdges) {
                        existingEdges.insert({u, v});
                    }
                }
            }
            // Add remaining edges
            while (graph.getEdgeCount() < edgeCount) {
                int u = mod1(vertexCount), v = mod1(vertexCount);
                // Check self loop
                if (!allowSelfLoop && u == v) continue;
                // Check multi edges
                if (!allowMultiEdges && existingEdges.count({u, v})) continue;
                if (!allowMultiEdges) {
                    existingEdges.insert({u, v});
                }
                WeightType weight = generateWeight<WeightType>(weightGenerator, u, v);
                graph.addEdge(u, v, weight);
            }
            return graph;
        }
        /**
         * @brief Generate a Directed Acyclic Graph (DAG)
         * @param vertexCount Number of vertices
         * @param edgeCount Number of edges
         * @param weightGenerator Weight generation function, pair, or constant value
         * @param allowMultiEdges Whether to allow multiple edges
         * @param allowSelfLoop Whether to allow self loops
         * @param ensureConnected Whether to ensure graph is connected
         * @return Graph<WeightType> Generated DAG
         */
        template <typename WeightType = int, typename Func>
        Graph<WeightType> genDAG(int vertexCount, int edgeCount,
                                 Func &&weightGenerator = WeightType{1},
                                 bool allowMultiEdges = false, bool allowSelfLoop = false, bool ensureConnected = false) {
            Graph<WeightType> dag(vertexCount);
            std::vector<int> topologicalOrder(vertexCount);
            for (int i = 0; i < vertexCount; ++i) topologicalOrder[i] = i + 1;
            shuffleVec(topologicalOrder);
            std::set<std::pair<int, int>> existingEdges;
            // If ensureConnected is true, first generate a spanning tree that respects topological order
            if (ensureConnected) {
                // Create a tree where edges only go from earlier to later vertices in topological order
                for (int i = 1; i < vertexCount; ++i) {
                    int parentIndex = modx(i);
                    int u = topologicalOrder[parentIndex];
                    int v = topologicalOrder[i];
                    WeightType weight = generateWeight<WeightType>(weightGenerator, u, v);
                    dag.addEdge(u, v, weight);
                    if (!allowMultiEdges) {
                        existingEdges.insert({u, v});
                    }
                }
            }
            // Add remaining edges, ensuring they respect topological order
            while (dag.getEdgeCount() < edgeCount) {
                int i = modx(vertexCount), j = modx(vertexCount);
                if (i >= j) continue; // Ensure edge goes from earlier to later in topological order
                int u = topologicalOrder[i], v = topologicalOrder[j];
                // Check multi edges
                if (!allowMultiEdges && existingEdges.count({u, v})) continue;
                if (!allowMultiEdges) {
                    existingEdges.insert({u, v});
                }
                WeightType weight = generateWeight<WeightType>(weightGenerator, u, v);
                dag.addEdge(u, v, weight);
            }
            return dag;
        }
        /**
         * @brief Generate a graph that challenges SPFA algorithm
         * @param vertexCount Number of vertices
         * @param edgeCount Number of edges
         * @param weightGenerator Weight generation function for normal edges
         * @param negativeWeightGenerator Weight generation function for negative edges
         * @param negativeRatio Ratio of negative weight edges
         * @param allowMultiEdges Whether to allow multiple edges
         * @param allowSelfLoop Whether to allow self loops
         * @param ensureConnected Whether to ensure graph is connected
         * @return Graph<WeightType> Generated SPFA-challenging graph
         */
        template <typename WeightType = int, typename Func1, typename Func2>
        Graph<WeightType> genSpfaKiller(int vertexCount, int edgeCount, Func1 &&weightGenerator = WeightType{1}, Func2 &&negativeWeightGenerator = [] { return WeightType{-1}; }, double negativeRatio = 0.1, bool allowMultiEdges = false, bool allowSelfLoop = false, bool ensureConnected = true) {
            Graph<WeightType> graph(vertexCount);
            // Ensure we have enough edges for connectivity
            if (edgeCount < vertexCount - 1) {
                // If not enough edges for a chain, just generate what we can
                for (int i = 1; i < vertexCount && graph.getEdgeCount() < edgeCount; ++i) {
                    WeightType weight = generateWeight<WeightType>(weightGenerator, i, i + 1);
                    graph.addEdge(i, i + 1, weight);
                }
                return graph;
            }
            // Create a chain to ensure connectivity
            for (int i = 1; i < vertexCount; ++i) {
                WeightType weight = generateWeight<WeightType>(weightGenerator, i, i + 1);
                graph.addEdge(i, i + 1, weight);
            }
            int remainingEdges = edgeCount - (vertexCount - 1);
            if (remainingEdges <= 0) return graph;
            // Add negative weight edges in a way that creates many relaxations
            int negativeEdgeCount = static_cast<int>(remainingEdges * negativeRatio);
            for (int i = 0; i < negativeEdgeCount; ++i) {
                // Ensure u is at least 2 and v < u to create backward edges
                int u = rangeRand(std::min(vertexCount, 3), vertexCount); // Start from at least vertex 3
                int v = rangeRand(1, std::max(1, u - 1));                 // Ensure v is at least 1 and less than u
                WeightType weight = generateWeight<WeightType>(negativeWeightGenerator, u, v);
                graph.addEdge(u, v, weight);
            }
            // Add remaining edges
            for (int i = 0; i < remainingEdges - negativeEdgeCount; ++i) {
                int u = mod1(vertexCount), v = mod1(vertexCount);
                if (!allowSelfLoop && u == v) continue;
                WeightType weight = generateWeight<WeightType>(weightGenerator, u, v);
                graph.addEdge(u, v, weight);
            }
            return graph;
        }
    } // namespace graph
    /**
     * @brief Data generator for competitive programming problems
     */
    /**
     * @brief Data generator for competitive programming problems
     */
    struct DataGenerator {
        /**
         * @brief Run data generation process
         * @param dataName Base name for data files
         * @param testCount Number of test cases
         * @param sampleCount Number of sample cases
         * @param stdName Standard program name
         * @param dataFolderName Data folder name
         * @param sampleFolderName Sample folder name
         * @param makeDataFunc Function to generate test data
         * @param makeSampleFunc Function to generate sample data (default does nothing)
         * @param testGroupCountFunc Function that returns number of test groups for each test case
         * @param sampleGroupCountFunc Function that returns number of test groups for each sample
         * @param outputTestCaseId Whether to output test case ID in the first line
         */
        static void run(
            const std::string &dataName = "data",
            int testCount = 10,
            int sampleCount = 0,
            const std::string &stdName = "std",
            const std::string &dataFolderName = "data",
            const std::string &sampleFolderName = "down",
            std::function<void(int)> makeDataFunc = [](int) {
                // Default implementation: do nothing
            },
            std::function<void(int)> makeSampleFunc = [](int) {
                // Default implementation: do nothing
            },
            std::function<int(int)> testGroupCountFunc = [](int) { return 0; }, std::function<int(int)> sampleGroupCountFunc = [](int) { return 0; }, bool outputTestCaseId = false) {
            const std::string dataPath = "./" + dataFolderName + "/";
            const std::string samplePath = "./" + sampleFolderName + "/";
            mkdir(dataFolderName);
            mkdir(sampleFolderName);
            // Generate test data files
            for (int testCaseId = 1; testCaseId <= testCount; ++testCaseId) {
                const auto taskName = dataName + std::to_string(testCaseId);
                generateFile(dataPath + taskName + ".in", [testCaseId, testGroupCountFunc, outputTestCaseId, makeDataFunc] { generateMultiTestData(testCaseId, testGroupCountFunc, outputTestCaseId, makeDataFunc); });
                generateAnswer(dataPath + taskName, stdName);
            }
            // Generate sample data files
            for (int testCaseId = 1; testCaseId <= sampleCount; ++testCaseId) {
                const auto taskName = std::to_string(testCaseId);
                generateFile(samplePath + taskName + ".in", [testCaseId, sampleGroupCountFunc, outputTestCaseId, makeSampleFunc] { generateMultiTestData(testCaseId, sampleGroupCountFunc, outputTestCaseId, makeSampleFunc); });
                generateAnswer(samplePath + taskName, stdName);
            }
        }

    private:
        /**
         * @brief Generate multi-test data file
         * @param testCaseId Test case ID
         * @param groupCountFunc Function that returns number of test groups
         * @param outputTestCaseId Whether to output test case ID
         * @param dataGenFunc Data generation function
         */
        static void generateMultiTestData(int testCaseId,
                                          std::function<int(int)> groupCountFunc,
                                          bool outputTestCaseId,
                                          std::function<void(int)> dataGenFunc) {
            int groupCount = groupCountFunc(testCaseId);
            if (groupCount == 0) {
                // Single test case
                if (outputTestCaseId) {
                    std::cout << testCaseId << "\n";
                }
                dataGenFunc(testCaseId);
            } else {
                // Multiple test cases
                if (outputTestCaseId) {
                    std::cout << groupCount << " " << testCaseId << "\n";
                } else {
                    std::cout << groupCount << "\n";
                }
                for (int i = 0; i < groupCount; ++i) {
                    dataGenFunc(testCaseId);
                }
            }
        }
        /**
         * @brief Generate input file
         * @param fileName File name
         * @param genFunc Generation function
         */
        template <typename Func>
        static void generateFile(const std::string &fileName, Func genFunc) {
            freopen(fileName.c_str(), "wb", stdout);
            genFunc();
            std::cerr << "Generated: " << fileName << "\n";
            fflush(stdout);
        }
        /**
         * @brief Generate answer file using standard program
         * @param filePrefix File prefix without extension
         * @param stdName Standard program name
         * @throw std::runtime_error if std program fails with exit code
         */
        static void generateAnswer(const std::string &filePrefix, const std::string &stdName) {
            // 构建命令 - 跨平台兼容
            std::string cmd;
#ifdef _WIN32
            // Windows 命令语法
            cmd = stdName + " < \"" + filePrefix + ".in\" > \"" + filePrefix + ".ans\"";
#else
            // Unix/Linux 命令语法
            cmd = "./" + stdName + " < \"" + filePrefix + ".in\" > \"" + filePrefix + ".ans\"";
#endif
            // 执行命令并检查返回值
            int ret = system(cmd.c_str());
            if (ret != 0) {
                std::string errorMsg = "Standard program failed with exit code " + std::to_string(1u * ret);
                errorMsg += " while generating answer for: " + filePrefix;
                throw std::runtime_error(errorMsg);
            }
            std::cerr << "Generated answer: " << filePrefix << ".ans\n";
        }
    };
} // namespace util