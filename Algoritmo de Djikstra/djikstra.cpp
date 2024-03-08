// g++ hello.cpp -o hello
// ./hello

#include <iostream>
#include <vector>

using namespace std;

int infinite = 1000000;

void djikstra (vector<vector<pair<int, int>>> & adj, int s) {

    int n = adj.size();
    vector<int> dist(n, infinite);
    dist[s] = 0;
    vector<bool> visited(n, false);

    for (int i = 0; i < n; ++i) {
        int u = -1;
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        visited[u] = true;

        for (int j = 0; j < adj[u].size(); ++j) {
            int v = adj[u][j].first;
            int w = adj[u][j].second;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    cout << "Distances from " << s << endl;
    for (int i = 0; i < n; ++i) {
        cout << "dist[" << i << "] = " << dist[i] << endl;
    }
}

int main() {
    
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < n; ++i) {
        adj[i] = vector<pair<int, int>>();
    }

    int v1, v2, w;
    for (int i = 0; i < m; ++i) {
        cin >> v1 >> v2 >> w;
        adj[v1].push_back(make_pair(v2, w));
        adj[v2].push_back(make_pair(v1, w));
    }

    djikstra(adj, 0);

    return 0;
}