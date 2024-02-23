#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> pre;
vector<int> pai;
int cnt = 0;
int comp_conexas = 0;

void dfs_rec(vector<vector<int>> &adj, int v) {
    pre[v] = cnt++;

    for (int i = 0; i < adj[v].size(); ++i) {
        int w = adj[v][i];

        if (pre[w] == -1) {
            pai[w] = v;
            dfs_rec(adj, w);
        }
    }
}

void dfs(vector<vector<int>> &adj) {
    int n = adj.size();
    for (int v = 0; v < n; ++v) {
        pre[v] = -1;
        pai[v] = -1;
    }

    for (int v = 0; v < n; ++v) {
        if (pre[v] == -1) {
            comp_conexas++;
            dfs_rec(adj, v);
        }
    }
}

int kosaraju(int V, vector<vector<int>> &adj) {
    dfs(adj);

    vector<vector<int>> adjT(V);
    for (int i = 0; i < V; i++) {
        for (auto it : adj[i]) {
            adjT[it].push_back(i);
        }
    }

    vector<int> vis(V, 0);
    
    comp_conexas = 0;

    for (int i = V - 1; i >= 0; i--) {
        int node = pre[i];
        if (!vis[node]) {
            dfs_reverse(node, vis, adjT);
            comp_conexas++;
        }
    }
    
    return comp_conexas;
}

void dfs_reverse(int node, vector<int> &vis, vector<vector<int>> &adjT) {
    vis[node] = 1;
    for (auto it : adjT[node]) {
        if (!vis[it]) {
            dfs_reverse(it, vis, adjT);
        }
    }
}

int main() {
    int n, m;

    cin >> n >> m;

    vector<vector<int>> adj(n);
    for (int i = 0; i < n; ++i) {
        adj[i] = vector<int>();
    }

    pre = vector<int>(n);
    pai = vector<int>(n);

    int v1, v2;
    for (int i = 0; i < m; ++i) {
        cin >> v1 >> v2;
        adj[v1].push_back(v2);
        adj[v2].push_back(v1);
    }

    int ans = kosaraju(n, adj);

    cout << "The number of strongly connected components is: " << ans << endl;

    return 0;
}
