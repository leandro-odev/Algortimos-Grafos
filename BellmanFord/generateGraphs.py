import random

# Number of vertices and edges
num_vertices = 200
num_edges = 14834

# Generate random edges
edges = []
for i in range(num_edges):
    source = random.randint(1, num_vertices) +1
    target = random.randint(1, num_vertices) +1
    while source == target or (source, target) in edges or (target, source) in edges:
        target = random.randint(1, num_vertices) +1
    weight = random.randint(-30, 30)
    edges.append((source, target, weight))

# Write the edges to file
try:
    with open("BellmanFord/teste.dat", "w") as f:
        f.write(f"{num_vertices} {num_edges}\n")
        for edge in edges:
            f.write(f"{edge[0]} {edge[1]} {edge[2]}\n")
    print("Edges have been successfully written to teste.dat")
except Exception as e:
    print("An error occurred:", e)