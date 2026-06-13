#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <utility>

using namespace std;

using Edge = pair<int, int>;
const int INF = numeric_limits<int>::max();

vector<int> dijkstra(const vector<vector<Edge>>& graph, int source) {
    int n = graph.size();
    vector<int> dist(n, INF);
    dist[source] = 0;

    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (const auto& [v, weight] : graph[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main() {
    int n = 6;
    vector<vector<Edge>> graph(n);

    auto addEdge = [&](int u, int v, int w) {
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    };

    addEdge(0, 1, 4);
    addEdge(0, 2, 1);
    addEdge(2, 1, 2);
    addEdge(1, 3, 1);
    addEdge(2, 3, 5);
    addEdge(3, 4, 3);
    addEdge(4, 5, 2);
    addEdge(3, 5, 6);

    int source = 0;
    vector<int> dist = dijkstra(graph, source);

    cout << "Shortest distances from node " << source << ":\n";
    for (int i = 0; i < n; ++i) {
        cout << "  " << source << " -> " << i << " = ";
        if (dist[i] == INF) cout << "INF\n";
        else cout << dist[i] << "\n";
    }

    return 0;
}
