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

void scaling (std::map<pair<Graph::vertex_descriptor,Graph::vertex_descriptor> , double> &);
std::map<pair<Graph::vertex_descriptor,Graph::vertex_descriptor> , double> edgeBetweenness (Graph&);
int main() {
    Graph g;
    Dproperty dp;

    std::ifstream graphFile ("../RandomGraphs/barbell_example.graphml");


    read_graphml(graphFile, g, dp);

//    for (int i = 0; i < g.m_vertices.at(0).m_out_edges.size(); i++){
//        cout << g.m_vertices.at(0).m_out_edges[i].m_target << endl;
//    }

    auto betweenness = edgeBetweenness(g);

    vector <pair<Graph::vertex_descriptor,Graph::vertex_descriptor> > edgesToBeRemoved;
    double maxBetweenness = 0;

    for (auto const& iter : betweenness){
        cout << "Edge: ( " << iter.first.first << ", " << iter.first.second << " ): " << iter.second << endl;

        if (maxBetweenness < iter.second){
            maxBetweenness = iter.second;
            edgesToBeRemoved.clear();
            edgesToBeRemoved.push_back(iter.first);
        }
        else if (maxBetweenness == iter.second)
            edgesToBeRemoved.push_back(iter.first);
    }

    cout << endl;

    for (int i = 0; i < edgesToBeRemoved.size(); i++){
        for (auto edge : boost::make_iterator_range(edges(g))){
            if (edgesToBeRemoved[i].first == edge.m_source && edgesToBeRemoved[i].second == edge.m_target){
                cout << "Removed Edge: " << edge << endl;
                g.remove_edge(edge);
                break;
            }
        }
    }

    cout << "\nBetweenness after edge removal:" << endl;

    betweenness = edgeBetweenness(g);

    edgesToBeRemoved.clear();
    maxBetweenness = 0;

    for (auto const& iter : betweenness){
        cout << "Edge: ( " << iter.first.first << ", " << iter.first.second << " ): " << iter.second << endl;

        if (maxBetweenness < iter.second){
            maxBetweenness = iter.second;
            edgesToBeRemoved.clear();
            edgesToBeRemoved.push_back(iter.first);
        }
        else if (maxBetweenness == iter.second)
            edgesToBeRemoved.push_back(iter.first);
    }


    return 0;

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
}

void scaling (std::map<pair<Graph::vertex_descriptor,Graph::vertex_descriptor> , double> &betweenness){
    for (auto &iter : betweenness) {
        iter.second /= 2;
    }

}

std::map<pair<Graph::vertex_descriptor,Graph::vertex_descriptor> , double> edgeBetweenness (Graph &g){
    std::map<pair<Graph::vertex_descriptor,Graph::vertex_descriptor> , double> edge_centralities;
    for (auto edge : boost::make_iterator_range(edges(g))) {
        pair<Graph::vertex_descriptor, Graph::vertex_descriptor> w;
        w.first = edge.m_source;
        w.second = edge.m_target;
        edge_centralities[w] = 0;
    }
    for (auto v : boost::make_iterator_range(vertices(g))){
        map <Graph::vertex_descriptor, bool> visited;
        vector <Graph::vertex_descriptor> src;
        src.push_back(v);
        map <Graph::vertex_descriptor, pair <double, double> > vScore;
        //g.m_vertices[v].m_property.m_value.first += 1;
        //pair<double,double> d (0,0);
        vScore[v].first += 1;
        vScore[v].second += 1;
        //vScore.at(v).first += 1;
        //vector <vector<Graph::vertex_descriptor> > edgePath;
        vector <map<Graph::vertex_descriptor,vector<Graph::vertex_descriptor> > > edgePaths;

        for (auto v : boost::make_iterator_range(vertices(g)))
            visited.insert(pair<Graph::vertex_descriptor,bool>(v,false));

        while (true){
            //visited.at(src) = true;
            for (int i = 0; i < src.size(); i++){
                visited.at(src[i]) = true;
            }
            vector <Graph::vertex_descriptor> nextSrc;
            map<Graph::vertex_descriptor,vector<Graph::vertex_descriptor> > currentPath;
            for (int i = 0; i < src.size(); i++){
                auto edges = g.m_vertices.at(src[i]).m_out_edges;

                for (int j = 0; j < edges.size(); j++){
                    if (!visited.at(edges[j].m_target)){
                        nextSrc.push_back(edges[j].m_target);
                        vScore[edges[j].m_target].first += vScore[src[i]].first;
                        vScore[edges[j].m_target].second = 1;
                        currentPath[edges[j].m_target].push_back(src[i]);
                    }

                }


            }
            if (nextSrc.size() == 0)
                break;
            else {
                edgePaths.push_back(currentPath);
                src = nextSrc;
            }


        }

        //int i = 0;

        //map<Graph::vertex_descriptor,vector<Graph::vertex_descriptor> >::iterator it;

       // for (it = symbolTable.begin(); it != symbolTable.end(); it++)
       for (int i = edgePaths.size() - 1; i > -1; i--){
            auto levelNodes = edgePaths[i];

            for (auto const& j : levelNodes){
                auto edges = j.second;
                for (int k = 0; k < edges.size(); k++){
                    //g.m_vertices.at(src[i])
                    double btwVal = vScore.at(j.first).second * vScore.at(edges[k]).first / vScore.at(j.first).first;
                    pair <Graph::vertex_descriptor, Graph::vertex_descriptor> w;
                    w.first = j.first;
                    w.second = edges[k];
                    if (edge_centralities.count(w) == 0) {
                        w.first = edges[k];
                        w.second = j.first;
                    }
                    edge_centralities.at(w) += btwVal;
                    vScore.at(edges[k]).second += btwVal;

                }
            }



        }

    }
    scaling (edge_centralities);
    return edge_centralities;

}