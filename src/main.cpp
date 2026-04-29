#include "adjacencyListGraph.hpp"
#include "adjacencyMatrixGraph.hpp"
#include "edgeListGraph.hpp"
#include "visualizer.hpp"

#include <algorithm>
#include <functional>
#include <limits>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace Graph;

namespace
{
    constexpr int INF = std::numeric_limits<int>::max() / 4;

    using AdjMap = std::map<int, std::vector<std::pair<int, int>>>;

    AdjMap undirectedAdj(const BaseGraph& g)
    {
        AdjMap adj;
        for (const auto& v : g.GetVertices())
            adj[v.Id];
        for (const auto& e : g.GetEdges())
        {
            adj[e.From].push_back({e.To, e.Weight});
            adj[e.To].push_back({e.From, e.Weight});
        }
        return adj;
    }

    void activateEdge(BaseGraph& g, int u, int v)
    {
        g.SetEdgeActive(u, v, true);
        g.SetEdgeActive(v, u, true);
    }

    void activatePath(BaseGraph& g, const std::vector<int>& path)
    {
        for (size_t i = 1; i < path.size(); ++i)
            activateEdge(g, path[i - 1], path[i]);
    }
}

void RunBFS(BaseGraph& g, int source)
{
    auto adj = undirectedAdj(g);
    std::set<int> visited;
    std::queue<int> q;

    visited.insert(source);
    q.push(source);
    g.SetVertexActive(source, true);

    while (!q.empty())
    {
        int u = q.front(); q.pop();
        for (const auto& [v, w] : adj[u])
        {
            if (visited.count(v)) continue;
            visited.insert(v);
            g.SetVertexActive(v, true);
            activateEdge(g, u, v);
            q.push(v);
        }
    }
}

void RunDFS(BaseGraph& g, int source)
{
    auto adj = undirectedAdj(g);
    std::set<int> visited;

    std::function<void(int)> dfs = [&](int u) {
        visited.insert(u);
        g.SetVertexActive(u, true);
        for (const auto& [v, w] : adj[u])
        {
            if (visited.count(v)) continue;
            activateEdge(g, u, v);
            dfs(v);
        }
    };
    dfs(source);
}

void RunKruskal(BaseGraph& g)
{
    auto vertices = g.GetVertices();
    auto edges = g.GetEdges();

    std::map<int, int> parent;
    for (const auto& v : vertices) parent[v.Id] = v.Id;

    std::function<int(int)> find = [&](int x) {
        while (parent[x] != x) { parent[x] = parent[parent[x]]; x = parent[x]; }
        return x;
    };

    std::vector<Edge> sorted = edges;
    std::sort(sorted.begin(), sorted.end(), [](const Edge& a, const Edge& b) { return a.Weight < b.Weight; });

    for (const auto& e : sorted)
    {
        int rf = find(e.From);
        int rt = find(e.To);
        if (rf != rt)
        {
            parent[rf] = rt;
            activateEdge(g, e.From, e.To);
            g.SetVertexActive(e.From, true);
            g.SetVertexActive(e.To, true);
        }
    }
}

void RunPrim(BaseGraph& g, int root)
{
    auto adj = undirectedAdj(g);
    std::set<int> inTree;
    inTree.insert(root);
    g.SetVertexActive(root, true);

    using PQEntry = std::tuple<int, int, int>; // weight, from(in), to(out)
    std::priority_queue<PQEntry, std::vector<PQEntry>, std::greater<>> pq;
    for (const auto& [v, w] : adj[root])
        pq.push({w, root, v});

    while (!pq.empty())
    {
        auto [w, u, v] = pq.top(); pq.pop();
        if (inTree.count(v)) continue;
        inTree.insert(v);
        g.SetVertexActive(v, true);
        activateEdge(g, u, v);
        for (const auto& [v2, w2] : adj[v])
            if (!inTree.count(v2))
                pq.push({w2, v, v2});
    }
}

void RunBellmanFord(BaseGraph& g, int from, int to)
{
    auto vertices = g.GetVertices();
    auto edges = g.GetEdges();

    std::map<int, int> dist;
    std::map<int, int> prev;
    for (const auto& v : vertices) { dist[v.Id] = INF; prev[v.Id] = -1; }
    dist[from] = 0;

    for (size_t i = 0; i + 1 < vertices.size(); ++i)
    {
        for (const auto& e : edges)
        {
            if (dist[e.From] + e.Weight < dist[e.To])
            {
                dist[e.To] = dist[e.From] + e.Weight;
                prev[e.To] = e.From;
            }
            if (dist[e.To] + e.Weight < dist[e.From])
            {
                dist[e.From] = dist[e.To] + e.Weight;
                prev[e.From] = e.To;
            }
        }
    }

    for (const auto& v : vertices)
        g.SetVertexWeight(v.Id, dist[v.Id] >= INF ? -1 : dist[v.Id]);

    if (dist[to] >= INF) return;
    std::vector<int> path;
    for (int cur = to; cur != -1; cur = prev[cur]) path.push_back(cur);
    std::reverse(path.begin(), path.end());
    activatePath(g, path);
}

