#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

void dfs(int node, vector<int> &vis, vector<int> adj[], stack<int> &st) {
    vis[node] = 1;
    for (auto it : adj[node]) {
        if (!vis[it]) {
            dfs(it, vis, adj, st);
        }
    }
    st.push(node);
}

void dfs_reverse(int node, vector<int> &vis, vector<int> adj[], vector<int> &component) {
    vis[node] = 1;
    component.push_back(node);
    for (auto it : adj[node]) {
        if (!vis[it]) {
            dfs_reverse(it, vis, adj, component);
        }
    }
}

int kosaraju(int V, vector<int> adj[], vector<vector<int>> &cfcs) {
    vector<int> vis(V, 0);
    stack<int> st;

    for (int i = 0; i < V; i++) {
        if (!vis[i]) {
            dfs(i, vis, adj, st);
        }
    }

    vector<int> adjT[V];
    for (int i = 0; i < V; i++) {
        vis[i] = 0;
        for (auto it : adj[i]) {
            adjT[it].push_back(i);
        }
    }

    while (!st.empty()) {
        int node = st.top();
        st.pop();
        if (!vis[node]) {
            vector<int> component;
            dfs_reverse(node, vis, adjT, component);
            cfcs.push_back(component);
        }
    }
    return cfcs.size();
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> adj[n];
    for (int i = 0; i < m; ++i) {
        int v1, v2, w;
        cin >> v1 >> v2 >> w;
        adj[v1].push_back(v2);
    }

    vector<vector<int>> cfcs;
    int cfc = kosaraju(n, adj, cfcs);

    cout << "The number of strongly connected components is: " << cfc << endl;

    cout << "Strongly connected components:\n";
    for (int i = 0; i < cfcs.size(); ++i) {
        cout << "Component " << i + 1 << ": ";
        for (int j = 0; j < cfcs[i].size(); ++j) {
            cout << cfcs[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
