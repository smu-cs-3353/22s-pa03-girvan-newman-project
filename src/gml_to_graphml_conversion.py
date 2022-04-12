import networkx as nx
import matplotlib.pyplot as plt

def start():
    H = nx.read_gml("../football.gml")
    
    G = nx.write_graphml_lxml(H, "../RandomGraphs/football.graphml")
    X = nx.read_graphml('football.graphml')
    #X = nx.read_graphml("../RandomGraphs/randomGraph.graphml")
    #X = nx.read_graphml("../RandomGraphs/tester.graphml")
    #X = nx.read_graphml("../RandomGraphs/karateClub.graphml")
    
    val_map = {'1': 1.0,
               '2': 1.0,
               '3': 1.0,
               '4': 1.0,
               '5': 1.0,
               '6': 1.0,
               '7': 1.0,
               '8': 1.0,
               '9': 0,
               '10': 0,
               '11': 1.0,
               '12': 1.0,
               '13': 1.0,
               '14': 1.0,
               '15': 0,
               '16': 0,
               '17': 1.0,
               '18': 1.0,
               '19': 0,
               '20': 1.0,
               '21': 0,
               '22': 1.0,
               '23': 1.0,
               '24': 1.0,
               '25': 0,
               '26': 1.0,
               '27': 1.0,
               '28': 1.0,
               '29': 1.0,
               '30': 0,
               '31': 0,
               '32': 1.0,
               '33': 0,
               '34': 0,
               }
    
    values = [val_map.get(node, 0.25) for node in X.nodes()]
    
    nx.draw(X,
            node_color = "blue",
            with_labels = True,
            font_color = "white")
    plt.show()

if __name__ == '__main__':
    start()
