#from networkx.generators.random_graphs import erdos_renyi_graph
import networkx as nx
import matplotlib.pyplot as plt


n = 6
p = 0.5
g = nx.erdos_renyi_graph(n, p)

nx.draw(g)
plt.show()

nx.write_graphml(g, "../RandomGraphs/bigGraph.graphml")
X = nx.read_graphml("../RandomGraphs/bigGraph.graphml")

nx.draw(X)
plt.show()

print(g.nodes)
# [0, 1, 2, 3, 4, 5]

print(g.edges)
# [(0, 1), (0, 2), (0, 4), (1, 2), (1, 5), (3, 4), (4, 5)]