// g++ hello.cpp -o hello
// ./hello

#include <iostream>
#include <string>
#include <vector>   

using namespace std;


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

    

    return 0;
}