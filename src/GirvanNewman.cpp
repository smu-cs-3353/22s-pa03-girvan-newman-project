//
// Created by Braiden Hook on 4/12/22.
//

#include "GirvanNewman.h"

GirvanNewman::GirvanNewman() {
    Graph g;
    Dproperty dp;

    dp.property("value", boost::get(&VertexProperty::dataKey, g));

    std::ifstream graphFile ("../RandomGraphs/barbell_example.graphml");


    read_graphml(graphFile, g, dp);

    double edgeCount = g.m_edges.size();



    int count = 0;

    double maxModularity = 100000;
    double currModularity =100000;

    Graph oldG;

    while (true){
//        if (count != 0)
//            maxModularity = currModularity;

        oldG = Graph();
        boost::copy_graph(g, oldG);
        auto betweenness = edgeBetweenness(g);
        vector <pair<Graph::vertex_descriptor,Graph::vertex_descriptor> > edgesToBeRemoved;
        double maxBetweenness = 0;

        for (auto const& iter : betweenness){
            //cout << "Edge: ( " << iter.first.first << ", " << iter.first.second << " ): " << iter.second << endl;

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

        currModularity = calculateModularity(oldG, g, edgeCount);

        cout << currModularity << endl;



        if (count != 0 && maxModularity >= currModularity + .002){
            cout << "Following the removal of the previous edge, the current modularity (" << currModularity + .002
                 << ") is unable to exceed the max modularity (" << maxModularity << ")\n"
                 << "As such the graph will regress back to the state prior to the removal of the last edge(s)." << endl;
            g = oldG;
            break;
        }
        count++;
        maxModularity = currModularity;
    }

    std::vector< int > component(num_vertices(g));
    int num = connected_components(g, &component[0]);

    std::vector< int >::size_type i;
    cout << "Total number of components: " << num << endl;
    for (i = 0; i != component.size(); ++i)
        cout << "Vertex " << i << " is in component " << component[i] << " -> real component "
             << endl;
    cout << endl;

    ofstream output("test.graphml");

    write_graphml(output, g, dp, true);

    ofstream output2("output.txt");

    for (auto v : make_iterator_range(vertices(g)))
        output2 << component [v] << endl;
}

void GirvanNewman::scaling (std::map<pair<Graph::vertex_descriptor,Graph::vertex_descriptor> , double> &betweenness){
    for (auto &iter : betweenness) {
        iter.second /= 2;
    }

}

std::map<pair<Graph::vertex_descriptor,Graph::vertex_descriptor> , double> GirvanNewman::edgeBetweenness (Graph &g){
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

double GirvanNewman::calculateModularity(Graph& oldG, Graph& newG, double edgeCount){
//
//    double res = 0;
//
//    // Iterating through the old vertices range
//    // Getting the adjacent vertices and counts how many of them there are before going into the inner loop
//    // The inner loop does the same thing at the start getting the adjacent vertices and counts how many there are
//    // Then it goes on to check if the vertex in the new graph is still adjacent to the old vertices
//    // If it is then it A will = 1, if not A = 0
//    // Amd then it will run the equation and increment itself with each loop
//
//    for (auto oldV : boost::make_iterator_range(vertices(oldG))){
//
//        auto adjacent_old = boost::adjacent_vertices(oldV,oldG);
//        int old_numAttached = 0;
//
//        for (auto buffer : make_iterator_range(adjacent_old))
//            old_numAttached++;
//        // Was met to find specific community for node, but not nodded
//        /*vector <Graph::vertex_descriptor> community;
//        bool arrived = false;
//        for (auto oldV2 : boost::make_iterator_range(vertices(oldG))){
//            if (oldV2 == oldV)
//                arrived = true;
//            if (arrived)
//                community.push_back(oldV2);
//        }*/
//
//        for (auto newV : boost::make_iterator_range(vertices(newG))){
//
//            auto adjacent_new = boost::adjacent_vertices(newV,newG);
//            int new_numAttached = 0;
//
//            for (auto buffer : make_iterator_range(adjacent_new))
//                new_numAttached++;
//
//            double A = 0;
//            for (auto adj : make_iterator_range(adjacent_old)) {
//                if (adj == newV) {
//                    A = 1;
//                    break;
//                }
//            }
//            //old_numAttached = size of community old vertex is in
//            //new_numAttached = size of community new vertex is in
//            res += A - ((old_numAttached * new_numAttached) / (double)(oldG.m_edges.size() * 2));
//        }
//
//    }
//    //return res/(double)(oldG.m_edges.size() * 2);
//    return res;

    double res = 0;
    std::vector< int > component(num_vertices(newG));
    int num = connected_components(newG, &component[0]);
    map<int, vector<Graph::vertex_descriptor> > communities;

    for (auto newV : boost::make_iterator_range(vertices(newG)))
        communities[newV].push_back(newV);

    for (auto const& newV : communities){

        for (int i = 0; i < newV.second.size(); i++){
            vector<Graph::vertex_descriptor> combinations;
            for (auto edges : boost::make_iterator_range(out_edges(newV.second[i], newG))){
                if (newV.second[i] < edges.m_target)
                    combinations.push_back(edges.m_target);
            }
            for (int j = 0; j < combinations.size(); j++){
                double A = 0;

                bool targetExists = false;

                for (auto target : boost::make_iterator_range(out_edges(newV.second[i], oldG))) {
                    if (target.m_target == combinations[j]) {
                        targetExists = true;
                        break;
                    }
                }
                bool otherTargetExists = false;
                if (targetExists){
                    for (auto target : boost::make_iterator_range(out_edges(combinations[j], oldG))){
                        if (target.m_target == newV.second[i]){
                            otherTargetExists = true;
                            break;
                        }

                    }

                }

                if (targetExists && otherTargetExists)
                    A = 1;

                double numOfEdgesA = newG.m_vertices.at(newV.second[i]).m_out_edges.size();
                double numOfEdgesB = newG.m_vertices.at(combinations[j]).m_out_edges.size();
                res += A - (numOfEdgesA * numOfEdgesB) / (double)(oldG.m_edges.size() * 2);

            }

        }

    }

    return res / (oldG.m_edges.size() * 2);

}
