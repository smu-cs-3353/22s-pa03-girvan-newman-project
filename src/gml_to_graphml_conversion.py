import networkx as nx
import matplotlib.pyplot as plt

def start():
    #H = nx.read_gml("../karate.gml", label ='id')
    
    #G = nx.write_graphml_lxml(H, "../RandomGraphs/karateClub.graphml")
    #X = nx.read_graphml("../RandomGraphs/karateClub.graphml")
    X = nx.read_graphml("../RandomGraphs/newbie.graphml")
        
    nx.draw(X,
            node_color = "blue",
            with_labels = True,
            font_color = "white")
    plt.show()

if __name__ == '__main__':
    start()
