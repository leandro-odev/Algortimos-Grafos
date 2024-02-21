// g++ hello.cpp -o hello
// ./hello

#include <iostream>
#include <string>
#include <vector>   

using namespace std;


int main() {
    
    int n, m;
    cin >> n >> m;
    vector<vector<int>> arestas(m, vector<int>(n, 0));
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        arestas[i][0] = a;
        arestas[i][1] = b;
        arestas[i][2] = c;
    }

    




    return 0;
}