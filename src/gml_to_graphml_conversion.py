import networkx as nx
import matplotlib.pyplot as plt

def start():
    #H = nx.read_gml("Users\mikec_g1kgiu8\OneDrive\Desktop\CS 3353 Projects\22s-pa03-girvan-newman-a-loner-s-regret\RandomGraphs\test.gml")
    
    #G = nx.write_graphml_lxml(H, "test.graphml")
    #X = nx.read_graphml('test.graphml')
    #X = nx.read_graphml("../RandomGraphs/randomGraph.graphml")
    #X = nx.read_graphml("../tester.graphml")
    X = nx.read_graphml("../karateClub.graphml")
    nx.draw(X)
    plt.show()

if __name__ == '__main__':
    start()

