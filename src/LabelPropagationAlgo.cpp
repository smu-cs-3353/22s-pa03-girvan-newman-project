//
// Created by mikec_g1kgiu8 on 4/11/2022.
//

#include "LabelPropagationAlgo.h"

void LabelPropagationAlgo::runAlgo(char* filePath) {
    struct VertexProperty { //stores the data key in football.graphml
        long dataKey;
    };

    typedef adjacency_list<vecS, vecS, undirectedS, VertexProperty> Graph;
    typedef dynamic_properties Dproperty;

    Graph g;
    Dproperty dp;

    dp.property("value", boost::get(&VertexProperty::dataKey, g));

    std::string fullPathName = filePath;

    std::ifstream graphFile (fullPathName);
    std::string fileName = fullPathName.substr(fullPathName.find_last_of("/\\") + 1);

    read_graphml(graphFile, g, dp);

    std::map<int, int> node_labels; //holds the current label for each node
    std::map<int, std::vector<int> > neighbor_nodes; //holds the labels of the current node's neighbors

    std::vector<int> nodes; //holds each node in the graph

    for (auto v : boost::make_iterator_range(vertices(g))) {
        node_labels[v] = v; //Initializing each node with its own unique label

        nodes.push_back(v); //adds the current node to the vector of nodes in the graph

        //the following code was found at: https://stackoverflow.com/questions/49898415/boost-library-how-to-get-neighbouring-nodes
        auto neighbors = boost::adjacent_vertices(v, g);
        for (auto vd : make_iterator_range(neighbors)) {
            neighbor_nodes[v].push_back(vd); //adds each neighboring node to the vector
        }
    }

    int counter = 1;
    while (true) { //loop that runs until all nodes have the same label as the majority of their neighbor nodes
        std::shuffle(nodes.begin(), nodes.end(), std::mt19937(std::random_device()())); //randomly shuffles the order in which the nodes will be visited

        for (int v : nodes) { //loops through each node (which are randomly sorted)
            std::unordered_map<int, int> label_frequency;

            int new_label = -1;
            int new_label_frequency = 0;

            std::vector<int> new_label_options;

            for (int i = 0; i < neighbor_nodes[v].size(); i++) { //loops through the current node's neighbor nodes
                label_frequency[node_labels[neighbor_nodes[v].at(i)]] += 1;

                if (label_frequency[node_labels[neighbor_nodes[v].at(i)]] > new_label_frequency) { //if a new most frequent label is found
                    new_label = node_labels[neighbor_nodes[v].at(i)];
                    new_label_frequency = label_frequency[node_labels[neighbor_nodes[v].at(i)]]; //updates the label frequency

                    new_label_options.clear(); //clears the vector of options
                } else if (label_frequency[node_labels[neighbor_nodes[v].at(i)]] == new_label_frequency) { //if multiple neighbor node labels have the same frequency
                    if (new_label_options.empty()) {
                        new_label_options.push_back(new_label);
                    }
                    new_label_options.push_back(node_labels[neighbor_nodes[v].at(i)]);
                }
            }
            if (!new_label_options.empty()) { //if multiple neighbor node labels appear the same number of times
                std::shuffle(new_label_options.begin(), new_label_options.end(), std::mt19937(std::random_device()())); //randomly shuffles the options
                node_labels[v] = new_label_options.at(0); //assigns a random option to be the new label
            } else { //if there is only one label that appears most frequent
                node_labels[v] = new_label;
            }

        }

        bool endAlgo = true; //variable that tells the label propagation to stop

        for (auto v: boost::make_iterator_range(vertices(g))) { //loops through every node
            int inCommon = 0; //counts how many neighbor nodes have the same label as the current node
            //label propagation can stop if the current node has the most frequent label among its neighbor nodes
            std::unordered_map<int, int> label_frequency;
            int most_frequent_frequency = 0; //stores how many times the most frequent label appears

            for (int i = 0; i < neighbor_nodes[v].size(); i++) {
                if (node_labels[neighbor_nodes[v].at(i)] == node_labels[v]) { //if the current node and the neighbor node have the same label
                    inCommon++;
                }

                label_frequency[node_labels[neighbor_nodes[v].at(i)]] += 1;

                if (label_frequency[node_labels[neighbor_nodes[v].at(i)]] > most_frequent_frequency) {
                    most_frequent_frequency = label_frequency[node_labels[neighbor_nodes[v].at(i)]];
                }
            }

            if (inCommon < most_frequent_frequency) { //if the current node has a different label than the most frequent label among its neighbor nodes
                endAlgo = false; //continue label propagation
                break;
            }
        }

        if (endAlgo) {
            break;
        }
        counter++;
    }
    if (fileName == "football.graphml") { //for the football dataset

        std::vector<int> labels; //holds all the labels that define each community

        std::ofstream output("../extra/outputForGraph.txt");

        for (auto v: boost::make_iterator_range(vertices(g))) {
            if (std::find(labels.begin(), labels.end(), node_labels[v]) == labels.end()) {
                labels.push_back(node_labels[v]);
            }
            output << node_labels[v] << std::endl;
        }

        output.close();

        std::sort(labels.begin(), labels.end()); //sorts the vector by increasing numerical order

        output.open("../output/LabelPropagationOutput.txt"); //output file containing data on the communities

        output << "Communities For Label Propagation:\n" << std::endl;
        std::cout << "Communities For Label Propagation:\n" << std::endl;

        for (int i = 0; i < labels.size(); i++) { //outputs the communities generated
            std::cout << "Community " << i + 1 << std::endl;
            std::cout << std::endl;
            output << "Community " << i + 1 << std::endl;
            output << std::endl;
            std::ifstream input("../extra/schoolNames.txt");
            int counter2 = 0;
            while (!input.eof()) {
                std::string name;
                input >> name;
                if (node_labels[counter2] == labels.at(i)) {
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
    else { //for other datasets

        std::map<int, std::vector<Graph::vertex_descriptor> > nodesInCommunities;

        for (auto v: boost::make_iterator_range(vertices(g)))
            nodesInCommunities[node_labels[v]].push_back(v);

        std::ofstream output("../output/LabelPropagationOutput.txt");

        output << "Communities For Label Propagation:\n" << std::endl;
        std::cout << "Communities For Label Propagation:\n" << std::endl;

        int count = 1;
        for (auto const& iter : nodesInCommunities){
            std::cout << "Community " << count << std::endl;
            std::cout << std::endl;
            output << "Community " << count << std::endl;
            output << std::endl;
            for (int i = 0; i < iter.second.size(); i++){
                std::cout << iter.second[i] << std::endl;
                output << iter.second[i] << std::endl;

            }
            std::cout << std::endl;
            output << std::endl;
            count++;
        }
    }
}
