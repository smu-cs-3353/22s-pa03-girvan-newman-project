//
// Created by Braiden Hook on 4/12/22.
//

#include "GirvanNewman.h"

void GirvanNewman::runAlgo(char* filePath) {
    Graph g;
    Dproperty dp;

    dp.property("value", boost::get(&VertexProperty::dataKey, g));

    string fullPathName = filePath;

    std::ifstream graphFile (fullPathName);
    std::string fileName = fullPathName.substr(fullPathName.find_last_of("/\\") + 1);

    read_graphml(graphFile, g, dp);

    double edgeCount = g.m_edges.size();

    int count = 0;

    double maxModularity = 100000;
    double currModularity =100000;

    Graph oldG;

    // Loops while removing edges until the modularity starts to decrease
    while (true){

        oldG = Graph();
        boost::copy_graph(g, oldG);
        auto betweenness = edgeBetweenness(g); // Calculating betweenness
        vector <pair<Graph::vertex_descriptor,Graph::vertex_descriptor> > edgesToBeRemoved;
        double maxBetweenness = 0;
        // Finding bet edge to remove (The one with the highest betweenness)
        for (auto const& iter : betweenness){

            if (maxBetweenness < iter.second){
                maxBetweenness = iter.second;
                edgesToBeRemoved.clear();
                edgesToBeRemoved.push_back(iter.first);
            }
            else if (maxBetweenness == iter.second)
                edgesToBeRemoved.push_back(iter.first);
        }
        // Locating and removing edge
        for (int i = 0; i < edgesToBeRemoved.size(); i++){
            for (auto edge : boost::make_iterator_range(edges(g))){
                if (edgesToBeRemoved[i].first == edge.m_source && edgesToBeRemoved[i].second == edge.m_target){

                    g.remove_edge(edge);
                    break;
                }
            }
        }

        currModularity = calculateModularity(oldG, g, edgeCount); // Calculating modularity
        // Stops once modularity decreases and will go back to the prior graph since modularity was higher
        if (count != 0 && maxModularity >= currModularity + .002){
            g = oldG;
            break;
        }
        count++;
        maxModularity = currModularity;
    }

    // Specialized output for football graph
    if (fileName == "football.graphml") {

        std::vector<int> component(num_vertices(g));
        int num = connected_components(g, &component[0]);

        std::vector<int> labels; //holds all the labels that define each community

        std::ofstream output("../extra/outputForGraph_GN.txt");


        for (auto v: boost::make_iterator_range(vertices(g))) {
            if (std::find(labels.begin(), labels.end(), component[v]) == labels.end()) {
                labels.push_back(component[v]);
            }
            output << component[v] << std::endl;
        }

        output.close();

        std::sort(labels.begin(), labels.end()); //sorts the vector by increasing numerical order

        output.open("../output/GNOutput.txt"); //output file containing data on the communities

        output << "Communities For Girvan-Newman:\n" << std::endl;
        std::cout << "Communities For Girvan-Newman:\n" << std::endl;

        for (int i = 0; i < labels.size(); i++) { //outputs the communities generated
            std::cout << "Community " << i + 1 << std::endl;
            cout << endl;
            output << "Community " << i + 1 << std::endl;
            output << endl;
            std::ifstream input("../extra/schoolNames.txt");
            int counter2 = 0;
            while (!input.eof()) {
                std::string name;
                input >> name;
                if (component[counter2] == labels.at(i)) {
                    if (name != "") {
                        std::cout << name << " (" << counter2 << ")" << std::endl;
                        output << name << " (" << counter2 << ")" << std::endl;
                    }
                }
                counter2++;
            }
            input.close();
            std::cout << std::endl;
            output << std::endl;
        }
    }
    // Output for everything else
    else{

        std::vector<int> component(num_vertices(g));
        int num = connected_components(g, &component[0]);
        map<int, vector<Graph::vertex_descriptor> > nodesInCommunities;

        for (auto v: boost::make_iterator_range(vertices(g)))
            nodesInCommunities[component[v]].push_back(v);

        std::ofstream output("../output/GNOutput.txt");

        output << "Communities For Girvan-Newman:\n" << std::endl;
        std::cout << "Communities For Girvan-Newman:\n" << std::endl;

        for (auto const& iter : nodesInCommunities){
            std::cout << "Community " << iter.first + 1 << std::endl;
            cout << endl;
            output << "Community " << iter.first + 1 << std::endl;
            output << endl;
            for (int i = 0; i < iter.second.size(); i++){
                cout << iter.second[i] << endl;
                output << iter.second[i] << endl;

            }
            cout << endl;
            output << endl;

        }
    }
}

