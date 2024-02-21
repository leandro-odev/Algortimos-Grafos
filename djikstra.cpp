// g++ hello.cpp -o hello
// ./hello

#include <iostream>
#include <string>
#include <vector>   

using namespace std;


int main() {
    
    int n, m;
    cin >> n >> m;
    vector<vector<int>> arestas(m, vector<int>(3));
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        // arestas[i][0] = a;
        // arestas[i][1] = b;
        // arestas[i][2] = c;
        arestas[i].push_back(a);
        arestas[i].push_back(b);
        arestas[i].push_back(c);
    }

    for (int i = 0; i < m; i++) {
        cout << arestas[i][0] << " " << arestas[i][1] << " " << arestas[i][2] << endl;
    }

    




    return 0;
}