# -*- coding: utf-8 -*-
"""
Created on Mon Apr 11 21:53:00 2022

@author: mikec_g1kgiu8
"""
import networkx as nx
import matplotlib.pyplot as plt

val_map = { }

f = open('../extra/outputForGraph_GN.txt', 'r')
f2 = open('../extra/schoolNames.txt', 'r')

for label in f:
    ID = next(f2).strip()
    val_map[ID] = int(label)
    print(ID, val_map[ID])
        
print(val_map)
        
X = nx.read_graphml('../RandomGraphs/football.graphml')

values = [val_map.get(node, 0.25) for node in X.nodes()]
    
nx.draw(X,
        node_color = values,
        with_labels = True,
        font_color = "black")
plt.figure(1, figsize=(200,200), dpi=60)
plt.show()

        
        
