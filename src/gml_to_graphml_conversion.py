import networkx as nx
import matplotlib.pyplot as plt

def start():
    H = nx.read_gml("/Users/braidenhook/Downloads/football/football.gml")

    G = nx.write_graphml_lxml(H, "football.graphml")
    X = nx.read_graphml('football.graphml')
    nx.draw(X)
    plt.show()

if __name__ == '__main__':
    start()

