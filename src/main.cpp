//
// Created by mikec_g1kgiu8 on 4/4/2022.
//
#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/range/irange.hpp>

//using namespace std;
using namespace boost;

int main() {
    typedef adjacency_list<vecS, vecS, undirectedS, no_property, no_property> Graph;
    typedef dynamic_properties Dproperty;

    Graph g;
    Dproperty dp;

    std::ifstream graphFile ("../RandomGraphs/test.graphml");

    read_graphml(graphFile, g, dp);

    std::map<int, int> node_labels; //holds the current label for each node
    std::map<int, std::vector<int>> neighbor_nodes; //holds the labels of the current node's neighbors

    // Printing edges
    for (auto v : boost::make_iterator_range(vertices(g))) {
        std::cout << "Node " << v << std::endl;
        node_labels[v] = v; //Initializing each node with its own unique label

        //the following code was found at: https://stackoverflow.com/questions/49898415/boost-library-how-to-get-neighbouring-nodes
        auto neighbors = boost::adjacent_vertices(v, g);
        for (auto vd : make_iterator_range(neighbors)) {
            std::cout << v << " has adjacent vertex " << vd << std::endl;
            neighbor_nodes[v].push_back(vd); //adds each neighboring node to the vector
        }

//        for (auto oe : make_iterator_range(out_edges(v, g))){
//            std::cout << "Edge " << oe << std::endl;
//        }
    }

    for (auto v : boost::make_iterator_range(vertices(g))) { //FIXME this needs to be done in a random order
        std::cout << "Currently on node " << v << std::endl;
        std::unordered_map<int, int> label_frequency;

        int new_label = -1;
        int new_label_frequency = 0;

        for (int i = 0; i < neighbor_nodes[v].size(); i++) {
            label_frequency[node_labels[neighbor_nodes[v].at(i)]] += 1;

            std::cout << label_frequency[node_labels[neighbor_nodes[v].at(i)]] << std::endl;
            if (label_frequency[node_labels[neighbor_nodes[v].at(i)]] > new_label_frequency) { //FIXME if there are ties, it needs to be broken randomly
                new_label = node_labels[neighbor_nodes[v].at(i)];
            }
        }

        node_labels[v] = new_label;

    }

    for (auto v : boost::make_iterator_range(vertices(g))) {
        std::cout << "Node " << v << "'s label is " << node_labels[v] << std::endl;
    }

    //cout << node_labels[1] << endl;
}