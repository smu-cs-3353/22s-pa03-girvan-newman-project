//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <iostream>
#include <boost/parameter/parameters.hpp>
#include <boost/pending/indirect_cmp.hpp>
#include <boost/range/irange.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/betweenness_centrality.hpp>
//#include <boost/fusion/include/push_back.hpp>

using namespace boost;
using namespace std;

int main() {
    typedef adjacency_list<vecS, vecS, undirectedS, no_property, no_property> Graph;
    typedef dynamic_properties Dproperty;
    Graph g;
    Dproperty dp;

    std::ifstream graphFile ("../RandomGraphs/barbell_example.graphml");


    read_graphml(graphFile, g, dp);

    std::map<Graph::edge_descriptor, double> edge_centralities;
    auto ecm = boost::make_assoc_property_map(edge_centralities);


    brandes_betweenness_centrality(g, boost::edge_centrality_map(ecm));

    double maxEdgeBetweeness = 0;

    vector<Graph::edge_descriptor> edgesToBeRemoved;

    for (auto edge : boost::make_iterator_range(edges(g))) {
        std::cout << edge_centralities.at(edge) << "\n";

        if (edge_centralities.at(edge) > maxEdgeBetweeness){
            maxEdgeBetweeness = edge_centralities.at(edge);
            edgesToBeRemoved.clear();
            edgesToBeRemoved.push_back(edge);
        }
        else if (edge_centralities.at(edge) == maxEdgeBetweeness)
            edgesToBeRemoved.push_back(edge);

    }

    for (int i = 0; i < edgesToBeRemoved.size(); i++)
        g.remove_edge(edgesToBeRemoved[i]);

    brandes_betweenness_centrality(g, boost::edge_centrality_map(ecm));
    for (auto edge : boost::make_iterator_range(edges(g)))
        std::cout << edge_centralities.at(edge) << "\n";



    // Printing Adjacency List
    for (auto v : boost::make_iterator_range(vertices(g))) {
        //std::cout << "Vertex descriptor #" << v;
        std::cout << v << ": ";
        for (auto oe : make_iterator_range(out_edges(v, g))){
            std::cout << oe.m_target << " ";
        }
        std::cout << std::endl;
    }

    ofstream output("test.graphml");

    write_graphml(output, g, dp, true);

//    for (auto v : boost::make_iterator_range(vertices(g))) {
//        std::cout << "Vertex descriptor #" << v;
//        for (auto oe : make_iterator_range(out_edges(v, g))){
//            std::cout << oe << std::endl;
//        }
//    }

    /*for (int i = 0; i < g.m_edges.size(); i++){
        std::cout << g.m_edges[0].m_source << "-" << g.m_edges[0].m_target << std::endl;
    }*/
    int i = 0;
}