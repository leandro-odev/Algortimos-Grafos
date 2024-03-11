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

void dfs_reverse(int node, vector<int> &vis, vector<int> adj[]) {
    vis[node] = 1;
    for (auto it : adj[node]) {
        if (!vis[it]) {
            dfs_reverse(it, vis, adj);
        }
    }
}

int kosaraju(int V, vector<int> adj[]) {
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

    int scc = 0;
    while (!st.empty()) {
        int node = st.top();
        st.pop();
        if (!vis[node]) {
            scc++;
            dfs_reverse(node, vis, adjT);
        }
    }
    return scc;
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

    int ans = kosaraju(n, adj);
    cout << "The number of strongly connected components is: " << ans << endl;

    return 0;
}