#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>

using namespace std;

int infinite = 1000000;

string djikstra (vector<vector<pair<int, int>>> & adj, int s) {

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

    // cout << "Distances from " << s << endl;
    // for (int i = 0; i < n; ++i) {
    //     cout << "dist[" << i << "] = " << dist[i] << endl;
    // }

    string distances = "1 ";
    for (int i = 0; i < n; ++i) {
        if(dist[i] != infinite) {
            distances += to_string(i) + ":" + to_string(dist[i]) + " ";
        }
        else {
            distances += to_string(i) + ":" + "-1" + " ";
        }
    }
    return distances;
}

int main(int argc, char *argv[]) {
    string input_file = "";
    string output_file = "";
    string show_output = "result";
    int start_node = 1;

    for (int i=1; i<argc ; i++){
        if(strcmp(argv[i], "-h") == 0){
            cout << "Help" << endl;
            cout << "-h: mostra help" << endl;
            cout << "-o <arquivo>: redireciona a saída para o arquivo" << endl;
            cout << "-f <arquivo>: lê o grafo do arquivo" << endl;
            cout << "-i : vértice inicial" << endl;

            return 0;

        } else if(strcmp(argv[i], "-o") == 0){
            output_file = argv[i+1];
            show_output = false;
        }
        else if(strcmp(argv[i], "-f") == 0){
            input_file = argv[i+1];
        }
        else if(strcmp(argv[i], "-i") == 0){
            start_node = atoi(argv[i+1]);
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

    int n, m; // numero de vertices e arestas
    fin >> n >> m; // recebendo n e m
    vector<vector<pair<int, int> > > adj(n + 1); // criando a matriz que emula um grafo

    for (int i = 0; i<m; i++) {
        int u, v, w; 
        fin >> u >> v >> w; // recebendo os vertices entre arestas
        adj[u].push_back(make_pair(v, w)); // adiciona v nos vizinhos de u
        adj[v].push_back(make_pair(u, w)); // adiciona u nos vizinhos de v
    }

    fin.close();

    string distances = djikstra(adj, start_node);

    if(!(output_file == "")){
        ofstream fout(output_file);
        if(!fout){
            cerr << "Could not open output file: " << output_file << endl;
            return 1;
        }
        fout << distances;
        fout << endl;

        fout.close();
    }

    return 0;
}