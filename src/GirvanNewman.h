//
// Created by Braiden Hook on 4/12/22.
//

#ifndef GML_TO_GRAPHML_CONVERSION_PY_GIRVANNEWMAN_H
#define GML_TO_GRAPHML_CONVERSION_PY_GIRVANNEWMAN_H

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <iostream>
#include <boost/parameter/parameters.hpp>
#include <boost/pending/indirect_cmp.hpp>
#include <boost/range/irange.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/copy.hpp>

using namespace boost;
using namespace std;
struct VertexProperty { //stores the data key in football.graphml
    long dataKey;
};

typedef adjacency_list<vecS, vecS, undirectedS, VertexProperty> Graph;
typedef dynamic_properties Dproperty;

class GirvanNewman {
private:
    void scaling (std::map<pair<Graph::vertex_descriptor,Graph::vertex_descriptor> , double> &);
    std::map<pair<Graph::vertex_descriptor,Graph::vertex_descriptor> , double> edgeBetweenness (Graph &);
    double calculateModularity(Graph& oldG, Graph& newG, double);

public:
    void runAlgo(char*);



};


#endif //GML_TO_GRAPHML_CONVERSION_PY_GIRVANNEWMAN_H
