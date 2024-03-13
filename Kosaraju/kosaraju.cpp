#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstring>
#include <fstream>
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

string kosaraju(int V, vector<int> adj[], vector<vector<int>> &cfcs) {
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

    string result = "";
    for (int i = 0; i < cfcs.size(); ++i) {
        for (int j = 0; j < cfcs[i].size(); ++j) {
            result += to_string(cfcs[i][j]);
            if(j < cfcs[i].size() - 1) {
                result += " ";
            }
        }
        result += "\n";
    }

    return result;
}

int main(int argc, char *argv[]) {

    string input_file = "";
    string output_file = "";
    bool show_output = false;
    int start_node = 1;

    for (int i=1; i<argc ; i++){
        if(strcmp(argv[i], "-h") == 0){
            cout << "Help" << endl;
            cout << "-h: mostra help" << endl;
            cout << "-o <arquivo>: redireciona a saída para o arquivo" << endl;
            cout << "-f <arquivo>: lê o grafo do arquivo" << endl;

            return 0;

        } else if(strcmp(argv[i], "-o") == 0){
            output_file = argv[i+1];
        }
        else if(strcmp(argv[i], "-f") == 0){
            input_file = argv[i+1];
        }
    }

    if (input_file == ""){
        cout << "No input file specified. Use the -f parameter" << endl;
        return 1;
    }
    ifstream fin(input_file);
    if(!fin){
        cerr << "Could not open input file: " << input_file << endl;
        return 1;
    }

    int n, m;
    fin >> n >> m;

    vector<int> adj[n];
    int v1, v2, w;
    for (int i = 0; i < m; ++i) {
        fin >> v1 >> v2 >> w;
        adj[v1].push_back(v2);
    }

    vector<vector<int>> cfcs;
    string result = kosaraju(n, adj, cfcs);

    if(!(output_file == "")){
        ofstream fout(output_file);
        if(!fout){
            cerr << "Could not open output file: " << output_file << endl;
            return 1;
        }
        fout << result;
        fout << endl;

        fout.close();
    }
    cout << result << endl;

    return 0;
}
