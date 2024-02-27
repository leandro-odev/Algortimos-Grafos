// g++ hello.cpp -o hello
// ./hello

#include <iostream>
#include <vector>

using namespace std;

int infinite = 1000000;

typedef struct edge{
    int v, u, w;
} edge;


void bf() {
    int n, m;
    cin >> n >> m;
    vector<int> dist(n, infinite);
    dist[0] = 0;
    edge e[m];

    for(int i = 0; i < m; i++) {
        int v, u, w;
        cin >> v >> u >> w;
        v--; u--;
        e[i].v = v; e[i].u = u; e[i].w = w;
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(dist[e[j].v] != infinite && dist[e[j].v] + e[j].w < dist[e[j].u]) {
                dist[e[j].u] = dist[e[j].v] + e[j].w;
            }
        }
    }
    
}

void bf2(vector<vector<pair<int, int>>> & adj, int s, int m) {
    
    cout << "entrou bf2" << endl;
    int n = adj.size();
    vector<int> dist(n, infinite);
    dist[s] = 0;

    cout << "entrando no for 1" << endl;
    for(int i = 0; i < n; i++) {
        cout << "entrando no for 2" << endl;
        for(int j = 0; j < m; j++) {
            if(dist[adj[i][j].first] != infinite && dist[adj[i][j].first] + adj[i][j].second < dist[i]) {
                dist[i] = dist[adj[i][j].first] + adj[i][j].second;
            }
        }
    }
    
    cout << "Distances from " << s << ":" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "dist[" << i << "] = " << dist[i] << endl;
    }
}

void bellman_ford (vector<vector<pair<int, int>>> & adj, int s) {

    int n = adj.size();
    vector<int> dist(n, infinite);
    dist[s] = 0;

    for(int u = 0; u < n; u++) { // para cada vértice

        for(int j = 0; j < adj[u].size(); j++) { // para cada aresta que o vértice u aponta

            int v = adj[u][j].first;
            int w = adj[u][j].second;

            if(dist[u] != infinite && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }
    

    cout << "Distances from " << s << ":" << endl;
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
    }

    //bellman_ford(adj, 0);
    bf2(adj, 0, m);

    return 0;
}