void GirvanNewman::scaling (std::map<pair<Graph::vertex_descriptor,Graph::vertex_descriptor> , double> &betweenness){
    for (auto &iter : betweenness) {
        iter.second /= 2;
    }

}

std::map<pair<Graph::vertex_descriptor,Graph::vertex_descriptor> , double> GirvanNewman::edgeBetweenness (Graph &g){

    // Map to contain the edge betweenness
    std::map<pair<Graph::vertex_descriptor,Graph::vertex_descriptor> , double> edge_centralities;
    // Adding all edges to graph and initializing betwenness to 0
    for (auto edge : boost::make_iterator_range(edges(g))) {
        pair<Graph::vertex_descriptor, Graph::vertex_descriptor> w;
        w.first = edge.m_source;
        w.second = edge.m_target;
        edge_centralities[w] = 0;
    }
    // Looping through all vertices in graph
    // Running BFS on each vertex
    // Calculating the edge betweenness
    for (auto v : boost::make_iterator_range(vertices(g))){
        map <Graph::vertex_descriptor, bool> visited; // To know when vertex is visited
        vector <Graph::vertex_descriptor> src; // current vertices that were targets of the prior vertex and haven't been visited
        src.push_back(v); // Adding the current vertex to it as well
        map <Graph::vertex_descriptor, pair <double, double> > vScore;
        vScore[v].first += 1; // node score
        vScore[v].second += 1; // edge credit
        vector <map<Graph::vertex_descriptor,vector<Graph::vertex_descriptor> > > edgePaths;
        // Initializing all vertices to false in terms of being visited
        for (auto v : boost::make_iterator_range(vertices(g)))
            visited.insert(pair<Graph::vertex_descriptor,bool>(v,false));

        while (true){
            // Current vertices that will be looped through to gather score set to true in terms of being visited
            for (int i = 0; i < src.size(); i++){
                visited.at(src[i]) = true;
            }

            vector <Graph::vertex_descriptor> nextSrc; // stores the targets from the current vertices
            map<Graph::vertex_descriptor,vector<Graph::vertex_descriptor> > currentPath;
            // Gets all targets from each vertex currently being iterated through
            for (int i = 0; i < src.size(); i++){
                auto edges = g.m_vertices.at(src[i]).m_out_edges;
                // If it hasn't been visited it will add to the node score and the edge credit will be set to 1
                for (int j = 0; j < edges.size(); j++){
                    if (!visited.at(edges[j].m_target)){
                        nextSrc.push_back(edges[j].m_target);
                        vScore[edges[j].m_target].first += vScore[src[i]].first;
                        vScore[edges[j].m_target].second = 1;
                        currentPath[edges[j].m_target].push_back(src[i]);
                    }

                }

            }
            // When all vertices have been visited, it will break out of the while loop
            // If there are still more vertices the visit it will continue the while loop
            // with the vertices connect to the vertices from last loop being up next
            if (nextSrc.size() == 0)
                break;
            else {
                edgePaths.push_back(currentPath);
                src = nextSrc;
            }


        }
        // Calculates edge betweenness
        // edgePaths contain for each loop through true the vertices visited from the src vertices
        // Then they add up the node score and edge credit from each edge from each node
        // Which will then result in the total edge betweenness for each edge
        // This will be computed for each vertex in the graph after being ran through BFS
        for (int i = edgePaths.size() - 1; i > -1; i--){
            auto levelNodes = edgePaths[i];

            for (auto const& j : levelNodes){
                auto edges = j.second;
                for (int k = 0; k < edges.size(); k++){
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
    // Scales each modularity down by dividing it by 2
    scaling (edge_centralities);
    return edge_centralities;
}

// Loops through each community.
// Then loops through all the edges in said community.
// During each inner loop (the edges) it checks to see if they existed in the same community prior,
// if they did A = 1, if they didn’t A = 0.
// And then still in that same inner loop we set 2 values numOfEdgesA and numOfEdgesB
// to hold the amount of edges connected to the source and target vertices respectfully.
// After they, still inside the inner for loop we calculate the modularity equation.
// It gets incremented every time that inner loop happens.
// The inner loop gets initialized based on the amount of communities in the new updated graph.
// And inner loop, loops for the amount of edges connected to a vertex in a specific community
double GirvanNewman::calculateModularity(Graph& oldG, Graph& newG, double edgeCount){

    double res = 0;
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
