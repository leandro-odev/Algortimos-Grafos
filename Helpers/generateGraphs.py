import networkx as nx
import random

num_nodes = random.randint(1, 100)
num_edges = random.randint(400, 500)

def salvar_grafo_txt(grafo, arquivo_destino):
    """
    Salva o grafo no arquivo de destino especificado no formato:
    <numero de vertices> <numero de arestas>
    <origem> <destino> <peso>
    ...
    
    :param grafo: O objeto grafo gerado pelo NetworkX.
    :param arquivo_destino: Caminho do arquivo de destino para salvar o grafo.
    """
    with open(arquivo_destino, 'w') as f:
        num_vertices = grafo.number_of_nodes()
        num_arestas = grafo.number_of_edges()
        
        # Escreve o número de vértices e o número de arestas na primeira linha
        f.write(f"{num_vertices} {num_arestas}\n")
        
        # Para cada aresta no grafo, escreve os detalhes da aresta no arquivo
        for origem, destino, dados in grafo.edges(data=True):
            peso = dados['weight']
            f.write(f"{origem + 1} {destino + 1} {peso}\n")
            # +1 faz a conversão de base 0 para base 1, se necessário

def gerar_grafo_corrigido(vertices, arestas, peso_max=10, tentativas_max=1000):
    """
    Gera um grafo direcionado com uma quantidade especificada de vértices e arestas.
    As arestas têm pesos aleatórios, podendo ser negativos, mas o grafo não terá ciclos negativos.

    :param vertices: Número de vértices no grafo.
    :param arestas: Número máximo de arestas no grafo.
    :param peso_max: Peso máximo (absoluto) para as arestas.
    :param tentativas_max: Número máximo de tentativas para adicionar uma nova aresta sem introduzir ciclos negativos.
    :return: O objeto grafo gerado.
    """
    G = nx.DiGraph()
    G.add_nodes_from(range(vertices))
    
    arestas_adicionadas = 0
    tentativas = 0

    while arestas_adicionadas < arestas and tentativas < tentativas_max:
        origem = random.randint(0, vertices - 1)
        destino = random.randint(0, vertices - 1)
        if origem != destino and not G.has_edge(origem, destino):
            peso = random.randint(-peso_max, peso_max)
            G.add_edge(origem, destino, weight=peso)

            # Verifica se o grafo contém ciclos negativos usando Bellman-Ford para cada vértice como fonte
            ciclo_negativo_encontrado = False
            for v in G.nodes:
                try:
                    nx.bellman_ford_path(G, v, v, weight='weight')
                except nx.NetworkXNegativeCycle:
                    ciclo_negativo_encontrado = True
                    break
            
            if ciclo_negativo_encontrado:
                # Se encontrou um ciclo negativo, remove a aresta
                G.remove_edge(origem, destino)
            else:
                # Se não encontrou ciclos negativos, mantém a aresta
                arestas_adicionadas += 1
        tentativas += 1

    return G

# Corrigindo o erro e gerando o grafo novamente
grafo_corrigido = gerar_grafo_corrigido(num_nodes, num_edges)
pos_corrigido = nx.spring_layout(grafo_corrigido)

# Chama a função para salvar o grafo
salvar_grafo_txt(grafo_corrigido, "meu_grafo.txt")