void RunDijkstra(BaseGraph& g, int from, int to)
{
    auto adj = undirectedAdj(g);
    std::map<int, int> dist;
    std::map<int, int> prev;
    for (const auto& v : g.GetVertices()) { dist[v.Id] = INF; prev[v.Id] = -1; }
    dist[from] = 0;

    using PQEntry = std::pair<int, int>;
    std::priority_queue<PQEntry, std::vector<PQEntry>, std::greater<>> pq;
    pq.push({0, from});

    while (!pq.empty())
    {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (const auto& [v, w] : adj[u])
        {
            if (d + w < dist[v])
            {
                dist[v] = d + w;
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    for (const auto& v : g.GetVertices())
        g.SetVertexWeight(v.Id, dist[v.Id] >= INF ? -1 : dist[v.Id]);

    if (dist[to] >= INF) return;
    std::vector<int> path;
    for (int cur = to; cur != -1; cur = prev[cur]) path.push_back(cur);
    std::reverse(path.begin(), path.end());
    activatePath(g, path);
}

void RunFloydWarshall(BaseGraph& g, int from, int to)
{
    auto vertices = g.GetVertices();
    auto edges = g.GetEdges();

    std::vector<int> ids;
    for (const auto& v : vertices) ids.push_back(v.Id);
    std::map<int, int> idx;
    for (size_t i = 0; i < ids.size(); ++i) idx[ids[i]] = static_cast<int>(i);

    int n = static_cast<int>(ids.size());
    std::vector<std::vector<int>> dist(n, std::vector<int>(n, INF));
    std::vector<std::vector<int>> next(n, std::vector<int>(n, -1));
    for (int i = 0; i < n; ++i) dist[i][i] = 0;
    for (const auto& e : edges)
    {
        int u = idx[e.From], v = idx[e.To];
        if (e.Weight < dist[u][v]) { dist[u][v] = e.Weight; next[u][v] = v; }
        if (e.Weight < dist[v][u]) { dist[v][u] = e.Weight; next[v][u] = u; }
    }

    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }

    int fromIdx = idx[from];
    int toIdx = idx[to];

    for (int i = 0; i < n; ++i)
        g.SetVertexWeight(ids[i], dist[fromIdx][i] >= INF ? -1 : dist[fromIdx][i]);

    if (next[fromIdx][toIdx] == -1) return;
    std::vector<int> path;
    path.push_back(from);
    int cur = fromIdx;
    while (cur != toIdx)
    {
        cur = next[cur][toIdx];
        if (cur < 0) break;
        path.push_back(ids[cur]);
    }
    activatePath(g, path);
}

void RunJohnson(BaseGraph& g, int from, int to)
{
    auto vertices = g.GetVertices();
    auto edges = g.GetEdges();

    std::map<int, int> h;
    for (const auto& v : vertices) h[v.Id] = 0;
    for (size_t i = 0; i + 1 < vertices.size(); ++i)
    {
        for (const auto& e : edges)
        {
            if (h[e.From] + e.Weight < h[e.To]) h[e.To] = h[e.From] + e.Weight;
            if (h[e.To] + e.Weight < h[e.From]) h[e.From] = h[e.To] + e.Weight;
        }
    }

    //Dijkstra from
    auto adj = undirectedAdj(g);
    std::map<int, int> dist;
    std::map<int, int> prev;
    for (const auto& v : vertices) { dist[v.Id] = INF; prev[v.Id] = -1; }
    dist[from] = 0;

    using PQEntry = std::pair<int, int>;
    std::priority_queue<PQEntry, std::vector<PQEntry>, std::greater<>> pq;
    pq.push({0, from});
    while (!pq.empty())
    {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (const auto& [v, w] : adj[u])
        {
            int rw = w + h[u] - h[v];
            if (d + rw < dist[v])
            {
                dist[v] = d + rw;
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    for (const auto& v : vertices)
    {
        int trueDist = dist[v.Id] >= INF ? -1 : dist[v.Id] - h[from] + h[v.Id];
        g.SetVertexWeight(v.Id, trueDist);
    }

    if (dist[to] >= INF) return;
    std::vector<int> path;
    for (int cur = to; cur != -1; cur = prev[cur]) path.push_back(cur);
    std::reverse(path.begin(), path.end());
    activatePath(g, path);
}

namespace
{
    using CapMap = std::map<std::pair<int, int>, int>;

    void runFlowAlgorithm(BaseGraph& g, int source, int sink, bool useBfs)
    {
        auto vertices = g.GetVertices();
        auto edges = g.GetEdges();

        CapMap cap;
        CapMap originalCap;
        for (const auto& e : edges)
        {
            cap[{e.From, e.To}] += e.Weight;
            originalCap[{e.From, e.To}] = cap[{e.From, e.To}];
        }

        auto findPath = [&]() -> std::vector<int> {
            std::set<int> visited;
            std::map<int, int> prev;
            visited.insert(source);
            prev[source] = -1;
            bool found = false;

            if (useBfs)
            {
                std::queue<int> q;
                q.push(source);
                while (!q.empty() && !found)
                {
                    int u = q.front(); q.pop();
                    for (const auto& v : vertices)
                    {
                        int vid = v.Id;
                        if (visited.count(vid)) continue;
                        if (cap[{u, vid}] > 0)
                        {
                            visited.insert(vid);
                            prev[vid] = u;
                            if (vid == sink) { found = true; break; }
                            q.push(vid);
                        }
                    }
                }
            }
            else
            {
                std::stack<int> st;
                st.push(source);
                while (!st.empty() && !found)
                {
                    int u = st.top(); st.pop();
                    if (u == sink) { found = true; break; }
                    for (const auto& v : vertices)
                    {
                        int vid = v.Id;
                        if (visited.count(vid)) continue;
                        if (cap[{u, vid}] > 0)
                        {
                            visited.insert(vid);
                            prev[vid] = u;
                            st.push(vid);
                        }
                    }
                }
            }

            if (!found) return {};
            std::vector<int> path;
            for (int cur = sink; cur != -1; cur = prev[cur])
            {
                path.push_back(cur);
                if (cur == source) break;
            }
            std::reverse(path.begin(), path.end());
            return path;
        };

        while (true)
        {
            auto path = findPath();
            if (path.empty()) break;
            int bottleneck = INF;
            for (size_t i = 1; i < path.size(); ++i)
                bottleneck = std::min(bottleneck, cap[{path[i - 1], path[i]}]);
            for (size_t i = 1; i < path.size(); ++i)
            {
                cap[{path[i - 1], path[i]}] -= bottleneck;
                cap[{path[i], path[i - 1]}] += bottleneck;
            }
        }

        for (const auto& e : edges)
        {
            int flow = originalCap[{e.From, e.To}] - cap[{e.From, e.To}];
            if (flow < 0) flow = 0;
            g.SetEdgeWeight(e.From, e.To, flow);
            if (flow > 0) g.SetEdgeActive(e.From, e.To, true);
        }
    }
}

void RunFordFulkerson(BaseGraph& g, int source, int sink)
{
    runFlowAlgorithm(g, source, sink, false);
}

void RunEdmondsKarp(BaseGraph& g, int source, int sink)
{
    runFlowAlgorithm(g, source, sink, true);
}

namespace
{
    std::unique_ptr<BaseGraph> makeGraph(int storageKind, const std::string& file)
    {
        if (storageKind == 0) return std::make_unique<AdjacencyListGraph>(file);
        if (storageKind == 1) return std::make_unique<AdjacencyMatrixGraph>(file);
        return std::make_unique<EdgeListGraph>(file);
    }

    const char* storageName(int storageKind)
    {
        if (storageKind == 0) return "List";
        if (storageKind == 1) return "Matrix";
        return "EdgeList";
    }
}

int main()
{
    const std::vector<std::string> testFiles = {"test1.txt", "test2.txt", "test3.txt"};

    Visualizer visualizer;

    struct Algorithm
    {
        std::string Name;
        std::function<void(BaseGraph&, int, int)> Run;
    };

    const std::vector<Algorithm> algorithms = {
        {"BFS",            [](BaseGraph& g, int s, int)   { RunBFS(g, s); }},
        {"DFS",            [](BaseGraph& g, int s, int)   { RunDFS(g, s); }},
        {"Kruskal MST",    [](BaseGraph& g, int, int)     { RunKruskal(g); }},
        {"Prim MST",       [](BaseGraph& g, int s, int)   { RunPrim(g, s); }},
        {"Bellman-Ford",   [](BaseGraph& g, int s, int t) { RunBellmanFord(g, s, t); }},
        {"Dijkstra",       [](BaseGraph& g, int s, int t) { RunDijkstra(g, s, t); }},
        {"Floyd-Warshall", [](BaseGraph& g, int s, int t) { RunFloydWarshall(g, s, t); }},
        {"Johnson",        [](BaseGraph& g, int s, int t) { RunJohnson(g, s, t); }},
        {"Ford-Fulkerson", [](BaseGraph& g, int s, int t) { RunFordFulkerson(g, s, t); }},
        {"Edmonds-Karp",   [](BaseGraph& g, int s, int t) { RunEdmondsKarp(g, s, t); }},
    };

    for (const auto& algo : algorithms)
    {
        for (size_t fileIdx = 0; fileIdx < testFiles.size(); ++fileIdx)
        {
            const auto& file = testFiles[fileIdx];
            const int storageKind = static_cast<int>(fileIdx % 3);

            AdjacencyListGraph proto(file);
            const auto verts = proto.GetVertices();
            if (verts.empty()) continue;
            const int source = verts.front().Id;
            const int sink = verts.back().Id;

            const std::string testTag = "T" + std::to_string(fileIdx + 1) +
                                        " (" + storageName(storageKind) + ")";

            auto g = makeGraph(storageKind, file);
            algo.Run(*g, source, sink);
            visualizer.AddGraph(algo.Name + " | " + testTag, g->ToJson());
        }
    }

    visualizer.Visualize("graphs.html");
    return 0;
}
