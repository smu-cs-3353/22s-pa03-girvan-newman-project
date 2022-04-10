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
#include <set>
//#include <boost/fusion/include/push_back.hpp>

using namespace boost;
using namespace std;
typedef property<vertex_name_t,pair<double,double> > VertexProperties;
typedef property<edge_name_t, double> EdgeProperties;
typedef adjacency_list<vecS, vecS, undirectedS, VertexProperties, EdgeProperties> Graph;
typedef dynamic_properties Dproperty;

_Noreturn void edgeBetweenness (Graph);
int main() {
    Graph g;
    Dproperty dp;

    std::ifstream graphFile ("../RandomGraphs/barbell_example.graphml");


    read_graphml(graphFile, g, dp);

    for (int i = 0; i < g.m_vertices.at(0).m_out_edges.size(); i++){
        cout << g.m_vertices.at(0).m_out_edges[i].m_target << endl;
    }
    edgeBetweenness(g);

    /*map <pair<Graph::vertex_descriptor, Graph::vertex_descriptor>, Graph::edge_descriptor> vertexToEdgeMap;

    for (auto edge : boost::make_iterator_range(edges(g))) {
        vertexToEdgeMap.insert(pair<edge.m_target, edge.m_target>, edge>)
    }*/

    /*std::map<Graph::edge_descriptor, double> edge_centralities;
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

    write_graphml(output, g, dp, true);*/

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


_Noreturn void edgeBetweenness (Graph g){
    std::map<Graph::edge_descriptor, double> edge_centralities;
    for (auto v : boost::make_iterator_range(vertices(g))){
        map <Graph::vertex_descriptor, bool> visited;
        vector <Graph::vertex_descriptor> src;
        src.push_back(v);
        map <Graph::vertex_descriptor, pair <double, double> > vertexScore;
        //g.m_vertices[v].m_property.m_value.first += 1;
        //pair<double,double> d (0,0);
        vertexScore[v].first += 1;
        //vertexScore.at(v).first += 1;
        //vector <vector<Graph::vertex_descriptor> > edgePath;
        vector <map<Graph::vertex_descriptor,vector<Graph::vertex_descriptor> > > edgePaths;

        for (auto v : boost::make_iterator_range(vertices(g)))
            visited.insert(pair<Graph::vertex_descriptor,bool>(v,false));

        while (true){
            //visited.at(src) = true;
            vector <Graph::vertex_descriptor> nextSrc;
            map<Graph::vertex_descriptor,vector<Graph::vertex_descriptor> > currentPath;
            for (int i = 0; i < src.size(); i++){
                visited.at(src[i]) = true;
                auto edges = g.m_vertices.at(src[i]).m_out_edges;

                for (int j = 0; j < edges.size(); j++){
                    if (!visited.at(edges[j].m_target)){
                        nextSrc.push_back(edges[j].m_target);
                        vertexScore[edges[j].m_target].first += vertexScore[v].first;
                        if (currentPath.count(edges[j].m_target) == 0){
                            //pair <edges[j].m_target, vector<Graph::vertex_descriptor> >
                            //currentPath.insert(pair <edges[j].get_target(), vector<Graph::vertex_descriptor> >);
                        }
                    }

                }


            }



        }

    }



}