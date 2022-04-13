#from networkx.generators.random_graphs import erdos_renyi_graph
import networkx as nx
import matplotlib.pyplot as plt


n = 100
p = 0.03
g = nx.erdos_renyi_graph(n, p)

nx.draw(g)
plt.show()

nx.write_graphml(g, "../RandomGraphs/randomGraph1.graphml")
X = nx.read_graphml("../RandomGraphs/randomGraph1.graphml")

nx.draw(X)
plt.show()

print(g.nodes)
# [0, 1, 2, 3, 4, 5]

print(g.edges)
num = 0
for edge in g.edges:
    num += 1
print("Num edges:", num)
    
# [(0, 1), (0, 2), (0, 4), (1, 2), (1, 5), (3, 4), (4, 5)]