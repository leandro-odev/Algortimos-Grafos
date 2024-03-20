# import networkx as nx

# def read_weighted_dag(filename):
#     # Lê o grafo a partir do arquivo
#     graph = nx.read_weighted_edgelist(filename, delimiter=' ', nodetype=int)
#     return graph

# def test_bellman_ford(graph, source):
#     # Executa o algoritmo de Bellman-Ford
#     try:
#         shortest_paths = nx.single_source_bellman_ford_path_length(graph, source=source)
#         return shortest_paths
#     except nx.NetworkXUnbounded:
#         return "O grafo contém um ciclo negativo"

# # Exemplo de uso
# filename = "weighted_dag.txt"
# graph = read_weighted_dag(filename)
# source_vertex = 1
# shortest_paths = test_bellman_ford(graph, source_vertex)

# if isinstance(shortest_paths, str):
#     print(shortest_paths)
# else:
#     for target_vertex, shortest_path_length in shortest_paths.items():
#         print(f"Caminho mais curto de {source_vertex} para {target_vertex}: {shortest_path_length}")

import networkx as nx

def read_weighted_dag(filename):
    # Lê o grafo a partir do arquivo
    graph = nx.read_weighted_edgelist(filename, delimiter=' ', nodetype=int)
    return graph

# Exemplo de uso
filename = "meu_grafo.txt"
graph = read_weighted_dag(filename)

print("Arestas do grafo:")
for u, v, weight in graph.edges(data='weight'):
    print(f"{u} -> {v}, Peso: {weight}")
